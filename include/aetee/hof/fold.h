#ifndef HEADER_AETEE_AXIOMS_FOLD_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FOLD_H_INCLUDED
#include <tuple>
#include <utility>
#include <aetee/axioms/length.h>

namespace aetee {

namespace detail {

//! Fold left implementation
struct foldLeftFunctor {
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, Init&& init, F&& f) const
    {
        return impl(
            std::forward<Tup>(tup)
          , std::forward<Init>(init)
          , std::forward<F>(f)
          , index_c<length(type_c<Tup>)>
            );
    }

private:
    template <typename Tup, typename Init, typename F, size_t I>
    constexpr decltype(auto) impl(Tup&& tup, Init&& init, F&& f, index_constant_t<I>) const
    {
        return f(
            impl(
                std::forward<Tup>(tup)
              , std::forward<Init>(init)
              , std::forward<F>(f)
              , index_c<I - 1>
                )
          , std::get<I - 1>(std::forward<Tup>(tup))
            );
    }
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) impl(Tup&& tup, Init&& init, F&& f, index_constant_t<0>) const
    {
        return std::forward<Init>(init);
    }
};

//! Fold right implementation
struct foldRightFunctor {
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, Init&& init, F&& f) const
    {
        return impl(
            std::forward<Tup>(tup)
          , std::forward<Init>(init)
          , std::forward<F>(f)
          , index_c<length(type_c<Tup>)>
            );
    }
private:
    template <typename Tup, typename Init, typename F, size_t I>
    constexpr decltype(auto) impl(Tup&& tup, Init&& init, F&& f, index_constant_t<I>) const
    {
        return f(
            std::get<length(type_c<tup>) - I>(std::forward<Tup>(tup))
          , impl(
                std::forward<Tup>(tup)
              , std::forward<Init>(init)
              , std::forward<F>(f)
              , index_c<I - 1>
                )
            );
    };
    template <typename Tup, typename Init, typename F>
    constexpr decltype(auto) impl(Tup&& tup, Init&& init, F&& f, index_constant_t<0>) const
    {
        return std::forward<Init>(init);
    }
};

} /*namespace detail*/;

static constexpr auto fold = detail::foldLeftFunctor{};
static constexpr auto foldr = detail::foldRightFunctor{};

} /*namespace aetee*/;

#endif
