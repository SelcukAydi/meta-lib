#pragma once

#include "meta-basics.hpp"

namespace sia::meta::impl
{
template <typename MetaFunc, typename... MetaExpr>
struct ExecImpl;

template <typename MetaFunc>
struct ExecImpl<MetaFunc>
{
    using type = MetaFunc;
};

template <typename MetaFunc, typename... MetaExpr>
struct ExecImpl<MetaFunc(MetaExpr...)>
{
    using type = typename ExecImpl<typename MetaFunc::template apply<typename ExecImpl<MetaExpr>::type...>::type>::type;
};

template <typename MetaFunc, typename... MetaExpr>
struct ExecImpl<MetaFunc (*)(MetaExpr...)>
{
    using type = typename ExecImpl<typename MetaFunc::template apply<typename ExecImpl<MetaExpr>::type...>::type>::type;
};

template <typename BoolConstant, typename ThenMetaFunc, typename ElseMetaFunc>
struct ExecIfImpl;

template <typename ThenMetaFunc, typename ElseMetaFunc>
struct ExecIfImpl<std::true_type, ThenMetaFunc, ElseMetaFunc>
{
    using type = typename ExecImpl<ThenMetaFunc>::type;
};

template <typename ThenMetaFunc, typename ElseMetaFunc>
struct ExecIfImpl<std::false_type, ThenMetaFunc, ElseMetaFunc>
{
    using type = typename ExecImpl<ElseMetaFunc>::type;
};

template <typename CondMetaFunc, typename ThenMetaFunc, typename ElseMetaFunc>
struct ExecImpl<sia::meta::If(CondMetaFunc, ThenMetaFunc, ElseMetaFunc)>
{
    using type = typename ExecImpl<
        typename ExecIfImpl<typename ExecImpl<CondMetaFunc>::type, ThenMetaFunc, ElseMetaFunc>::type>::type;
};

template <typename CondMetaFunc, typename ThenMetaFunc, typename ElseMetaFunc>
struct ExecImpl<sia::meta::If (*)(CondMetaFunc, ThenMetaFunc, ElseMetaFunc)>
{
    using type = typename ExecImpl<
        typename ExecIfImpl<typename ExecImpl<CondMetaFunc>::type, ThenMetaFunc, ElseMetaFunc>::type>::type;
};

template <typename MetaFunc, typename ElseMetaExpr>
struct ExecImplPropagateError
{
    using type = typename ExecImpl<ElseMetaExpr>::type;
};

template <typename ErrorTag, typename... ErrorArgs, typename ElseMetaExpr>
struct ExecImplPropagateError<Error<ErrorTag, ErrorArgs...>, ElseMetaExpr>
{
    using type = Error<ErrorTag, ErrorArgs...>;
};

template <typename MetaFuncThatMayThrow, typename ElseMetaExpr>
struct ExecImpl<sia::meta::PropagateError(MetaFuncThatMayThrow, ElseMetaExpr)>
{
    using type = typename ExecImplPropagateError<typename ExecImpl<MetaFuncThatMayThrow>::type, ElseMetaExpr>::type;
};

template <typename MetaFuncThatMayThrow, typename ElseMetaExpr>
struct ExecImpl<sia::meta::PropagateError(*)(MetaFuncThatMayThrow, ElseMetaExpr)>
{
    using type = typename ExecImplPropagateError<typename ExecImpl<MetaFuncThatMayThrow>::type, ElseMetaExpr>::type;
};

}  // namespace sia::meta::impl

namespace sia::meta
{
template <typename MetaFunc, typename... MetaExpr>
using Exec = impl::ExecImpl<MetaFunc, MetaExpr...>;
}