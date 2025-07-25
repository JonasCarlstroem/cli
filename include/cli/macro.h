#pragma once
#include <tuple>
#include <type_traits>

#define CLI_STRINGIFY(x) #x

#define CLI_TO_CLI_NAME(name) CLI_STRINGIFY(name)

#define CLI_MAKE_FIELD(cls, name)                                              \
    std::make_pair(CLI_TO_CLI_NAME(name), &cls::name)

#define CLI_EXPAND(x) x
#define CLI_COUNT_ARGS_IMPL(                                                   \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,     \
    _17, _18, _19, _20, N, ...                                                 \
)                                                                              \
    N

#define CLI_COUNT_ARGS(...)                                                    \
    CLI_COUNT_ARGS_IMPL(                                                       \
        __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,   \
        5, 4, 3, 2, 1                                                          \
    )

#define CLI_FOR_EACH_1(fn, cls, a1) fn(cls, a1)
#define CLI_FOR_EACH_2(fn, cls, a1, a2) fn(cls, a1), fn(cls, a2)
#define CLI_FOR_EACH_3(fn, cls, a1, a2, a3)                                    \
    fn(cls, a1), fn(cls, a2), fn(cls, a3)
#define CLI_FOR_EACH_4(fn, cls, a1, a2, a3, a4)                                \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4)
#define CLI_FOR_EACH_5(fn, cls, a1, a2, a3, a4, a5)                            \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5)
#define CLI_FOR_EACH_6(fn, cls, a1, a2, a3, a4, a5, a6)                        \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5), fn(cls, a6)
#define CLI_FOR_EACH_7(fn, cls, a1, a2, a3, a4, a5, a6, a7)                    \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7)
#define CLI_FOR_EACH_8(fn, cls, a1, a2, a3, a4, a5, a6, a7, a8)                \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7), fn(cls, a8)
#define CLI_FOR_EACH_9(fn, cls, a1, a2, a3, a4, a5, a6, a7, a8, a9)            \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7), fn(cls, a8), fn(cls, a9)
#define CLI_FOR_EACH_10(fn, cls, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)      \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7), fn(cls, a8), fn(cls, a9), fn(cls, a10)
#define CLI_FOR_EACH_11(fn, cls, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7), fn(cls, a8), fn(cls, a9), fn(cls, a10),      \
        fn(cls, a11)
#define CLI_FOR_EACH_12(                                                       \
    fn, cls, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12                 \
)                                                                              \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7), fn(cls, a8), fn(cls, a9), fn(cls, a10),      \
        fn(cls, a11), fn(cls, a12)
#define CLI_FOR_EACH_13(                                                       \
    fn, cls, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13            \
)                                                                              \
    fn(cls, a1), fn(cls, a2), fn(cls, a3), fn(cls, a4), fn(cls, a5),           \
        fn(cls, a6), fn(cls, a7), fn(cls, a8), fn(cls, a9), fn(cls, a10),      \
        fn(cls, a11), fn(cls, a12), fn(cls, a13)

#define CLI_GET_FOR_EACH_MACRO(                                                \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, NAME, ...          \
)                                                                              \
    NAME
#define CLI_FOR_EACH(fn, cls, ...)                                                                                                                                                                                                                               \
    CLI_EXPAND(                                                                                                                                                                                                                                                  \
        CLI_GET_FOR_EACH_MACRO(__VA_ARGS__, CLI_FOR_EACH_13, CLI_FOR_EACH_12, CLI_FOR_EACH_11, CLI_FOR_EACH_10, CLI_FOR_EACH_9, CLI_FOR_EACH_8, CLI_FOR_EACH_7, CLI_FOR_EACH_6, CLI_FOR_EACH_5, CLI_FOR_EACH_4, CLI_FOR_EACH_3, CLI_FOR_EACH_2, CLI_FOR_EACH_1)( \
            fn, cls, __VA_ARGS__                                                                                                                                                                                                                                 \
        )                                                                                                                                                                                                                                                        \
    )

#define CLI_BIND_FIELDS(...)                                                   \
    static constexpr auto cli_fields() { return std::make_tuple(__VA_ARGS__); }

#define CLI_ARG(name, member) std::make_pair(name, member)