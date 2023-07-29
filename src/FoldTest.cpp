#include <type_traits>
#include "detail/fold.hpp"
#include "detail/meta-basics.hpp"

struct VoidFunctor
{
    template<typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Ts...>
    {
        using type = T;
    };

    template<typename T1, typename T2, typename... Ts>
    struct apply<T1, T2, Ts...>
    {
        using type = std::conditional_t<(sizeof(T1) <= sizeof(T2)), T1, T2>;
    };
};

TC_BEGIN(Fold, 1)
{
    using Result = sia::meta::detail::Fold::apply<VoidFunctor, double, float, char, bool>::type;
    static_assert(std::is_same_v<char, Result>, "");
}
