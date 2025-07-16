#pragma once
#include "cli_option.hpp"
#include "cli_parse_result.hpp"
#include <optional>
#include <stdexcept>
#include <utils/string>
#include <unordered_map>
#include <vector>
#include <logging/base>

#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE
#endif

auto npos = string::npos;

namespace cli {

class parser {
    std::unordered_map<string, option> options_;
    std::vector<argument> global_args_;
    logging::logger* logger_;

    const argument *
    find_argument_definition(const string &option, const string &name) const {
        if (!option.empty()) {
            auto it = options_.find(option);
            if (it != options_.end()) {
                for (const auto &arg : it->second.args()) {
                    if (arg.matches(name))
                        return &arg;
                }
            }
        }

        for (const auto &arg : global_args_) {
            if (arg.matches(name))
                return &arg;
        }

        return nullptr;
    }

  public:
    parser(logging::logger* logger) : logger_(logger) {}

    void add_option(option opt) {
        options_[opt.name()] = std::move(opt);
    }

    void add_global_argument(argument arg) {
        global_args_.emplace_back(std::move(arg));
    }

    parse_result parse(int argc, char **argv) {
        parse_result result;

        bool found_option = false;
        string current_option;

        for (const auto &arg : global_args_) {
            result.add_argument(arg.clone_with_current_state());
        }

        auto copy_option_args = [&](const string &opt_name) {
            const auto &opt = options_.at(opt_name);
            for (const auto &arg : opt.args()) {
                result.add_argument(arg.clone_with_current_state());
            }
        };

        int i = 1;

        while (i < argc) {
            std::string token = argv[i];

            if (!found_option && !starts_with(token, "-")) {
                if (options_.find(token) == options_.end()) {
                    throw std::runtime_error("Invalid command: " + token);
                }

                result.set_chosen_option(token);
                current_option = token;
                copy_option_args(token);
                found_option = true;
                ++i;
                continue;
            }

            if (starts_with(token, "--") || starts_with(token, "-")) {
                string name, value;
                bool is_long = starts_with(token, "--");

                if (is_long) {
                    auto eq = token.find('=');
                    if (eq != npos) {
                        name  = token.substr(2, eq - 2);
                        value = token.substr(eq + 1);
                    } else {
                        name = token.substr(2);

                        if (i + 1 < argc &&
                            starts_with(argv[i + 1], "-") == false) {
                            value = argv[++i];
                        } else {
                            value = "true";
                        }
                    }
                } else {
                    name = string(1, token[1]);
                    if (i + 1 < argc &&
                        starts_with(argv[i + 1], "-") == false) {
                        value = argv[++i];
                    } else {
                        value = "true";
                    }
                }

                argument *existing = result.find_argument(name);
                if (!existing)
                    throw std::runtime_error("Invalid argument: " + token);

                else if (value == "true")
                    existing->set_value(true);
                else
                    existing->set_value_from_string(value);
            }

            ++i;
        }

        return result;
    }
};

} // namespace cli