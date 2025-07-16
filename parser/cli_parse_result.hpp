#pragma once
#include "cli_argument.hpp"
#include "cli_macro.hpp"
#include <unordered_map>
#include <vector>

namespace cli {

template <typename T> struct binder;

class parse_result {
    friend class parser;

    string option_;
    std::unordered_map<string, argument> parsed_args_;

    void set_chosen_option(const string &name) { option_ = name; }

    void add_argument(const argument &arg) {
        if (!arg.name().empty())
            parsed_args_[arg.name()] = arg;
        else if (arg.alias().has_value())
            parsed_args_[arg.alias().value()] = arg;
    }

    argument *find_argument(const string &name) {
        auto it = parsed_args_.find(name);
        return it != parsed_args_.end() ? &it->second : nullptr;
    }

    template <typename T, typename FieldPtr>
    void assign_to_field(
        T &instance, const string &cli_name, FieldPtr field_ptr
    ) const {
        if constexpr (std::is_same_v<
                          std::remove_pointer_t<
                              decltype(&(instance.*field_ptr))>,
                          string>) {
            if (auto val = get<string>(cli_name))
                instance.*field_ptr = *val;
        } else if constexpr (std::is_same_v<
                                 std::remove_pointer_t<
                                     decltype(&(instance.*field_ptr))>,
                                 int>) {
            if (auto val = get<int>(cli_name))
                instance.*field_ptr = *val;
        } else if constexpr (std::is_same_v<
                                 std::remove_pointer_t<
                                     decltype(&(instance.*field_ptr))>,
                                 bool>) {
            if (auto val = get<bool>(cli_name))
                instance.*field_ptr = *val;
        }
    }

    template <typename T, typename Tuple>
    void apply_bind(T &instance, const Tuple &fields) {
        std::apply(
            [&](auto &&...pair) {
                ((assign_to_field(instance, pair.first, pair.second)), ...);
            },
            fields
        );
    }

  public:
    const string &option() const { return option_; }
    const std::vector<const argument *> args() const {
        std::vector<const cli::argument *> arguments;
        arguments.reserve(parsed_args_.size());

        for (auto &kv : parsed_args_) {
            arguments.push_back(&kv.second);
        }

        return arguments;
    }

    bool has_arg(const string &name, argument *arg = nullptr) {
        auto it = parsed_args_.find(name);
        if (it == parsed_args_.end())
            return false;
        arg = &it->second;
        return true;
    }

    bool has(const string &name) { return parsed_args_.count(name) > 0; }

    const argument *get_arg(const string &name) {
        return has_arg(name) ? &parsed_args_.at(name) : nullptr;
    }

    template <typename T> bool has_arg(const string &name, const T &value) {
        auto hasArg      = has_arg(name);
        auto cliArgValue = hasArg ? parsed_args_[name].get_value<T>() : T();
        auto isMatch     = hasArg ? cliArgValue == value : false;
        return isMatch;
    }

    template <typename T> std::optional<T> get(const string &name) const {
        if (parsed_args_.count(name) > 0)
            return parsed_args_.at(name).get_value<T>();
        return std::nullopt;
    }

    template <typename T> T bind() {
        T instance{};

        apply_bind(instance, T::cli_fields());

        return instance;
    }

    argument operator[](const char *name) {
        auto arg = parsed_args_.find(name);
        if (arg != parsed_args_.end()) {
            return arg->second;
        }

        return {};
    }
};

} // namespace cli