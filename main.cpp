#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "Commands/info.h"
#include "APIs/checkCommand.h"
#include "APIs/existsFile.h"
#include <Windows.h>
using namespace std;

//Variablen
  double Version = 0.1;
  string System = "Windows";
  char pfad[256];
  string input;
  string hostname = "Windows";
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  //Variablen ende

// DAS HIER DANN IN COMMANDS_H
void befehl1(vector<string> args);

vector<string> names;
void(*befehle[2])(vector<string> args) =
{
  &befehl1,
  befehl1
};

void nInit()
{
  names.push_back("befehl1");
  names.push_back("befehl2");
}

void befehl1(vector<string> args)
{
  for (int i = 0; i < args.size(); i++)
  {
    cout << "Argument " << i << " = " << args[i] << endl;
  }
  cout << "Befehl1 bendet!" << endl;
  return;
}

#define ANZ names.size();
// ENDE COMMANDS_H





int shell(int argc, char const *argv[])
{
  string cmd = "";

  while (!checkCommand(cmd, "exit"))
  {
    string input;
    vector<string> args;

    getcwd(pfad, 256);
    //bald wird hier der Hostname des pcs definiert
     SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY);
     std::cout << "[" << getenv("USER") << "@" << hostname << "]" << "$ ";
      SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY);
    getline(cin, input);
    if(input != "") {
      stringstream ss(input);
      string buf;

      while (ss >> buf)
      {
          args.push_back(buf);
      }
      cmd = args[0];

        if (checkCommand(cmd, "befehl1") || checkCommand(cmd, "befehl2"))
        {
          befehl1(args);
        }
        else {



          if (existsFile(cmd)) {
             SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
            cout << "Starte Datei in Konsole..";
             SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY);
            cout << ".\n\n";
            string executefilestr = "./";
            executefilestr += cmd.c_str();
            system(executefilestr.c_str());
          }
          else {
             SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
            cout << "Die Datei oder das Kommando wurde nicht gefunden!\n";
        }
      }
    }
  }
}

int scriptfile(int argc, char const *argv[]) {
   SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
  cout << "Die Script funktion ist noch nicht vervollständigt\n";
  return 0;
}


int main(int argc, char const *argv[]) {
  info(Version, System);
  if (argc==1) {
    shell(argc, argv);
  }
  else {
    scriptfile(argc, argv);
  }
return 0;
}
