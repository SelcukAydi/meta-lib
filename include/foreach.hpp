#pragma once

#include "set.hpp"
#include "vector.hpp"
namespace sia::meta::detail
{
struct ForEach
{
    template <typename... Ts>
    struct apply;

    template <typename F, typename... Ts>
    struct apply<F, Vector<Ts...>>
    {
        template <typename... Pack>
        struct apply_helper;

        template <typename... Items, typename... Pack, typename Current>
        struct apply_helper<Vector<Items...>, Current, Pack...>
        {
            using type =
                typename apply_helper<Vector<Items..., typename F::template apply<Current>::type>, Pack...>::type;
        };

        template <typename... Pack>
        struct apply_helper<Vector<Pack...>>
        {
            using type = Vector<Pack...>;
        };

        using type = typename apply_helper<Vector<>, Ts...>::type;
    };

    template <typename F, typename... Ts>
    struct apply<F, Set<Ts...>>
    {
        template <typename... Pack>
        struct apply_helper;

        template <typename... Items, typename... Pack, typename Current>
        struct apply_helper<Set<Items...>, Current, Pack...>
        {
            using type = typename apply_helper<Set<Items..., typename F::template apply<Current>::type>, Pack...>::type;
        };

        template <typename... Pack>
        struct apply_helper<Set<Pack...>>
        {
            using type = Set<Pack...>;
        };

        using type = typename apply_helper<Set<>, Ts...>::type;
    };
};

}  // namespace sia::meta::detail
