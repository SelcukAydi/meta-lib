#pragma once

#include "detail/meta-basics.hpp"

struct StandartErrorTag
{
    template <typename C>
    struct apply
    {
        using type = sia::meta::AlwaysFalse<C>;
    };
};

struct NotDefaultConstructibleErrorTag
{
    template <typename C>
    struct apply
    {
        static_assert(sia::meta::AlwaysFalse<C>::value, "Class 'C' is not default constructible!");
        using type = sia::meta::AlwaysFalse<C>;
    };
};
