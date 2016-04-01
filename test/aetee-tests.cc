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
    auto expected = tupify(1, 2, 3);
    auto actual = append(tupify(1, 2), 3);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Prepend)
{
    auto expected = tupify(1, 2, 3);
    auto actual = prepend(tupify(2, 3), 1);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Fold)
{
    auto expected = 15;
    auto actual = fold(tupify(1, 2, 3, 4, 5), 0, std::plus<>{});
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Zip)
{
    auto expected = tupify(tupify(1, 2), tupify(3, 4), tupify(5, 6));
    auto actual = zip(tupify(1, 3, 5), tupify(2, 4, 6));
    ASSERT_EQ(length(expected), length(actual));
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Reverse)
{
    auto expected = tupify(5, 4, 3, 2, 1);
    auto actual = reverse(tupify(1, 2, 3, 4, 5));
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
        auto expected = tupify(1, 2);
        auto actual = take(tupify(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
    { // takeBack
        auto expected = tupify(4, 5);
        auto actual = takeBack(tupify(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
}

TEST(Aetee, Drop)
{
    { // dropFront
        auto expected = tupify(3, 4, 5);
        auto actual = drop(tupify(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
    { // dropBack
        auto expected = tupify(1, 2, 3);
        auto actual = dropBack(tupify(1, 2, 3, 4, 5), 2_c);
        ASSERT_EQ(length(expected), length(actual));
        EXPECT_EQ(expected, actual);
    }
}

TEST(Aetee, Compose)
{
    auto foo = [](auto f, auto g) { return f + g; };
    auto bar = [](auto d, auto e) { return tupify(d % e, d / e); };
    auto baz = [](auto a, auto b, auto c) { return tupify(a + b, a - c); };
    EXPECT_EQ(compose(foo, bar, baz)(3, 2, 1), 3);
}

TEST(Aetee, Flatten)
{
    auto tup = tupify(tupify(tupify(0, tupify(1, 2), 3), tupify(4, 5)), tupify(6));
    auto expected = tupify(tupify(0, tupify(1, 2), 3), tupify(4, 5), 6);
    auto actual = flatten(tup);

    EXPECT_EQ(expected, actual);
}

TEST(Aetee, FlattenRecursive)
{
    auto tup = tupify(tupify(tupify(0, tupify(1, 2), 3), tupify(4, 5)), tupify(6));
    auto expected = tupify(0, 1, 2, 3, 4, 5, 6);
    auto actual = flatten.recursive(tup);

    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Slice)
{
    auto tup = tupify(0, 1, 2, 3, 4, 5, 6, 7);

    EXPECT_EQ(tupify(0, 3, 6), slice(tup, 0_c, 8_c, 3_c));
    EXPECT_EQ(tupify(2, 3), slice(tup, 2_c, 4_c));
    EXPECT_EQ(tupify(2), slice(tup, 2_c, 4_c, 2_c));
    EXPECT_EQ(tupify(0, 2, 4, 6), slice(tup, 0_c, 8_c, 2_c));
    EXPECT_EQ(tupify(1, 3, 5, 7), slice(tup, 1_c, 8_c, 2_c));
}

TEST(Aetee, Value)
{
    auto x = 1_c;
    auto y = 2_c;

    EXPECT_EQ(1, value(x));
    EXPECT_EQ(2, value(y));
    EXPECT_EQ(3, value(x+y));
    EXPECT_EQ(4, value(4));
}
