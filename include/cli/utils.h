#pragma once
#include <type_traits>

//#define CLI_STRINGIFY(x) #x
//
//#define CLI_TO_CLI_NAME(name) CLI_STRINGIFY(name)
//
//#define CLI_MAKE_FIELD(cls, name) std::make_pair(CLI_TO_CLI_NAME(name), &cls::name)
//
//#define CLI_EXPAND(x) x
//#define CLI_COUNT_ARGS_IMPL(                                \
//        _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,            \
//        _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, N, ...) N
//
//#define CLI_COUNT_ARGS(...)                                 \
//    CLI_COUNT_ARGS_IMPL(__VA_ARGS__,                        \
//        20,19,18,17,16,15,14,13,12,11,10,                   \
//        9, 8, 7, 6, 5, 4, 3, 2, 1)
//
//#define CLI_FOR_EACH_1(fn, cls, a1) fn(cls, a1)
//#define CLI_FOR_EACH_2
//
//#define CLI_BIND_FIELDS(...)                                \
//static constexpr auto cli_fields() {                        \
//    using Self = std::decay_t<decltype(*this)>;             \
//    return std::make_tuple(
//        CLI
//    );
//}
//
//#define CLI_BIND(...)                                       \
//static constexpr auto cli_fields() {                        \
//    return std::make_tuple(std::make_pair(__VA_ARGS__));    \
//}
//
//#define CLI_BIND2(...)                                      \
//static constexpr auto cli_fields() {                        \
//    return std::make_tuple(__VA_ARGS__);                    \
//}
//
//
//struct test {
//    int i;
//    bool b;
//    char* ch;
//
//    CLI_BIND(
//        ("i", &test::i)
//    )
//
//        CLI_BIND2(
//            std::make_pair("ip-address", &test::i),
//            std::make_pair("port", &test::b)
//    )
//};

namespace cli {}