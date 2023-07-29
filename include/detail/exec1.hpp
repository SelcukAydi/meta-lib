#pragma once

#include <basics.hpp>

template<typename MetaExpr>
struct DoExec;

template<typename MetaExpr>
struct DoExec
{
    using type = MetaExpr;
};

template<typename MetaFunc, typename... MetaExpr>
struct DoExec<MetaFunc(MetaExpr...)>
{
    using type = typename DoExec<typename MetaFunc:: template apply<typename DoExec<MetaExpr>::type...>::type>::type;
};

template<typename MetaFunc, typename... MetaExpr>
struct DoExec<MetaFunc(*)(MetaExpr...)>
{
    using type = typename DoExec<typename MetaFunc:: template apply<typename DoExec<MetaExpr>::type...>::type>::type;
};

template<typename MetaBool, typename MetaExprThen, typename MetaExprElse>
struct DoExecIf;

template<typename MetaExprThen, typename MetaExprElse>
struct DoExecIf<std::true_type, MetaExprThen, MetaExprElse>
{
    using type = typename DoExec<MetaExprThen>::type;
};

template<typename MetaExprThen, typename MetaExprElse>
struct DoExecIf<std::false_type, MetaExprThen, MetaExprElse>
{
    using type = typename DoExec<MetaExprElse>::type;
};

template<typename CondMetaExpr, typename MetaExprThen, typename MetaExprElse>
struct DoExec<If(CondMetaExpr, MetaExprThen, MetaExprElse)>
{
    using type = typename DoExecIf<typename DoExec<CondMetaExpr>::type, MetaExprThen, MetaExprElse>::type;
};

template<typename CondMetaExpr, typename MetaExprThen, typename MetaExprElse>
struct DoExec<If(*)(CondMetaExpr, MetaExprThen, MetaExprElse)>
{
    using type = typename DoExecIf<typename DoExec<CondMetaExpr>::type, MetaExprThen, MetaExprElse>::type;
};

template<typename MetaExpr>
using Exec = typename DoExec<MetaExpr>::type;

// And(Expr1, Expr2, Expr3)
// If(Expr1, Expr2, false) Expr1 && Expr2
// If(Expr1, If(Expr2, Expr3, false), false) Expr1 && Expr2 && Expr3