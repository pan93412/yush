#ifndef CMD_ALIAS_H
#define CMD_ALIAS_H

#include <string>
#include <map>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::alias(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
    // add command
    // size_t found = input.find("=");
    // std::string cmd_name = i.substr(0, found);
    // std::string cmd_content = i.substr(found+1, i.size()-1);
    // alias_map.insert(cmd_name, cmd_content);
    return 0;
}

#endif