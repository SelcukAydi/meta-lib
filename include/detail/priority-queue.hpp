#pragma once

#include <type_traits>
#include "exec.hpp"
#include "vector.hpp"
namespace sia::meta::detail
{
template <typename... Ts>
struct PriorityQueue
{
    using top = typename sia::meta::Exec<sia::meta::detail::FindMax(Ts...)>::type;
};

struct PQPush
{
    template <typename... Ts>
    struct apply;

    template <typename NewT, typename... Ts>
    struct apply<NewT, PriorityQueue<Ts...>>
    {
        // TODO(selcuk): NewT msut be put on the first position.
        //
        using type = PriorityQueue<NewT, Ts...>;
    };
};

struct PQRemove
{
    template <typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, PriorityQueue<Ts...>>
    {
        template <typename... Pack>
        struct helper;

        template <typename Current, typename... Items, typename... Pack>
        struct helper<PriorityQueue<Items...>, Current, Pack...>
        {
            using type =
                std::conditional_t<std::is_same_v<Current, T>, typename helper<PriorityQueue<Items...>, Pack...>::type,
                                   typename helper<PriorityQueue<Items..., Current>, Pack...>::type>;
        };

        template <typename... Items>
        struct helper<PriorityQueue<Items...>>
        {
            using type = PriorityQueue<Items...>;
        };

        using type = typename helper<PriorityQueue<>, Ts...>::type;
    };
};

struct PQPop
{
    template <typename... Ts>
    struct apply;

    template <typename... Ts>
    struct apply<PriorityQueue<Ts...>>
    {
        using PQT = PriorityQueue<Ts...>;
        using top = typename PQT::top;

        using type = typename PQRemove::apply<top, PriorityQueue<Ts...>>::type;
    };
};

struct PQTop
{
    template <typename... Ts>
    struct apply;

    template <typename... Ts>
    struct apply<PriorityQueue<Ts...>>
    {
        using type = typename PriorityQueue<Ts...>::top;
    };
};

struct PQSize
{
    template <typename... Ts>
    struct apply;

    template <typename... Ts>
    struct apply<PriorityQueue<Ts...>>
    {
        using type = std::integral_constant<std::size_t, sizeof...(Ts)>;
    };
};
}  // namespace sia::meta::detail

namespace sia::meta
{
template <typename... Ts>
using PriorityQueue = sia::meta::detail::PriorityQueue<Ts...>;
}
