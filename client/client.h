#pragma once
#include <string>
#include <thread>
#include <functional>
#include "boost\asio.hpp"
#include "boost\bind.hpp"
#include "boost\config.hpp"
#include <iostream>
#define SPLIT_SYMBOL "#"
#define AUTHO_SYMBOL "*"
#define END_SYMBOL "\n"
#define AUTHORIZE "AUTHORIZE"
#define NON_AUTHORIZE "NON_AUTORIZE"
#define MAX_SIZE_OF_BUFF 1024
#define CR 13 // /n
#define LF 10 // /r

using namespace std;
using namespace boost::asio;

class ClientSyncr {
public:
  ClientSyncr(io_service & service, string ip, int port);
  void LoopFunc(string & dataOutput, void(*func)(string dataInput));
  void Run();
  void Stop();
  void Wait();
  bool Autorization(string login, string password);
private:
  int m_timeSleepLoopMC = 100;
  string m_login;
  string m_password;
  bool m_stop = false;
  string* m_data_write;
  function <void(string)> m_func;

  thread thrGo;
  io_service* m_service;
  ip::tcp::endpoint ep;
  char buff[MAX_SIZE_OF_BUFF];
  friend void MLoop(ClientSyncr* obj);
};

size_t read_complete(char* buff, const boost::system::error_code & err, size_t size_byte);
void MLoop(ClientSyncr* obj);