#include "detail/set.hpp"
#include <gtest/gtest.h>

TEST(Set, 1)
{
    using Set1 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::SetContains(std::true_type, Set1)>::type;
    static_assert(Result::value, "Set1 must contain true_type!");
}

TEST(Set, 2)
{
    using Set1 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::SetCheckIfUnique(Set1)>::type;
    static_assert(Result::value, "");

    using Set2 = sia::meta::detail::Set<>;
    using Result2 = sia::meta::Exec<sia::meta::detail::SetCheckIfUnique(Set2)>::type;
    static_assert(Result2::value, "");

    using Set3 = sia::meta::detail::Set<std::false_type>;
    using Result3 = sia::meta::Exec<sia::meta::detail::SetCheckIfUnique(Set3)>::type;
    static_assert(Result3::value, "");

    using Set4 = sia::meta::detail::Set<std::false_type, std::false_type>;
    using Result4 = sia::meta::Exec<sia::meta::detail::SetCheckIfUnique(Set4)>::type;
    static_assert(!Result4::value, "");
}

TEST(Set, 3)
{
    using Set1 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::SetInsert(int, Set1)>::type;
    static_assert(!std::is_same_v<Set1, Result>, "Result now has int!");

    using Set2 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result2 = sia::meta::Exec<sia::meta::detail::SetInsert(std::true_type, Set1)>::type;
    static_assert(std::is_same_v<Set2, Result2>, "Result should not have true_type again!");
}

TEST(Set, 4)
{
    using Set1 = sia::meta::detail::Set<std::false_type, std::true_type, int>;
    using Result = sia::meta::detail::SetRemove::apply<int, Set1>::type;

    using Set1_removed = sia::meta::detail::Set<std::false_type, std::true_type>;
    static_assert(std::is_same_v<Result, Set1_removed>, "");

    using Result2 = sia::meta::detail::SetRemove::apply<std::true_type, Set1>::type;
    using Set2_remove = sia::meta::detail::Set<std::false_type, int>;
    static_assert(std::is_same_v<Result2, Set2_remove>, "");

    using Result3 = sia::meta::detail::SetRemove::apply<std::false_type, Set1>::type;
    using Set3_remove = sia::meta::detail::Set<std::true_type, int>;
    static_assert(std::is_same_v<Result3, Set3_remove>, "");

    using Result4 = sia::meta::detail::SetRemove::apply<float, Set1>::type;
    using Set4_remove = sia::meta::detail::Set<std::false_type, std::true_type, int>;
    static_assert(std::is_same_v<Result4, Set4_remove>, "");

    using EmptySet = sia::meta::detail::Set<>;
    using Result5 = sia::meta::detail::SetRemove::apply<int, EmptySet>::type;
    static_assert(std::is_same_v<Result5, EmptySet>, "");
}

