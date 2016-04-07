#ifndef HEADER_AETEE_MATH_SUGAR_OPERATOR_C_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_OPERATOR_C_INCLUDED

namespace aetee {

namespace detail {

template <typename ForwardIt>
static constexpr std::size_t my_stoull(ForwardIt lo, ForwardIt hi)
{
    std::size_t retval = 0;
    while (lo != hi) {
        retval = (retval * 10) + *lo++;
    }
    return retval;
}

static constexpr bool my_isdigit(char c)
{
    return '0' <= c <= '9';
}

} /*namespace detail*/;

template <char... C>
constexpr auto operator""_c()
{
    static_assert((detail::my_isdigit(C) && ...));
    constexpr std::size_t str[]{(C - '0')...};
    return idx_c<detail::my_stoull(str, str + sizeof...(C))>;
}

} /*namespace aetee*/;

#endif
