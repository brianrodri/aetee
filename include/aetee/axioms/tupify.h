#ifndef HEADER_AETEE_AXIOMS_TUPIFY_H_INCLUDED
#define HEADER_AETEE_AXIOMS_TUPIFY_H_INCLUDED
#include <aetee/axioms/select.h>
#include <aetee/traits/is_tuple.h>
#include <aetee/axioms/nothing.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct tupifyFunctor {

    constexpr auto operator()(nothing_t) const
    {
        return std::make_tuple();
    }

    template <typename Tup>
    constexpr auto operator()(Tup&& t) const
    {
        return select(
            is_tuple(type_c<Tup>)
          , std::forward<Tup>(t)
          , std::make_tuple(std::forward<Tup>(t))
            );
    }

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
