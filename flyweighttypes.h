#pragma once
#include <cstdint>
#include <unordered_map>

class FlyweightType
{
public:
    explicit constexpr FlyweightType(const int32_t sharedValue)
        : m_SharedValue{sharedValue}
    {
    }

    [[nodiscard]] int32_t GetSharedValue() const
    {
        return m_SharedValue;
    }
private:
    int32_t m_SharedValue{};
};

class Type
{
public:
    explicit Type(const std::shared_ptr<const FlyweightType> flyweight, const int32_t nonsharedValue)
        : m_Flyweight{flyweight}
        , m_NonsharedValue{nonsharedValue}
    {
    }

    [[nodiscard]] std::shared_ptr<const FlyweightType> GetFlyweight() const
    {
        return m_Flyweight;
    }

    [[nodiscard]] int32_t GetNonsharedValue() const
    {
        return m_NonsharedValue;
    }
private:
    std::shared_ptr<const FlyweightType> m_Flyweight{};
    int32_t m_NonsharedValue{};
};

template<typename T>
class FlyweightFactory
{
public:
    [[nodiscard]] std::shared_ptr<const T> GetFlyweight(const std::string& flyweightIdentifier)
    {
        return GetFlyweight(ms_KeyHasher(flyweightIdentifier));
    }

    [[nodiscard]] std::shared_ptr<const T> GetFlyweight(const size_t flyweightIdentifierHash)
    {
        if (auto search{m_FlyweightCache.find(flyweightIdentifierHash)}; search != std::end(m_FlyweightCache))
        {
            return search->second;
        }

        std::shared_ptr<const T> flyweightType{std::make_shared<const T>(++m_NextSharedValue)};
        m_FlyweightCache.insert({flyweightIdentifierHash, flyweightType});
        return flyweightType;
    }

private:
    static constexpr std::hash<std::string> ms_KeyHasher{std::hash<std::string>{}};
    int32_t m_NextSharedValue{0};
    std::unordered_map<size_t, std::shared_ptr<const T>> m_FlyweightCache{};
};
