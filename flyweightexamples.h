#pragma once

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "flyweighttypes.h"

namespace
{
    constexpr std::hash<std::string> keyHasher{std::hash<std::string>{}};
    const std::string stringA{"stringA"};
    const std::string stringB{"stringB"};
    const std::string stringC{"stringC"};
    const size_t stringAHash{keyHasher(stringA)};
    const size_t stringBHash{keyHasher(stringB)};
    const size_t stringCHash{keyHasher(stringC)};
    constexpr int32_t loopCount{500'000};
}

TEST_CASE("Flyweight - Unit Test - GetFlyweightType")
{
    FlyweightFactory<FlyweightType> factory{};

    const Type typeA{factory.GetFlyweight(stringA), 1};
    const Type typeB{factory.GetFlyweight(stringB), 2};
    const Type typeBB{factory.GetFlyweight(stringB), 3};
    const Type typeC{factory.GetFlyweight(stringC), 4};

    REQUIRE(typeA.GetNonsharedValue() == 1);
    REQUIRE(typeB.GetNonsharedValue() == 2);
    REQUIRE(typeBB.GetNonsharedValue() == 3);
    REQUIRE(typeC.GetNonsharedValue() == 4);

    REQUIRE(typeA.GetFlyweight()->GetSharedValue() != typeC.GetFlyweight()->GetSharedValue());
    REQUIRE(typeA.GetFlyweight()->GetSharedValue() != typeB.GetFlyweight()->GetSharedValue());
    REQUIRE(typeB.GetFlyweight()->GetSharedValue() == typeBB.GetFlyweight()->GetSharedValue());
}

TEST_CASE("Flyweight - Unit Test - GetFlyweightType Prehashed")
{
    FlyweightFactory<FlyweightType> factory{};

    const Type typeA{factory.GetFlyweight(stringAHash), 1};
    const Type typeB{factory.GetFlyweight(stringBHash), 2};
    const Type typeBB{factory.GetFlyweight(stringBHash), 3};
    const Type typeC{factory.GetFlyweight(stringCHash), 4};

    REQUIRE(typeA.GetNonsharedValue() == 1);
    REQUIRE(typeB.GetNonsharedValue() == 2);
    REQUIRE(typeBB.GetNonsharedValue() == 3);
    REQUIRE(typeC.GetNonsharedValue() == 4);

    REQUIRE(typeA.GetFlyweight()->GetSharedValue() != typeC.GetFlyweight()->GetSharedValue());
    REQUIRE(typeA.GetFlyweight()->GetSharedValue() != typeB.GetFlyweight()->GetSharedValue());
    REQUIRE(typeB.GetFlyweight()->GetSharedValue() == typeBB.GetFlyweight()->GetSharedValue());
}

TEST_CASE("Flyweight - Benchmark - GetFlyweightType")
{
    FlyweightFactory<FlyweightType> factory{};

    BENCHMARK("Benchmark")
    {
        for(int32_t i{0}; i != loopCount; ++i)
        {
            const Type typeA{factory.GetFlyweight(stringA), i};
            const Type typeB{factory.GetFlyweight(stringB), i};
            const Type typeC{factory.GetFlyweight(stringC), i};
        }
    };

    BENCHMARK("Benchmark - Prehashed")
    {
        for(int32_t i{0}; i != loopCount; ++i)
        {
            const Type typeA{factory.GetFlyweight(stringAHash), i};
            const Type typeB{factory.GetFlyweight(stringBHash), i};
            const Type typeC{factory.GetFlyweight(stringCHash), i};
        }
    };
}
