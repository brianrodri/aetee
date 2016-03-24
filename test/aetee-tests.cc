#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <aetee/aetee.h>
#include <string>
#include <experimental/tuple>
#include <functional>

using namespace aetee;


TEST(Aetee, TypeConstant)
{
    auto int_ct = type_c<int>;
    auto string_ct = type_c<std::string>;
    auto isPOD = [](auto t) { return std::is_pod<typename decltype(t)::type>::value; };
    bool int_is_pod = isPOD(int_ct);
    bool string_is_pod = isPOD(string_ct);
    EXPECT_TRUE(int_is_pod);
    EXPECT_FALSE(string_is_pod);
}

TEST(Aetee, TypeSequence)
{
    auto l = type_sequence_c<int, float, double>;
    EXPECT_EQ(length(l), 3);
}

TEST(Aetee, Append)
{
    auto expected = std::make_tuple(1, 2, 3);
    auto actual = append(std::make_tuple(1, 2), 3);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Prepend)
{
    auto expected = std::make_tuple(1, 2, 3);
    auto actual = prepend(std::make_tuple(2, 3), 1);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Fold)
{
    auto expected = 15;
    auto actual = fold(std::make_tuple(1, 2, 3, 4, 5), 0, std::plus<>{});
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Zip)
{
    auto expected = std::make_tuple(std::make_tuple(1, 2), std::make_tuple(3, 4), std::make_tuple(5, 6));
    auto actual = zip(std::make_tuple(1, 3, 5), std::make_tuple(2, 4, 6));
    ASSERT_EQ(length(expected), length(actual));
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Reverse)
{
    auto expected = std::make_tuple(5, 4, 3, 2, 1);
    auto actual = reverse(std::make_tuple(1, 2, 3, 4, 5));
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Take)
{
    { // takeFront
        auto expected = std::make_tuple(1, 2);
        auto actual = take(std::make_tuple(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
    { // takeBack
        auto expected = std::make_tuple(4, 5);
        auto actual = takeBack(std::make_tuple(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
}

TEST(Aetee, Drop)
{
    { // dropFront
        auto expected = std::make_tuple(3, 4, 5);
        auto actual = drop(std::make_tuple(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
    { // dropBack
        auto expected = std::make_tuple(1, 2, 3);
        auto actual = dropBack(std::make_tuple(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
}
