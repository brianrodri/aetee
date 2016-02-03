#ifndef HEADER_AETEE_AXIOMS_CURRY_H_INCLUDED
#define HEADER_AETEE_AXIOMS_CURRY_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct curryFunctor {
    template <typename F, typename... Args>
    constexpr auto operator()(F&& f, Args&&... args) const
    {
        return curried<F, Args...>{std::forward<F>(f), std::forward<Args>(args)...};
    }

private:
    template <class F, typename... A>
    struct curried {
        constexpr curried(F&& f_, A&&... a_) : f{std::forward<F>(f_)}, a{std::forward<A>(a_)...} {};

        template <typename... B>
        constexpr decltype(auto) operator()(B&&... b) const
        {
            return impl(std::make_index_sequence<sizeof...(A)>{}, std::forward<B>(b)...);
        }

    private:
        F f;
        std::tuple<A...> a;

        template <typename G, typename Tup, size_t... I, typename... B>
        constexpr decltype(auto) impl(std::index_sequence<I...>, B&&... b)
        {
            return f(std::get<I>(a)..., std::forward<B>(b)...);
        }
    } /*struct curried*/;

} /*struct curryFunctor*/;

} /*namespace detail*/;

static constexpr auto curry = detail::curryFunctor{};

} /*namespace aetee*/;

#endif
