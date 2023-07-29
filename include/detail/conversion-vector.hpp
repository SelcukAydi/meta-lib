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

struct ConversionMatrixRemovePair
{
    template <typename... Ts>
    struct apply;

    template <typename RemoveT, typename... Pairs>
    struct apply<RemoveT, ConversionVector<Pairs...>>
    {
        template <typename... Ts>
        struct helper;

        template <typename First, typename Second, template <typename, typename> typename CurrentPair,
                  typename... Items>
        struct helper<ConversionVector<Items...>, CurrentPair<First, Second>>
        {
            using type =
                std::conditional_t<std::is_same_v<RemoveT, CurrentPair<First, Second>>, ConversionVector<Items...>,
                                   ConversionVector<CurrentPair<First, Second>, Items...>>;
        };

        template <typename First, typename Second, template <typename, typename> typename CurrentPair,
                  typename... PairPack, typename... Items>
        struct helper<ConversionVector<Items...>, CurrentPair<First, Second>, PairPack...>
        {
            using type = std::conditional_t<
                std::is_same_v<RemoveT, CurrentPair<First, Second>>,
                typename helper<ConversionVector<Items...>, PairPack...>::type,
                typename helper<ConversionVector<CurrentPair<First, Second>, Items...>, PairPack...>::type>;
        };

        using type = typename helper<ConversionVector<>, Pairs...>::type;
    };
};

struct ConversionVectorAddPair
{
    template <typename... Ts>
    struct apply;

    template <typename AddT, typename... Pairs>
    struct apply<AddT, ConversionVector<Pairs...>>
    {
        using type = std::conditional_t<
            !std::is_same_v<typename FindPair::template apply<AddT, ConversionVector<Pairs...>>::type, sia::meta::None>,
            ConversionVector<Pairs...>, ConversionVector<Pairs..., AddT>>;
    };
};

struct ConversionVectorSize
{
    template <typename... Ts>
    struct apply;

    template <typename... Pairs>
    struct apply<ConversionVector<Pairs...>>
    {
        using type = std::integral_constant<std::size_t, sizeof...(Pairs)>;
    };
};
}  // namespace sia::meta::detail
