#include "server.h"
#include <sstream>
#include <map>
#include <ctime>

io_service serviceMain;

vector < pair <string, string>> quest;
map <string, int> m;
stringstream SS;
int r = -1;

void f(string login, string data, string & dataOut) {
  string result;
  if (data != "first") {
    int rr = stoi(data.substr(0, data.find('@')));

    if (data.substr(data.find('@') + 1) == quest[rr].second) {
      m[login] += 1;
      r = rand() % quest.size();
      result = "Correct! ";
    }
    else
    {
      result = "Wrong answer! ";
    }
  }
  else {
    m[login] = 0;
  }
  if (r == -1) {
    r = rand() % quest.size();
  }
  string best; int coin = -1;
  for (auto i = m.begin(); i != m.end(); i++) {
    if (coin < i->second) {
      best = i->first; coin = i->second;
    }
  }

  dataOut = to_string(r) + "@" + result + "The best: " + best + " _______ " + quest[r].first;
}

int main() {
  srand(time(0));
  quest.push_back(make_pair("2 * 2 = ", "4"));
  quest.push_back(make_pair("2 / 2 = ", "1"));
  quest.push_back(make_pair("2 / 5 * 100 = ", "40"));
  quest.push_back(make_pair("2^e > e^2 ?", "no"));
  quest.push_back(make_pair("10 > 5 ?", "yes"));
  quest.push_back(make_pair("1 + 2 + 3 + ... + 10 = ", "55"));
  quest.push_back(make_pair("1 * 2 * 3 * 4 * 5 = ", "120"));
  quest.push_back(make_pair("F = m * ?", "a"));
  quest.push_back(make_pair("? = m * c^2", "E"));

  ServerSyncr server(serviceMain, 8002);

  cout << "Starting server on port 8002..." << endl;

  server.LoopFunc(f);
  server.Run();

  cout << "Done" << endl;

  server.Wait();
  system("pause");
  return 0;
}
