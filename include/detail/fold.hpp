#pragma once

#include "exec.hpp"
namespace sia::meta::detail
{
struct FoldImpl
{
    template <typename... Ts>
    struct apply;

    template <typename F, typename First, typename Second, typename... Ts>
    struct apply<F, First, Second, Ts...>
    {
        using type = typename apply<F, typename sia::meta::Exec<typename F::template apply<First, Second>::type>::type,
                                    Ts...>::type;
    };

    template <typename F, typename T>
    struct apply<F, T>
    {
        using type = typename F::template apply<T>::type;
    };
};
}  // namespace sia::meta::detail

namespace sia::meta
{
using Fold = sia::meta::detail::FoldImpl;
}
