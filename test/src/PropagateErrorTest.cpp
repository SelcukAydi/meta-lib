#include "TestCommonDefs.hpp"
#include <detail/exec.hpp>
#include <gtest/gtest.h>

struct EmptyMetaFunctor
{
    template <typename... Ts>
    struct apply
    {
        using type = std::true_type;
    };
};

struct ErrorMetaFunctor
{
    template <typename... Ts>
    struct apply
    {
        using type = sia::meta::Exec<sia::meta::ConstructError(NotDefaultConstructibleErrorTag)>::type;
    };
};

TEST(PropagateErrorTest, 0)
{
    using Error = sia::meta::Exec<sia::meta::ConstructError(NotDefaultConstructibleErrorTag)>::type;
    using Result = sia::meta::Exec<sia::meta::PropagateError(Error, std::false_type)>::type;

    static_assert(std::is_same_v<Result, Error>);
}

TEST(PropagateErrorTest, 1)
{
    using Result = sia::meta::Exec<sia::meta::PropagateError(EmptyMetaFunctor(), std::false_type)>::type;

    static_assert(std::is_same_v<Result, std::false_type>);
}

TEST(PropagateErrorTest, 2)
{
    using Result = sia::meta::Exec<sia::meta::PropagateError(ErrorMetaFunctor(std::false_type, std::true_type),
                                                             std::false_type)>::type;

    using Check = sia::meta::Exec<sia::meta::IsError(Result)>::type;

    static_assert(Check::value);
}

TEST(PropagateErrorTest, 3)
{
    using Result =
        sia::meta::Exec<EmptyMetaFunctor(sia::meta::PropagateError(EmptyMetaFunctor(), EmptyMetaFunctor()))>::type;

    static_assert(Result::value);
}
