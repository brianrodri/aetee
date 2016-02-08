#ifndef HEADER_AETEE_AXIOMS_INVOKE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_INVOKE_H_INCLUDED

namespace aetee {

namespace detail {

struct invokeFunctor {
    template <typename F, typename... A>
    constexpr auto operator()(A&&... a, F&& fn) const
    {
        return std::forward<F>(fn)(std::forward<A>(a)...);
    }
} /*struct invokeFunctor*/;

} /*namespace detail*/;

static constexpr auto invoke = detail::invokeFunctor{};

} /*namespace aetee*/;

#endif
