#include "client.h"

ClientSyncr::ClientSyncr(io_service & service, string ip, int port):
  ep(ip::address::from_string(ip), port)
{
  m_service = &service;
}
  
void ClientSyncr::LoopFunc(string &dataOutput, void(*func)(string dataInput))
{
  m_data_write = &dataOutput;
  m_func = func;
}

void ClientSyncr::Run()
{
  thrGo = thread(bind(MLoop, this));
}

void ClientSyncr::Stop()
{
  m_stop = true;
}

void ClientSyncr::Wait()
{
  thrGo.join();
}

bool ClientSyncr::Autorization(string login, string password)
{
  m_login = login; m_password = password;
  ip::tcp::socket sock(*(m_service));
  sock.connect(ep);
  sock.write_some(buffer("*#" + m_login + SPLIT_SYMBOL + m_password + SPLIT_SYMBOL + END_SYMBOL));

  int bytes = read(sock, buffer(buff), boost::bind(read_complete, buff, _1, _2));
  string answer(buff, bytes - 1);

  sock.close();

  if (answer == AUTHORIZE) {
    return true;
  }
  else {
    return false;
  }
}

size_t read_complete(char* buff, const boost::system::error_code & err, size_t size_byte)
{
  if (err) {
    return 0;
  }
  if (*(buff + size_byte - 1) == '\n') {
    return 0;
  }
  else {
    return 1;
  }
}

void MLoop(ClientSyncr * obj)
{
  while (!obj->m_stop) {
    this_thread::sleep_for(chrono::milliseconds(obj->m_timeSleepLoopMC));
    ip::tcp::socket sock(*(obj->m_service));
    sock.connect(obj->ep);
    sock.write_some(buffer(obj->m_login + SPLIT_SYMBOL + obj->m_password + SPLIT_SYMBOL + *(obj->m_data_write) + SPLIT_SYMBOL + END_SYMBOL));

    int bytes = read(sock, buffer(obj->buff), boost::bind(read_complete, obj->buff, _1, _2));
    string answer(obj->buff, bytes - 1);
    
    obj->m_func(answer);

    sock.close();
  }
}
