#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#define SPLIT_SYMBOL '#'
#define AUTHO_SYMBOL "*"
#define END_SYMBOL "\n"
#define AUTHORIZE "AUTHORIZE\n"
#define NON_AUTHORIZE "NON_AUTORIZE\n"

using namespace std;

class DataManagment {
public:
  DataManagment();
  void SplitRequest(string query, string & login, string & data);
private:
  void FileToString(string filename, string & strOut);
  map <string, string> m_authorizationData;
  vector <string> m;
  string filenameSaves = "data.txt";
  fstream fin;
};