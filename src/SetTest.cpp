#include <type_traits>
#include "exec.hpp"
#include "meta-basics.hpp"
#include "set.hpp"

TC_BEGIN(Set, 1)
{
    using Set1 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::SetContains(std::true_type, Set1)>::type;
    static_assert(Result::value, "Set1 must contain true_type!");
}

TC_BEGIN(Set, 2)
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

TC_BEGIN(Set, 3)
{
    using Set1 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::SetInsert(int, Set1)>::type;
    static_assert(!std::is_same_v<Set1, Result>, "Result now has int!");

    using Set2 = sia::meta::detail::Set<std::false_type, std::true_type>;
    using Result2 = sia::meta::Exec<sia::meta::detail::SetInsert(std::true_type, Set1)>::type;
    static_assert(std::is_same_v<Set2, Result2>, "Result should not have true_type again!");
}
