#include "detail/vector.hpp"
#include "detail/meta-basics.hpp"
#include <gtest/gtest.h>

using namespace sia::meta::detail;

struct DummyType
{
};

struct EmptyClassType
{
};


TEST(Vector, 1)
{
    using V1 = sia::meta::detail::Vector<std::true_type, std::false_type>;
    using Result = sia::meta::Exec<sia::meta::detail::IsInVector(std::false_type, V1)>::type;
    static_assert(Result::value, "false_type must be in vector!");

    using Result1 = sia::meta::Exec<IsInVector(DummyType, V1)>::type;
    static_assert(!Result1::value, "DummyType should not be in vector!");
}

TEST(Vector, 2)
{
    using V1 = sia::meta::detail::Vector<DummyType, EmptyClassType, std::true_type, std::false_type>;
    using Result = sia::meta::Exec<sia::meta::detail::VectorSize(V1)>::type;
    static_assert(Result::value == 4, "V1 size must be four!");
}

TEST(Vector, 3)
{
    using V1 = sia::meta::detail::Vector<EmptyClassType, std::true_type, std::false_type>;
    using Result = sia::meta::Exec<sia::meta::detail::PushBack(DummyType, V1)>::type;
    using Size1 = sia::meta::Exec<VectorSize(V1)>::type;
    using Size2 = sia::meta::Exec<VectorSize(Result)>::type;
    static_assert(Size1::value + 1 == Size2::value, "V1 size + 1 must be equal to Result size!");
}

TEST(Vector, 4)
{
    using V1 = sia::meta::detail::Vector<EmptyClassType, std::true_type, std::false_type>;
    using Result = sia::meta::Exec<sia::meta::detail::PushFront(DummyType, V1)>::type;
    using Size1 = sia::meta::Exec<VectorSize(V1)>::type;
    using Size2 = sia::meta::Exec<VectorSize(Result)>::type;
    static_assert(Size1::value + 1 == Size2::value, "V1 size + 1 must be equal to Result size!");
}

TEST(Vector, 5)
{
    using V1 = sia::meta::detail::Vector<EmptyClassType, std::true_type, std::false_type>;
    using V2 = sia::meta::detail::Vector<EmptyClassType, DummyType>;
    using Result = sia::meta::Exec<sia::meta::detail::ConcatVectors(V1, V2)>::type;
    using Size1 = sia::meta::Exec<VectorSize(V1)>::type;
    using Size2 = sia::meta::Exec<VectorSize(V2)>::type;
    using Size3 = sia::meta::Exec<VectorSize(Result)>::type;
    static_assert(Size3::value == (Size1::value + Size2::value), "V1 + V2 must be equal to Result size!");
}

TEST(Vector, 6)
{
    using IndexSequence = sia::meta::detail::GenerateVectorSequence::generate<2, Vector<>>::type;
    using Result = sia::meta::Exec<VectorSize(IndexSequence)>::type;
    static_assert(Result::value == 2, "Generate vector sequence must have 2 item!");
}

TEST(Vector, 7)
{
    using V1 = sia::meta::detail::Vector<std::false_type, DummyType, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::VectorRemoveFirstN(sia::meta::Integer<1>, V1)>::type;
    using ResultSize = sia::meta::Exec<sia::meta::detail::VectorSize(Result)>::type;
    static_assert(ResultSize::value == 2, "Remaining number of items must be 2!");
}

TEST(Vector, 8)
{
    using V1 = sia::meta::detail::Vector<std::false_type, DummyType, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::VectorEndsWith(V1, std::true_type)>::type;
    using Expected = sia::meta::detail::Vector<std::true_type>;
    static_assert(std::is_same_v<Result, Expected>, "V1 must end with true_type!");
}

TEST(Vector, 9)
{
    using V1 = sia::meta::detail::Vector<std::false_type, DummyType, std::true_type>;
    using Result = sia::meta::Exec<sia::meta::detail::VectorGetNThElement(sia::meta::Integer<1>, V1)>::type;
    static_assert(std::is_same_v<DummyType, Result>, "Second item must be DummyType!");
}

TEST(Vector, 10)
{
    using Result = sia::meta::Exec<sia::meta::detail::FindMax(std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 3>)>::type;
    static_assert(Result::value == 3, "Max item must be 3!");
}

