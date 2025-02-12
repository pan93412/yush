#ifndef SHELL_H
#define SHELL_H

#include <string_view>
#include <vector>
#include <filesystem>
#include <string>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "env/system_var.h"
#include "cmds.h"

class Shell {
public:
    Shell(std::istream& in, std::ostream& out, std::ostream& err);

    int init();
    int run(bool);

private:
    int run_command(std::string current_command, StreamManager& stream_manager);

    bool exit_check;
    VariableManager variable_manager;
    StreamManager stream_manager;
};

#endif