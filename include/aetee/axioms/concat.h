#ifndef HEADER_AETEE_AXIOMS_CONCAT_H_INCLUDED
#define HEADER_AETEE_AXIOMS_CONCAT_H_INCLUDED
#include <aetee/int_c.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct concatTwoFunctor {

    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return impl(
            std::forward<A>(a), std::forward<B>(b)
          , idx_sequence_c_of<A>, idx_sequence_c_of<B>
            );
    }

private:

    template <typename A, typename B, size_t... I, size_t... J>
    static constexpr auto impl(A&& a, B&& b, idx_sequence_t<I...>, idx_sequence_t<J...>)
    {
        return std::make_tuple(
            std::get<I>(std::forward<A>(a))...
          , std::get<J>(std::forward<B>(b))...
            );
    }

} /*struct concatTwoFunctor*/;

struct concatFunctor {

    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return fold(
            std::forward_as_tuple(std::forward<T>(t)...)
          , std::make_tuple()
          , concatTwoFunctor{}
            );
    }

} /*struct concatFunctor*/;

} /*namespace detail*/;

static constexpr auto concat = detail::concatFunctor{};

} /*namespace aetee*/;

#endif
