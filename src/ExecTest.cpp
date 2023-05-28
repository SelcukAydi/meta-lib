#include <exec.hpp>

struct EmptyMetaFunctor
{
    template <typename... Ts>
    struct apply
    {
        using type = std::true_type;
    };
};

struct FactoryMetaFunctor
{
    template <typename... Ts>
    struct apply
    {
        using type = EmptyMetaFunctor;
    };
};

// Simple meta function that gets mock parameters.
// Returns 11 as constant.
//
struct SimpleMetaFunctor
{
    template <typename T, typename... Args>
    struct apply
    {
        using type = std::integral_constant<std::size_t, 11>;
    };
};

// A meta function that returns another callable functor.
//
struct SelfRecursiveMetaFunctor
{
    template <typename T, typename... Args>
    struct apply
    {
        struct type
        {
            template <typename F = std::false_type, typename... Params>
            struct apply
            {
                using type = std::integral_constant<std::size_t, 12>;
            };
        };
    };
};

// A meta function that returns another meta function.
//
struct RecursiveMetaFunctor
{
    template <typename F, typename... Args>
    struct apply
    {
        using type = F(Args...);
    };
};

TC_BEGIN(ExecTest, 0)
{
    // Call meta function with single parameter.
    //
    using Result = sia::meta::Exec<SimpleMetaFunctor(std::true_type)>::type;
    static_assert(Result::value == 11);
}

TC_BEGIN(ExecTest, 1)
{
    // Call meta function with two parameters.
    //
    using Result = sia::meta::Exec<SimpleMetaFunctor(std::true_type, std::false_type)>::type;
    static_assert(Result::value == 11);
}

TC_BEGIN(ExecTest, 2)
{
    // Call SelfRecursiveMetaFunctor once. SelfRecursiveMetaFunctor returns a functor
    // but its signature is not like F() that's why Exec won't execute the returned value.
    //
    using FirstExec = sia::meta::Exec<SelfRecursiveMetaFunctor(std::false_type)>::type;

    // Call the Exec one more time to execute the returned type.
    //
    using Result = sia::meta::Exec<FirstExec()>::type;

    static_assert(Result::value == 12);
}

TC_BEGIN(ExecTest, 3)
{
    // Call the RecursiveMetaFunctor that returns another meta function. The second
    // meta function is executed by the Exec automaticaly.
    //
    using Result = sia::meta::Exec<RecursiveMetaFunctor(EmptyMetaFunctor)>::type;

    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 4)
{
    // First the FactoryMetaFunctor() is executed then its returned type is executed
    // as a parameter given to RecursiveMetaFunctor.
    //
    using Result = sia::meta::Exec<RecursiveMetaFunctor(FactoryMetaFunctor())>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 5)
{
    // Executes the If meta function.
    //
    using Result = sia::meta::Exec<sia::meta::If(EmptyMetaFunctor(), std::true_type, std::false_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 6)
{
    using Result = sia::meta::Exec<sia::meta::If(EmptyMetaFunctor(), std::false_type, std::true_type)>::type;
    static_assert(!Result::value);
}

TC_BEGIN(ExecTest, 7)
{
    // Execute the If statement first then SelfRecursiveMetaFunctor meta function.
    // The returned type has to be executed again.
    //
    using Result1 = sia::meta::Exec<SelfRecursiveMetaFunctor(
        sia::meta::If(EmptyMetaFunctor(), std::true_type, std::false_type))>::type;

    // Execute the returned type again.
    //
    using Result2 = sia::meta::Exec<Result1()>::type;

    static_assert(Result2::value == 12);
}

TC_BEGIN(ExecTest, 8)
{
    using Result = sia::meta::Exec<sia::meta::And(std::true_type)>::type;

    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 9)
{
    using Result = sia::meta::Exec<sia::meta::And(std::true_type, std::true_type)>::type;

    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 10)
{
    using Result = sia::meta::Exec<sia::meta::And(std::true_type, std::false_type)>::type;

    static_assert(!Result::value);
}

TC_BEGIN(ExecTest, 11)
{
    using Result =
        sia::meta::Exec<sia::meta::And(std::true_type, std::true_type, std::true_type, std::false_type)>::type;

    static_assert(!Result::value);
}

TC_BEGIN(ExecTest, 12)
{
    using Result = sia::meta::Exec<sia::meta::If(sia::meta::And(EmptyMetaFunctor(), std::true_type), std::true_type,
                                                 std::false_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 13)
{
    using Result = sia::meta::Exec<sia::meta::If(sia::meta::And(EmptyMetaFunctor(), std::false_type), std::true_type,
                                                 std::false_type)>::type;
    static_assert(!Result::value);
}

TC_BEGIN(ExecTest, 14)
{
    // Empty And should always return true type.
    //
    using Result = sia::meta::Exec<sia::meta::And()>::type;

    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 15)
{
    using Result = sia::meta::Exec<sia::meta::Or(std::true_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 16)
{
    using Result = sia::meta::Exec<sia::meta::Or(std::true_type, std::true_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 17)
{
    using Result = sia::meta::Exec<sia::meta::Or(std::true_type, std::false_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 18)
{
    using Result =
        sia::meta::Exec<sia::meta::Or(std::true_type, std::true_type, std::true_type, std::false_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 19)
{
    using Check22 = sia::meta::Exec<sia::meta::If(sia::meta::Or(EmptyMetaFunctor(), std::true_type), std::true_type,
                                                  std::false_type)>::type;
    static_assert(Check22::value);
}

TC_BEGIN(ExecTest, 20)
{
    using Result = sia::meta::Exec<sia::meta::If(sia::meta::Or(EmptyMetaFunctor(), std::false_type), std::true_type,
                                                 std::false_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 21)
{
    using Result = sia::meta::Exec<sia::meta::Or()>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 22)
{
    using Result = sia::meta::Exec<sia::meta::Not(std::false_type)>::type;
    static_assert(Result::value);
}

TC_BEGIN(ExecTest, 23)
{
    // Won't compile. Assertion will fail.
    //
    // using Check26 = sia::meta::Exec<sia::meta::If(sia::meta::Not(EmptyMetaFunctor()), std::false_type,
                                                //   sia::meta::NotDefaultConstructibleErrorTag(std::false_type))>::type;
}
