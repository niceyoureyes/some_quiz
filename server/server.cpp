#include "server.h"

ServerSyncr::ServerSyncr(io_service & service, int port) :
  m_acp(service, ip::tcp::endpoint(ip::tcp::v4(), port))
{
  m_service = &service;
}

void ServerSyncr::LoopFunc(void(*func)(string login, string data, string & dataOut))
{
  m_func = func;
}

void ServerSyncr::Write(ip::tcp::socket & sock, string data)
{
  sock.write_some(buffer(data));
}

void ServerSyncr::Run()
{
  thrGo = thread(bind(MLoop, this));
}

void ServerSyncr::Stop()
{
  m_stop = true;
}

void ServerSyncr::Wait()
{
  thrGo.join();
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

void MLoop(ServerSyncr* obj)
{
  while (!obj->m_stop) {

    ip::tcp::socket sock(*(obj->m_service));
    obj->m_acp.accept(sock);
    int bytes = read(sock, buffer(obj->buff), boost::bind(read_complete, obj->buff, _1, _2)); //read
    obj->m_data_read = string(obj->buff, bytes - 1);

    string strLogin, strData;
    obj->m_dataManager.SplitRequest(obj->m_data_read, strLogin, strData);
    if (strLogin != "" && strLogin != AUTHO_SYMBOL) {
      string strOut;
      obj->m_func(strLogin, strData, strOut);
      sock.write_some(buffer(strOut + END_SYMBOL)); //write
    }
    else if (strLogin == AUTHO_SYMBOL) {
      sock.write_some(buffer(AUTHORIZE)); //write
    }
    else {
      sock.write_some(buffer(NON_AUTHORIZE)); //write
    }
    sock.close();

  }
}