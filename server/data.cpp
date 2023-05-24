#include "data.h"

DataManagment::DataManagment()
{

}

void DataManagment::SplitRequest(string query, string & login, string & data)
{
  m.clear();
  int lastSumb = 0;
  for (int i = 0; i < query.size(); i++) {
    if (query[i] == SPLIT_SYMBOL) {
      m.push_back(query.substr(lastSumb, i - lastSumb));
      lastSumb = i + 1;
    }
  }
  if (m[0] == AUTHO_SYMBOL) {
    if (m_authorizationData[m[1]] == "") {
      m_authorizationData[m[1]] = m[2];
      cout << "Registration succesful" << endl;
      login = AUTHO_SYMBOL; data = "";
    }
    else if (m_authorizationData[m[1]]== m[2]) {
      cout << "Authorization succesful" << endl;
      login = AUTHO_SYMBOL; data = "";
    }
    else {
      //cout << "This name already used" << endl;
      login = ""; data = "";
    }
  }
  else {
    if (m_authorizationData[m[0]] == m[1]) {
      login = m[0];
      data = m[2];
      cout << "Good data" << endl;
    }
    else {
      login = "";
      data = "";
      cout << "Bad data" << endl;
    }
  }
}

void DataManagment::FileToString(string filename, string & strOut)
{
  fin.open(filename);
  if (fin.is_open()) {
    strOut = "";
    fin.seekg(0, std::ios::end);
    size_t size = fin.tellg();
    strOut.resize(size);
    fin.seekg(0);
    fin.read(&strOut[0], size);
  }
  else {
    cerr << "Can't open the file: " << filename << endl;
  }
  fin.close();
}