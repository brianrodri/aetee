#ifndef HEADER_AETEE_HOF_ZIP_H_INCLUDED
#define HEADER_AETEE_HOF_ZIP_H_INCLUDED
#include <tuple>
#include <utility>
#include <aetee/axioms/value.h>
#include <aetee/traits/length.h>

namespace aetee {

namespace detail {

struct zipFunctor {
    constexpr auto operator()() const
    {
        return std::make_tuple();
    }

    template <typename... Tup>
    constexpr auto operator()(Tup&&... tup) const
    {
        constexpr auto minLen = std::min({value(length(type_c<Tup>))...});
        return impl(idx_sequence_c_til<minLen>, std::forward<Tup>(tup)...);
    }

private:
    template <size_t... I, typename... Tup>
    constexpr auto impl(idx_sequence_t<I...> indices, Tup&&... tup) const
    {
        return std::make_tuple(
            extractElement(idx_c<I>, std::forward<Tup>(tup)...)...
            );
    }

    template <size_t X, typename... Tup>
    constexpr auto extractElement(idx_constant_t<X>, Tup&&... tup) const
    {
        return std::make_tuple(std::get<X>(std::forward<Tup>(tup))...);
    }
} /*struct zipFunctor*/;

} /*namespace detail*/;

static constexpr auto zip = detail::zipFunctor{};

} /*namespace aetee*/;

#endif
