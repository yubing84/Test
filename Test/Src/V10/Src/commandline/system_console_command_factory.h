#ifndef SYSTEM_CONSOLE_COMMAND_FACTORY_H
#define SYSTEM_CONSOLE_COMMAND_FACTORY_H

#include <string>


namespace wmdf
{
  class ConsoleCommand;
  class ConsoleCommandGroup;

  // system command factory
  // ����һ����Ч��ConsoleCommand
  ConsoleCommand* CreateNullConsoleCommand();

  // ����system��
  ConsoleCommandGroup* CreateSystemConsoleCommandGroup();

  // ��system���У�����ConsoleCommand
  // ������ֵΪ�գ�����δ�����Ӧcommand_line��ConsoleCommand����
  ConsoleCommand* CreateSystemConsoleCommand(std::string command_name);

}

#endif
