#pragma once

#include <type_traits>
#include "meta-basics.hpp"

namespace sia::meta::detail
{

template <typename... Pairs>
struct ConversionVector
{
};

struct FindPair
{
    template <typename... Ts>
    struct apply;

    template <typename SearchT, typename... Pairs>
    struct apply<SearchT, ConversionVector<Pairs...>>
    {
        template <typename... Ts>
        struct helper;

        template <template <typename, typename> typename Pair, typename First, typename Second>
        struct helper<Pair<First, Second>>
        {
            using type = std::conditional_t<std::is_same_v<SearchT, First>, Pair<First, Second>, sia::meta::None>;
        };

        template <typename First, typename Second, template <typename, typename> typename Pair, typename... PairPack>
        struct helper<Pair<First, Second>, PairPack...>
        {
            using type = std::conditional_t<std::is_same_v<SearchT, First>, Pair<First, Second>,
                                            typename apply<PairPack...>::type>;
        };

        using type = typename helper<Pairs...>::type;
    };
};

}  // namespace sia::meta::detail
