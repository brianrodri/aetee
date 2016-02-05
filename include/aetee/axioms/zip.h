#ifndef HEADER_AETEE_HOF_ZIP_H_INCLUDED
#define HEADER_AETEE_HOF_ZIP_H_INCLUDED
#include <aetee/mathsugar.h>
#include <aetee/type_c.h>
#include <aetee/objects.h>

namespace aetee {

namespace detail {

struct zipFunctor {
    template <typename... Tup>
    constexpr auto operator()(Tup&&... tup) const
    {
        constexpr auto minLen = std::min({length(tup)...});
        return impl(std::make_index_sequence<minLen>{}, std::forward<Tup>(tup)...);
    }

private:
    template <size_t... I, typename... Tup>
    constexpr auto impl(std::index_sequence<I...> indices, Tup&&... tup) const
    {
        return std::make_tuple(
            extractElement(index_c<I>, std::forward<Tup>(tup)...)...
            );
    }

    template <size_t X, size_t... I, typename... Tup>
    constexpr auto extractElement(index_constant_t<X>, Tup&&... tup) const
    {
        return std::make_tuple(std::get<X>(std::forward<Tup>(tup))...);
    }
} /*struct zipFunctor*/;

} /*namespace detail*/;

static constexpr auto zip = detail::zipFunctor{};

} /*namespace aetee*/;

#endif
