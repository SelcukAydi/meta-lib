#include "TestCommonDefs.hpp"
#include "detail/exec.hpp"
#include <gtest/gtest.h>

TEST(ExtractFirstError, 0)
{
    // Declaring an error extracted from ExtractFirstError explicity.
    //
    using Result =
        sia::meta::ExtractFirstError::apply<sia::meta::Error<NotDefaultConstructibleErrorTag>>::type;

    // Result should be an error.
    //
    static_assert(sia::meta::Exec<sia::meta::IsError(Result)>::type::value);
}

TEST(ExtractFirstError, 1)
{
    // Extracting the first error from the executed metafunction's output.
    //
    using ConstractedError =
        sia::meta::Exec<sia::meta::ConstructError(NotDefaultConstructibleErrorTag)>::type;

    // Extract the first error from the constructed error.
    //
    using ExtractedError = sia::meta::ExtractFirstError::apply<ConstractedError>::type;

    // Check if this is really an error.
    //
    using Check = sia::meta::Exec<sia::meta::IsError(ExtractedError)>::type;

    static_assert(Check::value);
}

TEST(ExtractFirstError, 2)
{
    // There should not be no any error in the type list.
    //
    using Check = sia::meta::ExtractFirstError::apply<std::false_type, std::integral_constant<std::size_t, 99>>::type;

    static_assert(std::is_same_v<sia::meta::None, Check>);
}

TEST(ExtractFirstError, 3)
{
    // The error is at the end of the type list.
    //
    using ExtractedError =
        sia::meta::ExtractFirstError::apply<std::false_type, std::integral_constant<std::size_t, 99>,
                                            sia::meta::Error<NotDefaultConstructibleErrorTag>>::type;

    static_assert(!std::is_same_v<sia::meta::None, ExtractedError>);
}

TEST(ExtractFirstError, 4)
{
    // The error is at the middle of the type list.
    //
    using ExtractedError =
        sia::meta::ExtractFirstError::apply<std::false_type,
                                            sia::meta::Error<NotDefaultConstructibleErrorTag>,
                                            std::integral_constant<std::size_t, 99>>::type;

    // Assert that if this is the correct error.
    //ac
    static_assert(std::is_same_v<sia::meta::Error<NotDefaultConstructibleErrorTag>, ExtractedError>);
}

TEST(ExtractFirstError, 5)
{
    // Two errors in the list.
    //
    using FirstError = sia::meta::Error<NotDefaultConstructibleErrorTag>;
    using SecondError = sia::meta::Error<StandartErrorTag>;

    // Extract the error.
    //
    using ExtractedError =
        sia::meta::Exec<sia::meta::ExtractFirstError(std::true_type, SecondError, FirstError, std::false_type)>::type;

    // Second error should have been extracted as the first error.
    //
    static_assert(std::is_same_v<SecondError, ExtractedError>);
}

