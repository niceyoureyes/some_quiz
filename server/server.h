#pragma once
#include <string>
#include <thread>
#include <functional>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\config.hpp"
#include <iostream>
#include "data.h"
#define MAX_SIZE_OF_BUFF 1024
#define CR 13 // /n
#define LF 10 // /r

using namespace std;
using namespace boost::asio;

class ServerSyncr {
public:
  ServerSyncr(io_service & service, int port);
  void LoopFunc(void(*func)(string login, string data, string & dataOut));
  void Write(ip::tcp::socket & sock, string data);
  void Run();
  void Stop();
  void Wait();
private:
  friend void MLoop(ServerSyncr* obj);

  bool m_stop = false;
  string m_data_read;
  string* m_data_write;
  function <void(string, string, string &)> m_func;

  thread thrGo;
  io_service* m_service;
  ip::tcp::acceptor m_acp;
  DataManagment m_dataManager;
  char buff[MAX_SIZE_OF_BUFF];
};

void MLoop(ServerSyncr* obj);
size_t read_complete(char* buff, const boost::system::error_code & err, size_t size_byte);