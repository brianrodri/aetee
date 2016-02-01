#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <aetee/aetee.h>
#include <string>
#include <experimental/tuple>
#include <functional>

TEST(Aetee, TypeConstant)
{
    auto int_c = aetee::type_c<int>;
    auto string_c = aetee::type_c<std::string>;
    auto isPOD = [](auto t) { return std::is_pod<typename decltype(t)::type>::value; };
    bool int_is_pod = isPOD(int_c);
    bool string_is_pod = isPOD(string_c);
    EXPECT_TRUE(int_is_pod);
    EXPECT_FALSE(string_is_pod);
}

TEST(Aetee, Append)
{
    using aetee::operator<<;
    auto expected = std::make_tuple(1, 2, 3);
    auto actual = aetee::append(std::make_tuple(1, 2), 3);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Prepend)
{
    auto expected = std::make_tuple(1, 2, 3);
    auto actual = aetee::prepend(std::make_tuple(2, 3), 1);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Fold)
{
    auto expected = 10;
    auto actual = aetee::fold(std::make_tuple(1, 2, 3, 4), 0, std::plus<>{});
    EXPECT_EQ(expected, actual);
}
