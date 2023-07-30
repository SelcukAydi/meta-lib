#pragma once

#include <cstddef>
#include <type_traits>
#include "meta-basics.hpp"
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

    template <typename... Ts>
    struct apply<Set<Ts...>>
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

struct SetRemove
{
    template <typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Set<Ts...>>
    {
        template <typename Current, typename... Pack>
        struct apply_helper;

        template <typename Current, typename... Pack, typename... Items>
        struct apply_helper<Set<Items...>, Current, Pack...>
        {
            using type =
                std::conditional_t<std::is_same_v<Current, T>, typename apply_helper<Set<Items...>, Pack...>::type,
                                   typename apply_helper<Set<Items..., Current>, Pack...>::type>;
        };

        template <typename... Items>
        struct apply_helper<Set<Items...>>
        {
            using type = Set<Items...>;
        };

        using type = typename apply_helper<Set<>, T, Ts...>::type;
    };
};

struct SetSize
{
    template <typename... Ts>
    struct apply;

    template <typename... Ts>
    struct apply<Set<Ts...>>
    {
        using type = std::integral_constant<std::size_t, sizeof...(Ts)>;
    };
};
}  // namespace sia::meta::detail

namespace sia::meta
{
template <typename... Ts>
using Set = sia::meta::detail::Set<Ts...>;
}
