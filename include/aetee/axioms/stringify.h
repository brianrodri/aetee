#ifndef HEADER_AETEE_AXIOMS_STRINGIFY_H_INCLUDED
#define HEADER_AETEE_AXIOMS_STRINGIFY_H_INCLUDED
#include <string>
#include <utility>

namespace aetee {

namespace detail {

struct stringifyFunctor {

    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return std::to_string(std::forward<T>(t));
    }

    constexpr auto operator()() const
    {
        return "";
    }

} /*struct stringifyFunctor*/;

} /*namespace detail*/;

static constexpr auto stringify = detail::stringifyFunctor{};

} /*namespace aetee*/;

#endif

