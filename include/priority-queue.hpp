#pragma once

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

    template<typename NewT, typename... Ts>
    struct apply<NewT, PriorityQueue<Ts...>>
    {
        // TODO(selcuk): NewT msut be put on the first position.
        //
        using type = PriorityQueue<NewT, Ts...>;
    };
};
}  // namespace sia::meta::detail
