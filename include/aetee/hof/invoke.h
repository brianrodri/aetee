#ifndef HEADER_AETEE_HOF_INVOKE_H_INCLUDED
#define HEADER_AETEE_HOF_INVOKE_H_INCLUDED
#include <utility>

namespace aetee {

namespace detail {

struct invokeFunctor {

    template <typename F, typename... A>
    constexpr auto operator()(F&& f, A&&... a) const
    {
        return fn(std::forward<A>(a)...);
    }

} /*struct invokeFunctor*/;

} /*namespace detail*/;

static constexpr auto invoke = detail::invokeFunctor{};

} /*namespace aetee*/;

#endif
