#pragma once

namespace sia::meta::detail
{
template <typename FirstT, typename SecondT>
struct Pair
{
    using First = FirstT;
    using Second = SecondT;
};

struct MakePair
{
    template <typename First, typename Second>
    struct apply
    {
        using type = Pair<First, Second>;
    };
};

struct GetFirst
{
    template <typename... Ts>
    struct apply;

    template <typename First, typename Second>
    struct apply<Pair<First, Second>>
    {
        using type = First;
    };
};

struct GetSecond
{
    template <typename... Ts>
    struct apply;

    template <typename First, typename Second>
    struct apply<Pair<First, Second>>
    {
        using type = Second;
    };
};

}  // namespace sia::meta::detail
