#include <type_traits>
#include "exec.hpp"
#include "foreach.hpp"
#include "meta-basics.hpp"
#include "set.hpp"
#include "vector.hpp"

struct IdentityFunctor
{
    template<typename T>
    struct apply
    {
        using type = T;
    };
};


TC_BEGIN(Foreach, 1)
{
    using V1 = sia::meta::detail::Vector<int, double, char, float, bool>;
    using Result = sia::meta::Exec<sia::meta::detail::ForEach(IdentityFunctor, V1)>::type;
    static_assert(std::is_same_v<Result, V1>, "V1 and Result must be same!");
}

TC_BEGIN(Foreach, 2)
{
    using Set1 = sia::meta::detail::Set<int, double, char, float, bool>;
    using Result = sia::meta::Exec<sia::meta::detail::ForEach(IdentityFunctor, Set1)>::type;
    static_assert(std::is_same_v<Result, Set1>, "Result must be same with Set1");
}
