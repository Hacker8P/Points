#include <crow>
#include <iostream>
#include <fstream>
#include <random>
#include <sodium.h>
#include "bcrypt.h"

using namespace std;

string GenHash() {
  unsigned char* Data = new unsigned char[100];

  if (sodium_init() < 0)
    throw 8084;

  randombytes_buf(Data, 100);

  char Util[201];

  sodium_bin2hex(Util, 201, Data, 100);

  return Util;
}

string Load(string Filename) {
  string Output;

  ifstream File(Filename);

  if (!File.is_open()) {
    cout << "Cannot open the file " << Filename << endl;
  }

  Output = string(istreambuf_iterator<char>(File), istreambuf_iterator<char>());

  File.close();

  return Output;
}

class Database {
  public:
    Database(string);
    string Location;
    bool VerifyData(string, string);
    string GetData(string);
};

Database::Database(string Location) {
  this->Location = Location;
}

string Database::GetData(string Name) {
  cout << "DEBUG: GD__1" << endl;

  auto DB = crow::json::load(Load(this->Location));

  cout << "DEBUG: GD__2" << endl;

  // cout << (string)DB[Name].s() << endl;

  cout << "DEBUG: GD__8000" << endl;

  return DB[Name].s();
}

bool Database::VerifyData(string Name, string Value) {
  return bcrypt::validatePassword(Value, this->GetData(Name));
}

Database DB("./DB.json");

void ServerAppMain() {
  crow::SimpleApp App;

  CROW_ROUTE(App, "/")(
    [](){
      return Load("pages/index.html");
    }
  );

  CROW_ROUTE(App, "/Host/<path>")(
    [](string Path){
      return Load("pages/" + Path);
    }
  );

  CROW_ROUTE(App, "/Server/Login").methods(crow::HTTPMethod::POST)(
    [](crow::request Request){
      auto Data = crow::json::load(Request.body);

      // DB.VerifyData(Data["Email"].s(), Data["Password"].s());

      cout << GenHash() << endl;

      return "OK";
    }
  );

  App
    .multithreaded()
    .port(60240)
    .run();
}