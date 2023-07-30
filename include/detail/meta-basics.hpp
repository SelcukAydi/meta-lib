#pragma once

#include <type_traits>
#include <string_view>

#define TC_BEGIN(prefix, testNumber) void TestCase##prefix##testNumber()

namespace sia::meta
{
struct If
{
};

struct And
{
    template <typename... MetaExpr>
    struct apply
    {
        using type = std::true_type;
    };

    template <typename MetaExpr>
    struct apply<MetaExpr>
    {
        using type = MetaExpr;
    };

    template <typename MetaExpr1, typename MetaExpr2>
    struct apply<MetaExpr1, MetaExpr2>
    {
        using type = If(MetaExpr1, MetaExpr2, std::false_type);
    };

    template <typename MetaExpr, typename... MetaExprTail>
    struct apply<MetaExpr, MetaExprTail...>
    {
        using type = If(MetaExpr, And(MetaExprTail...), std::false_type);
    };
};

struct Or
{
    template <typename... MetaExpr>
    struct apply
    {
        using type = std::true_type;
    };

    template <typename MetaExpr>
    struct apply<MetaExpr>
    {
        using type = MetaExpr;
    };

    template <typename MetaExpr1, typename MetaExpr2>
    struct apply<MetaExpr1, MetaExpr2>
    {
        using type = If(MetaExpr1, std::true_type, MetaExpr2);
    };

    template <typename MetaExpr, typename... MetaExprTail>
    struct apply<MetaExpr, MetaExprTail...>
    {
        using type = If(MetaExpr, std::true_type, Or(MetaExprTail...));
    };
};

struct Not
{
    template <typename MetaBool>
    struct apply
    {
        using type = std::bool_constant<!MetaBool::value>;
    };
};

struct IsSame
{
    template <typename T1, typename T2>
    struct apply
    {
        using type = std::false_type;
    };

    template <typename T>
    struct apply<T, T>
    {
        using type = std::true_type;
    };
};

struct Identity
{
    template <typename T>
    struct apply
    {
        using type = T;
    };
};

struct PropagateError {};

template <typename ErrorTag, typename... Args>
struct Error
{
};

struct ConstructError
{
    template <typename ErrorTag, typename... Args>
    struct apply
    {
        using type = Error<ErrorTag, Args...>;
    };
};

template <typename... Ts>
struct AlwaysFalse
{
    static constexpr bool value = false;
};

struct IsError
{
    template <typename... MetaExprs>
    struct apply
    {
        using type = std::false_type;
    };
};

template <typename ErrorTag, typename... ErrorArgs>
struct IsError::apply<Error<ErrorTag, ErrorArgs...>>
{
    using type = std::true_type;
};

struct None
{
};

struct ExtractFirstErrorImpl
{
    template<typename... Types>
    struct apply;

    template<typename Type>
    struct apply<Type>
    {
        using type = None;
    };

    template<typename ErrorTag, typename... ErrorArgs>
    struct apply<Error<ErrorTag, ErrorArgs...>>
    {
        using type = Error<ErrorTag, ErrorArgs...>;
    };

    template<typename Type, typename... Types>
    struct apply<Type, Types...>
    {
        using type = std::conditional_t<IsError::apply<Type>::type::value, Type, typename apply<Types...>::type>;
    };
};

struct ExtractFirstError
{
    template <typename... Types>
    struct apply
    {
        using type = typename ExtractFirstErrorImpl::apply<Types...>::type;
    };
};

}  // namespace sia::meta
