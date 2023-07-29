#include <type_traits>
#include "detail/exec.hpp"
#include "detail/meta-basics.hpp"
#include "detail/priority-queue.hpp"

TC_BEGIN(PQ, 1)
{
    using Q1 = sia::meta::detail::PriorityQueue<std::integral_constant<int, 3>, std::integral_constant<int, 1>,
                                                std::integral_constant<int, 2>>;

    using Result = sia::meta::Exec<sia::meta::detail::PQPush(std::integral_constant<int, 4>, Q1)>::type;

    static_assert(Result::top::value == 4, "Maximum item must be 4!");
}

TC_BEGIN(PQ, 2)
{
    using Q1 = sia::meta::detail::PriorityQueue<std::integral_constant<int, 3>, std::integral_constant<int, 1>,
                                                std::integral_constant<int, 2>>;
    using Result = sia::meta::Exec<sia::meta::detail::PQPop(Q1)>::type;

    using Expected = sia::meta::detail::PriorityQueue<std::integral_constant<int, 1>, std::integral_constant<int, 2>>;
    
    static_assert(std::is_same_v<Result, Expected>, "Top priority 3 must be removed from the queue!");
}

TC_BEGIN(PQ, 3)
{
    using Q1 = sia::meta::detail::PriorityQueue<std::integral_constant<int, 3>, std::integral_constant<int, 1>,
                                                std::integral_constant<int, 2>>;
    
    using Result = sia::meta::Exec<sia::meta::detail::PQTop(Q1)>::type;

    static_assert(Result::value == 3);
}
