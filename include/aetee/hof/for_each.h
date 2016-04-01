#ifndef HEADER_AETEE_AXIOMS_FOR_EACH_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FOR_EACH_H_INCLUDED
#include <aetee/int_c.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct forEachFunctor {

    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& fn) const
    {
        return impl(std::forward<Tup>(tup), std::forward<F>(fn), idx_c_sequence_of<Tup>);
    }

private:

    template <typename Tup, size_t... I, typename F>
    static constexpr auto impl(Tup&& tup, F&& fn, idx_sequence_t<I...>)
    {
        (fn(std::get<I>(std::forward<Tup>(tup))), ...);
        return fn;
    }

} /*struct forEachFunctor*/;

} /*namespace detail*/;

static constexpr auto for_each = detail::forEachFunctor{};

} /*namespace aetee*/;

#endif
