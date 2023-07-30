#pragma once

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>
#include <type_traits>
#include <utility>
#include "exec.hpp"
namespace sia::meta::detail
{

// TODO(selcuk): List of things to be implemented!
// - IsInVector
// - VectorSize
// - PushFront
// - PushBack
// - ConcatVectors
// - VectorRemoveFirstN
// - VectorEndsWith

template <typename... Types>
struct Vector
{
};

struct IsInVector
{
    template <typename T, typename V>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Vector<Ts...>>
    {
        using type = std::bool_constant<(std::is_same_v<T, Ts> || ...)>;
    };
};

struct VectorSize
{
    template <typename... Ts>
    struct apply;

    template <typename... Ts>
    struct apply<Vector<Ts...>>
    {
        using type = std::integral_constant<std::size_t, sizeof...(Ts)>;
    };
};

struct PushBack
{
    template <typename T, typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Vector<Ts...>>
    {
        using type = Vector<Ts..., T>;
    };
};

struct PushFront
{
    template <typename T, typename... Ts>
    struct apply;

    template <typename T, typename... Ts>
    struct apply<T, Vector<Ts...>>
    {
        using type = Vector<T, Ts...>;
    };
};

struct ConcatVectors
{
    template <typename... Ts>
    struct apply;

    template <typename... Ts, typename... Us>
    struct apply<Vector<Ts...>, Vector<Us...>>
    {
        using type = Vector<Ts..., Us...>;
    };
};

struct DummyTypeBase
{
};

struct DecrementIntegral
{
    template <typename N>
    struct apply
    {
        using type = std::integral_constant<N, N::value - 1>;
    };
};

struct GenerateVectorSequence
{
    template <std::uint32_t K, typename... Ts>
    struct generate;

    template <std::uint32_t K, typename... Ts>
    struct generate<K, Vector<Ts...>>
    {
        using type = std::conditional_t<
            (K > 0),
            typename generate<K - 1, typename sia::meta::Exec<PushBack(DummyTypeBase, Vector<Ts...>)>::type>::type,
            Vector<Ts...>>;
    };

    template <typename... Ts>
    struct generate<0, Vector<Ts...>>
    {
        using type = Vector<Ts...>;
    };

    template <typename N>
    struct apply
    {
        using type = typename generate<N::value, Vector<>>::type;
    };
};

template <typename... T>
using AlwaysVoidPtr = void*;

struct VectorRemoveFirstN
{
    template <typename T, typename... Ts>
    struct apply;

    template <typename N, typename... Ts>
    struct apply<N, Vector<Ts...>>
    {
        private:
        template <typename... Indexes, typename... Tail>
        static Vector<Tail...> removeFirstNElementHelper(AlwaysVoidPtr<Indexes>..., Tail*...);

        template <typename... Params>
        struct func;

        template <typename... Indexes, typename... Params>
        struct func<Vector<Indexes...>, Vector<Params...>>
        {
            using type = decltype(removeFirstNElementHelper<Indexes...>((static_cast<Params*>(nullptr))...));
        };

        public:
        using type =
            typename func<typename GenerateVectorSequence::generate<N::value, Vector<>>::type, Vector<Ts...>>::type;
    };
};

struct VectorEndsWith
{
    template <typename V, typename T>
    struct apply
    {
        using type = typename sia::meta::Exec<VectorRemoveFirstN(
            std::integral_constant<std::uint32_t, sia::meta::Exec<VectorSize(V)>::type::value - 1>, V)>::type;
    };
};

struct VectorGetNThElement
{
    private:
    template <int n, typename... Ts>
    struct apply_helper;

    template <int n, typename T, typename... Ts>
    struct apply_helper<n, T, Ts...>
    {
        using type = typename apply_helper<n - 1, Ts...>::type;
    };

    template <typename T, typename... Ts>
    struct apply_helper<0, T, Ts...>
    {
        using type = T;
    };

    public:
    template <typename N, typename... Ts>
    struct apply;

    template <typename N, typename... Ts>
    struct apply<N, Vector<Ts...>>
    {
        using type = typename apply_helper<N::value, Ts...>::type;
    };
};

struct FindMax
{
    template <typename... Ts>
    struct apply
    {
        template <typename... Items>
        struct apply_helper;

        template <typename MaxT, typename Item, typename... Tail>
        struct apply_helper<MaxT, Item, Tail...>
        {
            using type = std::conditional_t<(MaxT::value < Item::value), typename apply_helper<Item, Tail...>::type,
                                            typename apply_helper<MaxT, Tail...>::type>;
        };

        template <typename MaxT>
        struct apply_helper<MaxT>
        {
            using type = MaxT;
        };

        using type = typename apply_helper<Ts...>::type;
    };
};
}  // namespace sia::meta::detail

namespace sia::meta
{
template <typename... Ts>
using Vector = sia::meta::detail::Vector<Ts...>;
}
