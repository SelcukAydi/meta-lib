#include "detail/exec.hpp"
#include "detail/pair.hpp"
#include "detail/conversion-vector.hpp"

#include <gtest/gtest.h>

TEST(ConversionVector, 0)
{
    using M1 = sia::meta::detail::ConversionVector<sia::meta::detail::Pair<int, float>>;
    using Result = sia::meta::Exec<sia::meta::detail::FindPair(int, M1)>::type;
    static_assert(std::is_same_v<sia::meta::detail::Pair<int, float>, Result>);

    using Result1 = sia::meta::Exec<sia::meta::detail::FindPair(float, M1)>::type;
    static_assert(std::is_same_v<Result1, sia::meta::None>);
}

TEST(ConversionVector, 2)
{
    using M1 =
        sia::meta::detail::ConversionVector<sia::meta::detail::Pair<int, float>, sia::meta::detail::Pair<char, bool>>;
    using Result =
        sia::meta::Exec<sia::meta::detail::ConversionMatrixRemovePair(sia::meta::detail::Pair<char, bool>, M1)>::type;
    static_assert(std::is_same_v<Result, sia::meta::detail::ConversionVector<sia::meta::detail::Pair<int, float>>>);
}

TEST(ConversionVector, 3)
{
    using M1 = sia::meta::detail::ConversionVector<sia::meta::detail::Pair<int, float>>;
    using Result =
        sia::meta::Exec<sia::meta::detail::ConversionVectorAddPair(sia::meta::detail::Pair<char, bool>, M1)>::type;
    static_assert(std::is_same_v<Result, sia::meta::detail::ConversionVector<sia::meta::detail::Pair<int, float>,
                                                                             sia::meta::detail::Pair<char, bool>>>);
}
