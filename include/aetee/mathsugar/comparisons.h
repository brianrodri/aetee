#ifndef HEADER_AETEE_MATHSUGAR_COMPARISONS_H_INCLUDED
#define HEADER_AETEE_MATHSUGAR_COMPARISONS_H_INCLUDED
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

struct equalToFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a == b)>;
    }
} /*struct equalToFunctor*/;

struct notEqualToFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a != b)>;
    }
} /*struct notEqualToFunctor*/;

struct lessFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a < b)>;
    }
} /*struct lessFunctor*/;

struct greaterFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a > b)>;
    }
} /*struct greaterFunctor*/;

struct lessEqualFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a <= b)>;
    }
} /*struct lessEqualFunctor*/;

struct greaterEqualFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a >= b)>;
    }
} /*struct greaterEqualFunctor*/;

} /*namespace detail*/;

static constexpr auto equal_to = detail::equalToFunctor{};
static constexpr auto not_equal_to = detail::notEqualToFunctor{};
static constexpr auto less = detail::lessFunctor{};
static constexpr auto greater = detail::greaterFunctor{};
static constexpr auto less_equal = detail::lessEqualFunctor{};
static constexpr auto greater_equal = detail::greaterEqualFunctor{};

} /*namespace aetee*/;

#endif
