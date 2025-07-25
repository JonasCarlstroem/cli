#pragma once
// std
#include <vector>

// lib
#include "argument.h"

namespace cli {

class option {
    string name_;
    string description_;
    std::vector<argument> args_;

  public:
    option() = default;
    option(string name) : name_(std::move(name)) {}

    void add_argument(argument arg) { args_.emplace_back(std::move(arg)); }

    const string &name() const { return name_; }
    const std::vector<argument> &args() const { return args_; }
};

} // namespace cli