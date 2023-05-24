#include "client.h"
#include <ctime>
#include <sstream>

io_service serviceMain;
stringstream SS;
string dataOutput = "first";
string IP;

void f(string dataInput) {

  string num_q = dataInput.substr(0, dataInput.find('@'));

  cout << dataInput.substr(dataInput.find('@') + 1) << endl;

  string str;
  cin >> str;
  dataOutput = num_q + '@' + str;
}

int main() {
  string login, password;

  srand(time(0));

  cout << "Enter IP" << endl;
  cin >> IP;

  
  cout << "Enter some login and password" << endl;
  cin >> login >> password;

  ClientSyncr client(serviceMain, IP, 8002);
  if (client.Autorization(login, password)) {
    client.LoopFunc(dataOutput, f);
    client.Run();
    client.Wait();
  }
  else
  {
    cout << "Wrong login/password or user with such login already exist!" << endl;
  }

  system("pause");
  return 0;
}
