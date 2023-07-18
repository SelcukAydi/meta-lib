#pragma once

#include <type_traits>
#include "basics.hpp"
#include "exec.hpp"

namespace sia::meta::detail
{
template <typename... Ts>
struct Set
{
};

struct SetContains
{
    template <typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Set<Ts...>>
    {
        static constexpr bool value = (std::is_same_v<T, Ts> || ...);
        using type = Bool<value>;
    };
};

struct SetCheckIfUnique
{
    template <typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<Set<T, Ts...>>
    {
        using type = std::conditional_t<!SetContains::apply<T, Set<Ts...>>::value, typename apply<Set<Ts...>>::type,
                                        Bool<false>>;
    };

    template <>
    struct apply<Set<>>
    {
        using type = Bool<true>;
    };
};

struct SetInsert
{
    template <typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Set<Ts...>>
    {
        using type = std::conditional_t<SetContains::apply<T, Set<Ts...>>::value, Set<Ts...>, Set<T, Ts...>>;
    };
};
}  // namespace sia::meta::detail
