#include <iostream>
#include <string_view>
#include <fstream>
#include <unordered_map>

#include "stream_manager.hpp"
#include "shell.h"
#include "cmds.h"
#include "env/user.h"
#include "env/home_dir.h"
#include "env/path_cmds.h"
#include "env/path_cmds_call.h"
#include "feature/path_str_gen.h"
#include "feature/theme.h"
#include "feature/string_parser.h"

Shell::Shell(std::istream& in, std::ostream& out, std::ostream& err)
    : exit_check(false),
    stream_manager(in, out, err)
{
    variable_manager.set("USER", user_name)
                    .set("HOME_DIR", home_dir)
                    .set("COLOR_THEME", theme_default.at("theme_name"))
                    .set("COLOR_NAME", theme_default.at("name"))
                    .set("COLOR_PATH", theme_default.at("path"))
                    .set("COLOR_DIR", theme_default.at("dir"))
                    .set("COLOR_WARN", theme_default.at("warn"))
                    .set("COLOR_SAVE", theme_default.at("save"))
                    .set("COLOR_RESET", theme_default.at("reset"))
                    .set("SYSTEM", sys)
                    .set("PATH", env_path_get())
                    .set("0", "yush");
}

int Shell::init() {
    const std::vector<std::string>& arg = {
        std::filesystem::current_path().string(),
        std::string(variable_manager.get("HOME_DIR")) + ".yushrc"
    };

    return cmds::yush(arg, stream_manager, variable_manager);
}

int Shell::run(bool output) {
    int runtime_status = 0;
    while (!exit_check && !stream_manager.in().eof()) {
        if (output) {
            stream_manager.out() << "\n"
                                 << variable_manager.get("COLOR_NAME") << variable_manager.get("USER")
                                 << variable_manager.get("COLOR_RESET") << ' '
                                 << variable_manager.get("COLOR_PATH") << path_str_gen(variable_manager.get("HOME_DIR"))
                                 << variable_manager.get("COLOR_RESET") << '\n';
            if (runtime_status != 0) {
                stream_manager.out() << variable_manager.get("COLOR_WARN");
            }
            // stream_manager.out() << runtime_status; // when debug
            stream_manager.out() << "> " << variable_manager.get("COLOR_RESET");
        }

        std::string input;
        std::getline(stream_manager.in(), input);

        runtime_status = run_command(input, stream_manager);
    }

    return runtime_status;
}

int Shell::run_command(const std::string current_command, StreamManager& stream_manager) {
    using namespace cmds;

    if (current_command == "") {
        return 0;
    }

    std::vector<std::string> arg = string_parser(current_command, ' ');

    static const std::unordered_map<std::string, decltype(&alias)> command_map = {
        {"alias", alias},
        {"cat", cat},
        {"cd", cd},
        {"clear", clear},
        {"cp", cp},
        {"date", date},
        {"echo", echo},
        {"function", function},
        {"help", help},
        {"la", la},
        {"ls", ls},
        {"mkdir", mkdir},
        {"mv", mv},
        {"pwd", pwd},
        {"rm", rm},
        {"set", set},
        {"touch", touch},
        {"whoami", whoami},
        {"yush", yush},
    };

    if (arg[0] == "exit") {
        exit_check = true;
        return 0;
    }

    auto command_it = command_map.find(arg[0]);
    if (command_it != command_map.cend()) {
        return command_it->second(arg, stream_manager, variable_manager);
    }

    return cmd_call(arg, stream_manager, variable_manager);
    return 127;
}
