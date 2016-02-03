#ifndef HEADER_AETEE_AXIOMS_FOLD_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FOLD_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

template <bool Leftness>
struct foldFunctor {
    //! With an initial value
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, Init&& i, F&& f) const
    {
        return impl(
            std::integral_constant<bool, Leftness>{}
          , std::forward<Tup>(tup)
          , std::forward<Init>(i)
          , std::forward<F>(f)
          , index_c<std::tuple_size<std::decay_t<Tup>>::value>
            );
    }

    //! Without an initial value
    template <typename Tup, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, F&& f) const
    {
        static_assert(std::tuple_size<std::decay_t<Tup>>::value > 0);
        return impl(
            std::integral_constant<bool, Leftness>{}
          , std::forward<Tup>(tup)
          , std::forward<F>(f)
          , index_c<std::tuple_size<std::decay_t<Tup>>::value>
            );
    }

private:
    //! FOLDING TUPLES W/ AN INITIAL VALUE

    //! Step case for left folding: Return recursively
    template <typename Tup, typename Init, typename F, size_t N>
    constexpr decltype(auto) impl(std::integral_constant<bool, true> leftness, Tup&& tup, Init&& i, F&& f, std::integral_constant<size_t, N>) const
    {
        return f(
            impl(
                leftness
              , std::forward<Tup>(tup)
              , std::forward<Init>(i)
              , std::forward<F>(f)
              , std::integral_constant<size_t, N-1>{}
                )
          , std::get<N-1>(std::forward<Tup>(tup))
            );
    }

    //! Step case for right folding: Return recursively
    template <typename Tup, typename Init, typename F, size_t N>
    constexpr decltype(auto) impl(std::integral_constant<bool, false> leftness, Tup&& tup, Init&& i, F&& f, std::integral_constant<size_t, N>) const
    {
        return f(
            std::get<std::tuple_size<std::decay_t<Tup>>::value - N>(std::forward<Tup>(tup))
          , impl(
                leftness
              , std::forward<Tup>(tup)
              , std::forward<Init>(i)
              , std::forward<F>(f)
              , std::integral_constant<size_t, N-1>{}
                )
            );
    }

    //! Base case: Return initial value
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) impl(std::integral_constant<bool, true>, Tup&& tup, Init&& i, F&& f, std::integral_constant<size_t, 0>) const
    {
        return std::forward<Init>(i);
    }

    //! Base case: Return initial value
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) impl(std::integral_constant<bool, false>, Tup&& tup, Init&& i, F&& f, std::integral_constant<size_t, 0>) const
    {
        return std::forward<Init>(i);
    }

    //! FOLDING TUPLES WITHOUT AN INITIAL VALUE

    //! Step case for left fold: Return recursively
    template <typename Tup, typename F, size_t N>
    constexpr decltype(auto) impl(std::integral_constant<bool, true> leftness, Tup&& tup, F&& f, std::integral_constant<size_t, N>) const
    {
        return f(
            impl(
                leftness
              , std::forward<Tup>(tup)
              , std::forward<F>(f)
              , std::integral_constant<size_t, N-1>{}
                )
          , std::get<N>(std::forward<Tup>(tup))
            );
    }

    //! Step case for right fold: Return recursively
    template <typename Tup, typename F, size_t N>
    constexpr decltype(auto) impl(std::integral_constant<bool, false> leftness, Tup&& tup, F&& f, std::integral_constant<size_t, N>) const
    {
        return f(
            std::get<std::tuple_size<std::decay_t<Tup>>::value - N>(std::forward<Tup>(tup))
          , impl(
                leftness
              , std::forward<Tup>(tup)
              , std::forward<F>(f)
              , std::integral_constant<size_t, N-1>{}
                )
            );
    }

    //! Base case for initial-less fold: Return relevant element of tuple
    template <bool L, typename Tup, typename F>
    constexpr decltype(auto) impl(std::integral_constant<bool, L>, Tup&& tup, F&& f, std::integral_constant<size_t, 0>) const
    {
        // no-op
    }

    //! Base case for initial-less fold: Return relevant element of tuple
    template <typename Tup, typename F>
    constexpr decltype(auto) impl(std::integral_constant<bool, true>, Tup&& tup, F&& f, std::integral_constant<size_t, 1>) const
    {
        return std::get<0>(std::forward<Tup>(tup));
    }

    //! Base case for initial-less fold: Return relevant element of tuple
    template <typename Tup, typename F>
    constexpr decltype(auto) impl(std::integral_constant<bool, false>, Tup&& tup, F&& f, std::integral_constant<size_t, 1>) const
    {
        return std::get<std::tuple_size<std::decay_t<Tup>>::value - 1>(std::forward<Tup>(tup));
    }
};

} /*namespace detail*/;

static constexpr auto fold = detail::foldFunctor<true>{};
static constexpr auto foldr = detail::foldFunctor<false>{};

} /*namespace aetee*/;

#endif
