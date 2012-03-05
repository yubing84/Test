#ifndef TAQ_CONSOLE_COMMAND_FACTORY_H
#define TAQ_CONSOLE_COMMAND_FACTORY_H

#include <string>
using namespace std;

namespace wmdf
{
  class IConsoleCommand;
  class ConsoleCommandGroup;

  // taq command factory
  // ����taq��
  ConsoleCommandGroup* CreateTaqConsoleCommandGroup();

  // ��taq���У�����ConsoleCommand
  IConsoleCommand* CreateTaqConsoleCommand(string command_line);

  // ��taq���У�����entry command
  IConsoleCommand* CreateTaqEntryCommand();

}

#endif
