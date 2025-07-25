#pragma once
#include <optional>
#include <string>
#include <variant>
using string = std::string;

namespace cli {

enum class argument_type { boolean, integer, string };

class argument {
    using value_type = std::variant<std::monostate, bool, int, string>;
    friend class parser;

    template <value_type argument::* s> void set_from_str(const string& str) {
        try {
            switch (type_) {
            case argument_type::boolean:
                this->*s = (str == "true" || str == "1");
                break;
            case argument_type::integer:
                this->*s = std::stoi(str);
                break;
            case argument_type::string:
                this->*s = str;
                break;
            }
        } catch (...) {
            throw std::runtime_error("Failed to parse value for argument: " + name());
        }
    }

  public:
    argument() = default;

    argument(
        string name,
        std::optional<std::string> alias       = std::nullopt,
        std::optional<std::string> description = std::nullopt,
        value_type default_value               = "",
        argument_type arg_type                 = argument_type::string
    )
        : name_(std::move(name)),
          alias_(std::move(alias)),
          description_(std::move(description)),
          default_value_(std::move(default_value)),
          type_(std::move(arg_type)) {}

    template <typename T>
    argument(
        string name,
        std::optional<std::string> alias = std::nullopt,
        std::optional<std::string> description = std::nullopt,
        T default_value             = T(),
        argument_type arg_type      = argument_type::string
    )
        : name_(std::move(name)),
          alias_(std::move(alias)),
          description_(std::move(description)),
          default_value_(std::move(default_value)),
          type_(std::move(arg_type)) {}

    void set_value(value_type v) { value_ = std::move(v); }

    void set_default(value_type v) { default_value_ = std::move(v); }

    void set_value_from_string(const std::string& str) { set_from_str<&argument::value_>(str); }

    void set_default_from_string(const string& str) {
        set_from_str<&argument::default_value_>(str);
    }

    bool was_provided() const { return value_.index() != 0; }

    template <typename T> std::optional<T> get_value() const {
        if (auto pval = std::get_if<T>(&value_)) return *pval;
        if (auto pval = std::get_if<T>(&default_value_)) return *pval;
        return std::nullopt;
    }

    const string& name() const { return name_; }

    const std::optional<std::string>& alias() const { return alias_; }

    const std::optional<std::string>& description() const { return description_; }

    argument_type type() const { return type_; }

    bool matches(const string& token) const {
        return (!name_.empty() && name_ == token) || (alias_ && string(*alias_) == token);
    }

    argument clone_with_current_state() const {
        argument copy(name_, alias_, description_, default_value_, type_);
        copy.value_ = value_;
        return copy;
    }

    operator string() {
        auto r = get_value<string>();
        return r.has_value() ? r.value() : "";
    }

    operator int() {
        auto r = get_value<int>();
        return r.has_value() ? r.value() : INT_MIN;
    }

    operator bool() {
        auto r = get_value<bool>();
        return r.has_value() ? r.value() : false;
    }

  private:
    string name_;
    std::optional<std::string> alias_;
    std::optional<std::string> description_;
    argument_type type_ {argument_type::string};
    value_type default_value_;
    value_type value_;
};

} // namespace cli