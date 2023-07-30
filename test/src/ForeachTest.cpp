#include "detail/foreach.hpp"
#include <gtest/gtest.h>

struct IdentityFunctor
{
    template<typename T>
    struct apply
    {
        using type = T;
    };
};


TEST(Foreach, 1)
{
    using V1 = sia::meta::detail::Vector<int, double, char, float, bool>;
    using Result = sia::meta::Exec<sia::meta::detail::ForEachImpl(IdentityFunctor, V1)>::type;
    static_assert(std::is_same_v<Result, V1>, "V1 and Result must be same!");
}

TEST(Foreach, 2)
{
    using Set1 = sia::meta::detail::Set<int, double, char, float, bool>;
    using Result = sia::meta::Exec<sia::meta::detail::ForEachImpl(IdentityFunctor, Set1)>::type;
    static_assert(std::is_same_v<Result, Set1>, "Result must be same with Set1");
}
