#ifndef THEME_H__
#define THEME_H__

#include <iostream>
#include <map>

#include "./color_text.h"

const std::map<std::string, std::string> theme_defalut{
    {"name", yellow},
    {"path", magenta},
    {"dir", cyan},
    {"warn", red},
    {"save", green},
};

const std::map<std::string, std::string> theme_one_color{
    {"name", reset},
    {"path", reset},
    {"dir", reset},
    {"warn", reset},
};

const std::map<std::string, std::string> theme_lightmode{
    {"name", white_back},
    {"path", white_back},
    {"dir", white_back},
    {"warn", white_back},
};

#endif