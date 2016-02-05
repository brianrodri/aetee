#ifndef HEADER_AETEE_AXIOMS_FOR_EACH_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FOR_EACH_H_INCLUDED
#include <tuple>
#include <utility>
#include <aetee/axioms/length.h>

namespace aetee {

namespace detail {

struct forEachApplyFunctor {
    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
    {
        constexpr size_t N = length(type_c<Tup>);
        return impl(std::forward<Tup>(tup), std::forward<F>(f), std::make_index_sequence<N>{});
    }

private:
    template <typename Tup, size_t... I, typename F>
    constexpr auto impl(Tup&& tup, F&& fn, std::index_sequence<I...>) const
    {
        (apply(std::get<I>(std::forward<Tup>(tup)), std::forward<F>(fn)), ...);
        return fn;
    }
};

struct forEachFunctor {
    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& fn) const
    {
        constexpr size_t N = length(type_c<Tup>);
        return impl(std::forward<Tup>(tup), std::forward<F>(fn), std::make_index_sequence<N>{});
    }

    static constexpr auto apply = detail::forEachApplyFunctor{};

private:
    template <typename Tup, size_t... I, typename F>
    constexpr auto impl(Tup&& tup, F&& fn, std::index_sequence<I...>) const
    {
        (fn(std::get<I>(std::forward<Tup>(tup))), ...);
        return fn;
    }
} /*struct forEachFunctor*/;

} /*namespace detail*/;

static constexpr auto for_each = detail::forEachFunctor{};

} /*namespace aetee*/;

#endif
