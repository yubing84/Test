#include <iostream>
using namespace std;

#include "console_command_processor.h"
using namespace wmdf;

int main(int argc, char* argv[])
{
  // ����������processor
  ConsoleCommandProcessor console_command_processor;

  // ����wmdf������
  console_command_processor.EnterMDFConsole();

  // ������ѭ��
  while(1)
  {
    string command_line;
    cin >> command_line;
    console_command_processor.ProcessConsoleCommand(command_line);
  }

  // �˳�wmdf������
  console_command_processor.ExitMDFConsole();

	return 0;
}