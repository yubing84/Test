// WMDFServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include <string>
#include <iostream>
#include "../environment/server_environment.h"
#include "../commandline/console_command_processor.h"
#include "../product/relay_product_adapter_factory.h"

using namespace std;
using namespace wmdf;

int main(int argc, char* argv[])
{
  ServerEnvironment::PrintServerInfo();
  ServerEnvironment::Initialize();
  RelayProductAdapterFactory::InitializeDispathingCenter();
  ServerEnvironment::StartServer();



  ConsoleCommandProcessor commandProcessor;
  commandProcessor.EnterMDFConsole();

  if (argc > 2)
  {
    std::string command_group(argv[1]);
    commandProcessor.ProcessConsoleCommand(command_group);
    std::string command="";
    for (int index = 2;index < argc;index++)
    {
      command += argv[index];
    }
    commandProcessor.ProcessConsoleCommand(command);
  }

  while (commandProcessor.processing())
  {
    string commandStr = "";
    getline(std::cin,commandStr);
    commandProcessor.ProcessConsoleCommand(commandStr);
  }
  return 0;
}

