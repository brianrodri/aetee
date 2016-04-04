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
    EXPECT_EQ(length(l), 3_c);
}

TEST(Aetee, Append)
{
    auto expected = tupify(1_c, 2_c, 3_c);
    auto actual = append(tupify(1_c, 2_c), 3_c);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Prepend)
{
    auto expected = tupify(1_c, 2_c, 3_c);
    auto actual = prepend(tupify(2_c, 3_c), 1_c);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Fold)
{
    auto expected = 15_c;
    auto actual = fold(tupify(1_c, 2_c, 3_c, 4_c, 5_c), 0_c, std::plus<>{});
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Zip)
{
    auto expected = tupify(tupify(1_c, 2_c), tupify(3_c, 4_c), tupify(5_c, 6_c));
    auto actual = zip(tupify(1_c, 3_c, 5_c), tupify(2_c, 4_c, 6_c));
    ASSERT_EQ(length(expected), length(actual));
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Reverse)
{
    auto expected = tupify(5_c, 4_c, 3_c, 2_c, 1_c);
    auto actual = reverse(tupify(1_c, 2_c, 3_c, 4_c, 5_c));
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Clamp)
{
    //                   lo   hi   clampee
    EXPECT_EQ(1_c, clamp(1_c, 3_c, 0_c));
    EXPECT_EQ(2_c, clamp(1_c, 3_c, 2_c));
    EXPECT_EQ(3_c, clamp(1_c, 3_c, 4_c));
}

TEST(Aetee, Take)
{
    { // takeFront
        auto expected = tupify(1_c, 2_c);
        auto actual = take(tupify(1_c, 2_c, 3_c, 4_c, 5_c), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
    { // takeBack
        auto expected = tupify(4_c, 5_c);
        auto actual = takeBack(tupify(1_c, 2_c, 3_c, 4_c, 5_c), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
}

TEST(Aetee, Drop)
{
    { // dropFront
        auto expected = tupify(3_c, 4_c, 5_c);
        auto actual = drop(tupify(1_c, 2_c, 3_c, 4_c, 5_c), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
    { // dropBack
        auto expected = tupify(1_c, 2_c, 3_c);
        auto actual = dropBack(tupify(1_c, 2_c, 3_c, 4_c, 5_c), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
}

TEST(Aetee, Compose)
{
    auto foo = [](auto f, auto g) { return f + g; };
    auto bar = [](auto d, auto e) { return tupify(d % e, d / e); };
    auto baz = [](auto a, auto b, auto c) { return tupify(a + b, a - c); };
    EXPECT_EQ(compose(foo, bar, baz)(3_c, 2_c, 1_c), 3_c);
}

TEST(Aetee, Flatten)
{
    auto tup = tupify(tupify(tupify(0_c, tupify(1_c, 2_c), 3_c), tupify(4_c, 5_c)), tupify(6_c));
    auto expected = tupify(tupify(0_c, tupify(1_c, 2_c), 3_c), tupify(4_c, 5_c), 6_c);
    auto actual = flatten(tup);

    EXPECT_EQ(expected, actual);
}

TEST(Aetee, FlattenRecursive)
{
    auto tup = tupify(tupify(tupify(0_c, tupify(1_c, 2_c), 3_c), tupify(4_c, 5_c)), tupify(6_c));
    auto expected = tupify(0_c, 1_c, 2_c, 3_c, 4_c, 5_c, 6_c);
    auto actual = flatten.recursive(tup);

    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Slice)
{
    auto tup = tupify(0_c, 1_c, 2_c, 3_c, 4_c, 5_c, 6_c, 7_c);

    EXPECT_EQ(tupify(0_c, 3_c, 6_c), slice(tup, 0_c, 8_c, 3_c));
    EXPECT_EQ(tupify(2_c, 3_c), slice(tup, 2_c, 4_c));
    EXPECT_EQ(tupify(2_c), slice(tup, 2_c, 4_c, 2_c));
    EXPECT_EQ(tupify(0_c, 2_c, 4_c, 6_c), slice(tup, 0_c, 8_c, 2_c));
    EXPECT_EQ(tupify(1_c, 3_c, 5_c, 7_c), slice(tup, 1_c, 8_c, 2_c));
}

TEST(Aetee, Value)
{
    auto x = 1_c;
    auto y = 2_c;

    EXPECT_EQ(1_c, value(x));
    EXPECT_EQ(2_c, value(y));
    EXPECT_EQ(3_c, value(x + y));
}
