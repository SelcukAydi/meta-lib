#include <type_traits>
#include "exec.hpp"
#include "meta-basics.hpp"
#include "priority-queue.hpp"

TC_BEGIN(PQ, 1)
{
    using Q1 = sia::meta::detail::PriorityQueue<std::integral_constant<int, 3>, std::integral_constant<int, 1>,
                                                std::integral_constant<int, 2>>;

    using Result = sia::meta::Exec<sia::meta::detail::PQPush(std::integral_constant<int, 4>, Q1)>::type;

    static_assert(Result::top::value == 4, "Maximum item must be 4!");
}
