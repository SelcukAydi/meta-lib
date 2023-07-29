#pragma once

#include <type_traits>

namespace sia::meta::detail
{
template <int N>
struct Integral
{
    using type = std::integral_constant<int, N>;
};

struct IntegralIncrement
{
    template <typename... Ts>
    struct apply;

    template <int N>
    struct apply<Integral<N>>
    {
        using type = Integral<N + 1>;
    };
};

struct IntegralDecrement
{
    template <typename... Ts>
    struct apply;

    template <int N>
    struct apply<Integral<N>>
    {
        using type = Integral<N - 1>;
    };
};

struct IntegralAdd
{
    template <typename... Ts>
    struct apply;

    template <int M, int N>
    struct apply<Integral<M>, Integral<N>>
    {
        using type = Integral<M + N>;
    };
};

struct IntegralSub
{
    template<typename... Ts>
    struct apply;

    template<int M, int N>
    struct apply<Integral<M>, Integral<N>>
    {
        using type = Integral<M - N>;
    };
};

struct IntegralDiv
{
    template<typename... Ts>
    struct apply;

    template<int N, int M>
    struct apply<Integral<N>, Integral<M>>
    {
        static_assert(M != 0, "Zero division error!");

        using type = Integral<N / M>;
    };
};

struct IntegralMul
{
    template<typename... Ts>
    struct apply;

    template<int N, int M>
    struct apply<Integral<N>, Integral<M>>
    {
        using type = Integral<N * M>;
    };
};

template <int N, int M>
constexpr typename IntegralAdd::apply<Integral<N>, Integral<M>>::type operator+(Integral<N>, Integral<M>)
{
    return typename IntegralAdd::apply<Integral<N>, Integral<M>>::type{}; 
}


template <int N, int M>
constexpr typename IntegralSub::apply<Integral<N>, Integral<M>>::type operator-(Integral<N>, Integral<M>)
{
    return typename IntegralSub::apply<Integral<N>, Integral<M>>::type{}; 
}


template <int N, int M>
constexpr typename IntegralDiv::apply<Integral<N>, Integral<M>>::type operator/(Integral<N>, Integral<M>)
{
    return typename IntegralDiv::apply<Integral<N>, Integral<M>>::type{}; 
}


template <int N, int M>
constexpr typename IntegralMul::apply<Integral<N>, Integral<M>>::type operator*(Integral<N>, Integral<M>)
{
    return typename IntegralMul::apply<Integral<N>, Integral<M>>::type{}; 
}


template <int N>
constexpr typename IntegralIncrement::apply<Integral<N>>::type operator++(Integral<N>, int)
{
    return typename IntegralIncrement::apply<Integral<N>>::type{}; 
}


template <int N>
constexpr typename IntegralDecrement::apply<Integral<N>>::type operator--(Integral<N>, int)
{
    return typename IntegralDecrement::apply<Integral<N>>::type{}; 
}


template <int N>
constexpr typename IntegralIncrement::apply<Integral<N>>::type operator++(Integral<N>)
{
    return typename IntegralIncrement::apply<Integral<N>>::type{}; 
}


template <int N>
constexpr typename IntegralDecrement::apply<Integral<N>>::type operator--(Integral<N>)
{
    return typename IntegralDecrement::apply<Integral<N>>::type{}; 
}

template<int N>
auto IntegralVar = Integral<N>{};

}  // namespace sia::meta::detail
