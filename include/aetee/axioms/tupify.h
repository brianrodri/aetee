#ifndef HEADER_AETEE_AXIOMS_TUPIFY_H_INCLUDED
#define HEADER_AETEE_AXIOMS_TUPIFY_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct tupifyFunctor {

    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::make_tuple(std::forward<T>(t)...);
    }

} /*struct tupifyFunctor*/;

} /*namespace detail*/;

static constexpr auto tupify = detail::tupifyFunctor{};

} /*namespace aetee*/;

#endif
