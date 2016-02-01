#ifndef HEADER_AETEE_COROLLARIES_H_INCLUDED
#define HEADER_AETEE_COROLLARIES_H_INCLUDED
#include <aetee/axioms.h>

namespace aetee {

namespace detail {
struct minFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return (a < b) ? a : b;
    }
};

struct maxFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return (a > b) ? a : b;
    }
};

template <size_t... I, typename... Tup>
static constexpr auto zip_impl(std::index_sequence<I...>, Tup&&... tup)
{
    return std::make_tuple(
        (index_c<I>, std::make_tuple(
            (type_c<Tup>, std::get<I>(std::forward<Tup>(tup)))...
            ))...
        );
}

}; // namespace detail

struct filterFunctor {
    template <typename Tup, typename UnaryPredicate>
    auto operator()(Tup&& tup, UnaryPredicate&& f) const
    {
        return fold(
            transform(
                std::forward<Tup>(tup)
              , choice.asPredicate(std::forward<UnaryPredicate>(f), tupify, nothing)
                )
          , std::make_tuple()
          , concat
            );
    }
};

static constexpr auto filter = filterFunctor{};

}; // namespace aetee

#endif
