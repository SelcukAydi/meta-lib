#pragma once

#include <type_traits>

struct Type
{
    template<typename T>
    struct apply
    {
        using type = T;
    };
};

struct If {};

struct RemoveReference
{
    template<typename T>
    struct apply
    {
        using type = std::remove_reference_t<T>;
    };
};

struct HasPrintMethod
{
    template<typename T, typename = std::void_t<>>
    struct apply
    {
        using type = std::false_type;
    };

    template<typename T>
    struct apply<T, decltype(std::declval<T>().print())>
    {
        using type = std::true_type;
    };
};

struct And
{
    template<typename... MetaExpr>
    struct apply;

    template<typename MetaExpr>
    struct apply<MetaExpr>
    {
        using type = MetaExpr;
    };

    template<typename MetaExpr1, typename MetaExpr2>
    struct apply<MetaExpr1, MetaExpr2>
    {
        using type = If(MetaExpr1, MetaExpr2, std::false_type);
    };

    template<typename MetaExpr1, typename MetaExpr2, typename... MetaExprTail>
    struct apply<MetaExpr1, MetaExpr2, MetaExprTail...>
    {
        using type = If(MetaExpr1, If(MetaExpr2, And(MetaExprTail...), std::false_type), std::false_type);
    };
};

struct Or
{
    template<typename... MetaExpr>
    struct apply
    {
        using type = std::false_type;
    };

    template<typename MetaExpr>
    struct apply<MetaExpr>
    {
        using type = MetaExpr;
    };

    template<typename MetaExpr1, typename MetaExpr2>
    struct apply<MetaExpr1, MetaExpr2>
    {
        using type = If(MetaExpr1, std::true_type, MetaExpr2);
    };

    template<typename MetaExpr1, typename MetaExpr2, typename... MetaExprTail>
    struct apply<MetaExpr1, MetaExpr2, MetaExprTail...>
    {
        using type = If(MetaExpr1, std::true_type, If(MetaExpr2, std::true_type, Or(MetaExprTail...)));
    };
};