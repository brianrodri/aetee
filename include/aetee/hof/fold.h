#ifndef HEADER_AETEE_AXIOMS_FOLD_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FOLD_H_INCLUDED
#include <tuple>
#include <utility>
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

//! Fold left implementation
struct foldLeftFunctor {
    template <typename Tup, typename I, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, I&& init, F&& f) const
    {
        return impl(
            std::forward<Tup>(tup)
          , std::forward<I>(init)
          , std::forward<F>(f)
          , len_c<Tup>
            );
    }

private:
    template <typename Tup, typename I, typename F, size_t X>
    constexpr decltype(auto) impl(Tup&& tup, I&& init, F&& f, idx_constant_t<X>) const
    {
        return f(
            impl(
                std::forward<Tup>(tup)
              , std::forward<I>(init)
              , std::forward<F>(f)
              , idx_c<X - 1>
                )
          , std::get<X - 1>(std::forward<Tup>(tup))
            );
    }
    template <typename Tup, typename I, typename F>
    constexpr decltype(auto) impl(Tup&& tup, I&& init, F&& f, idx_constant_t<0>) const
    {
        return std::forward<I>(init);
    }
};

//! Fold right implementation
struct foldRightFunctor {
    template <typename Tup, typename I, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, I&& init, F&& f) const
    {
        return impl(
            std::forward<Tup>(tup)
          , std::forward<I>(init)
          , std::forward<F>(f)
          , len_c<Tup>
            );
    }
private:
    template <typename Tup, typename I, typename F, size_t X>
    constexpr decltype(auto) impl(Tup&& tup, I&& init, F&& f, idx_constant_t<X>) const
    {
        return f(
            std::get<length(type_c<tup>) - X>(std::forward<Tup>(tup))
          , impl(
                std::forward<Tup>(tup)
              , std::forward<I>(init)
              , std::forward<F>(f)
              , idx_c<X - 1>
                )
            );
    };
    template <typename Tup, typename I, typename F>
    constexpr decltype(auto) impl(Tup&& tup, I&& init, F&& f, idx_constant_t<0>) const
    {
        return std::forward<I>(init);
    }
};

} /*namespace detail*/;

static constexpr auto fold = detail::foldLeftFunctor{};
static constexpr auto foldr = detail::foldRightFunctor{};

} /*namespace aetee*/;

#endif
