#ifndef HEADER_AETEE_HOF_APPLY_H_INCLUDED
#define HEADER_AETEE_HOF_APPLY_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/traits/is_tuple.h>
#include <type_traits>
#include <utility>

namespace aetee {

namespace detail {

struct applyFunctor {

    template <typename T, typename F>
    constexpr decltype(auto) operator()(T&& t, F&& f) const
    {
        return impl(std::forward<T>(t), std::forward<F>(f), is_tuple(type_c<T>));
    }

private:

    template <typename T, typename F>
    static constexpr decltype(auto) impl(T&& t, F&& f, true_constant_t)
    {
        return impl(std::forward<T>(t), std::forward<F>(f), idx_sequence_c_of<T>);
    }

    template <typename Arg, typename F>
    static constexpr decltype(auto) impl(Arg&& a, F&& f, false_constant_t)
    {
        return f(std::forward<Arg>(a));
    }

    template <typename T, typename F, size_t... I>
    static constexpr decltype(auto) impl(T&& tup, F&& f, idx_sequence_t<I...>)
    {
        return f(std::get<I>(std::forward<T>(tup))...);
    }

} /*struct applyFunctor*/;

} /*namespace detail*/;

static constexpr auto apply = detail::applyFunctor{};

} /*namespace aetee*/;

#endif
