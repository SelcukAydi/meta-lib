#include <exec1.hpp>
#include <iostream>

#include <exec.hpp>

struct Foo
{
};
struct Bar
{
    void print();
};

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

struct SimpleMetaFunctor
{
    template <typename T, typename... Args>
    struct apply
    {
        using type = std::integral_constant<std::size_t, 11>;
    };
};

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

struct RecursiveMetaFunctor
{
    template <typename F, typename... Args>
    struct apply
    {
        using type = F(Args...);
    };
};

extern void TestCaseVector1();
extern void TestCaseVector6();


int main()
{
    TestCaseVector1();
    TestCaseVector6();

    return 0;
}
