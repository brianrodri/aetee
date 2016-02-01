#ifndef HEADER_AETEE_AXIOMS_H_INCLUDED
#define HEADER_AETEE_AXIOMS_H_INCLUDED
#include <string>
#include <tuple>
#include <utility>
#include <aetee/integer_c.h>
#include <aetee/type_c.h>

namespace aetee {

struct lengthFunctor {
    template <typename Tup>
    constexpr auto operator()(Tup&& t) const
    {
        return index_c<std::tuple_size<std::decay_t<Tup>>::value>;
    }

    template <typename Tup>
    constexpr auto operator()(type_constant_t<Tup>) const
    {
        return index_c<std::tuple_size<Tup>::value>;
    }
};

namespace detail {

template <typename T, size_t... I>
constexpr auto replicate_impl(T&& val, std::index_sequence<I...>)
{
    return std::make_tuple((I, T{val})...);
}

template <typename Tup, size_t... I, typename F>
constexpr auto for_each_impl(Tup&& tup, F&& fn, std::index_sequence<I...>)
{
    (fn(std::get<I>(std::forward<Tup>(tup))), ...);
    return fn;
}

template <typename Tup, typename F, size_t... I>
constexpr auto transform_impl(Tup&& tup, F&& f, std::index_sequence<I...>)
{
    return std::make_tuple(f(std::get<I>(std::forward<Tup>(tup)))...);
}

template <typename ATup, typename BTup, size_t... I, size_t... J>
constexpr auto concat_impl(ATup&& a, BTup&& b, std::index_sequence<I...>, std::index_sequence<J...>)
{
    return std::make_tuple(
        std::get<I>(std::forward<ATup>(a))...
      , std::get<J>(std::forward<BTup>(b))...
        );
}

template <typename Tup, typename X, size_t... I>
constexpr auto prepend_impl(Tup&& tup, X&& x, std::index_sequence<I...>)
{
    return std::make_tuple(std::forward<X>(x), std::get<I>(std::forward<Tup>(tup))...);
}

template <typename Tup, typename X, size_t... I>
constexpr auto append_impl(Tup&& tup, X&& x, std::index_sequence<I...>)
{
    return std::make_tuple(std::get<I>(std::forward<Tup>(tup))..., std::forward<X>(x));
}

template <typename Tup, typename F, size_t... I>
constexpr auto apply_impl(bool_constant_t<true>, Tup&& tup, F&& f, std::index_sequence<I...>)
{
    return f(std::get<I>(std::forward<F>(f))...);
}

template <typename Tup, typename F, size_t... I>
constexpr void apply_impl(bool_constant_t<false>, Tup&& tup, F&& f, std::index_sequence<I...>)
{
    f(std::get<I>(std::forward<F>(f))...);
}

template <typename Tup, typename F>
struct expanded_call_impl {
    template <typename Seq> struct expander;

    template <size_t... I>
    struct expander<std::index_sequence<I...>> {
        using type = F(std::tuple_element_t<I, Tup>...);
    };

    using call_type = typename expander<decltype(std::make_index_sequence<std::tuple_size<std::decay_t<Tup>>::value>{})>::type;
};

template <typename Tup, typename Init, typename F>
constexpr decltype(auto) fold_impl(Tup&& tup, Init&& i, F&& f, index_constant_t<0>)
{
    return std::forward<Init>(i);
}

template <typename Tup, typename Init, typename F, size_t N>
constexpr decltype(auto) fold_impl(Tup&& tup, Init&& i, F&& f, index_constant_t<N>)
{
    return f(
        fold_impl(
            std::forward<Tup>(tup)
          , std::forward<Init>(i)
          , std::forward<F>(f)
          , index_c<N-1>
            )
      , std::get<N-1>(std::forward<Tup>(tup))
        );
}

template <typename Tup, typename Init, typename F, size_t N>
constexpr decltype(auto) foldr_impl(Tup&& tup, Init&& i, F&& f, index_constant_t<N> n)
{
    constexpr auto X = std::tuple_size<std::decay_t<Tup>>::value - N;
    return f(
        std::get<X>(std::forward<Tup>(tup))
      , foldr_impl(
            std::forward<Tup>(tup)
          , std::forward<Init>(i)
          , std::forward<F>(f)
          , index_c<N-1>
            )
        );
}

template <typename F, typename Tup, size_t... I, typename... B>
constexpr auto curry_impl(F&& f, Tup&& t, std::index_sequence<I...>, B&&... b)
{
    return f(std::get<I>(std::forward<Tup>(t))..., std::forward<B>(b)...);
}

}; // namespace detail

struct replicateFunctor {
    template <typename T, size_t N>
    constexpr auto operator()(T&& t, index_constant_t<N>)
    {
        return detail::replicate_impl(std::forward<T>(t), std::make_index_sequence<N>{});
    }
};

struct sizeFunctor {
    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return index_c<sizeof(T)>;
    }
};

struct alignFunctor {
    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return index_c<alignof(T)>;
    }
};

struct identityFunctor {
    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return t;
    }

    template <typename T>
    struct bindFunctor {
        T t;
        bindFunctor(T&& t_) : t{t_} {};
        auto operator()() const
        {
            return t;
        }
    };

    template <typename T>
    static constexpr auto bind(T&& t)
    {
        return bindFunctor<T>{std::forward<T>(t)};
    }
};

struct tupifyFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::make_tuple(std::forward<T>(t)...);
    }
};

struct stringifyFunctor {
    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return std::to_string(std::forward<T>(t));
    }
};

struct nothingFunctor {
    auto operator()(...) const
    {
        return std::make_tuple();
    }
};

template <typename T>
struct justFunctor {
    T t;
    justFunctor(T&& t_) : t{t_} {};
    auto operator()(...) const
    {
        return t;
    }
};

struct prependFunctor {
    template <typename Tup, typename X>
    constexpr auto operator()(Tup&& tup, X&& x) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return detail::prepend_impl(std::forward<Tup>(tup), std::forward<X>(x), std::make_index_sequence<N>{});
    }
};

struct appendFunctor {
    template <typename Tup, typename X>
    constexpr auto operator()(Tup&& tup, X&& x) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return detail::append_impl(std::forward<Tup>(tup), std::forward<X>(x), std::make_index_sequence<N>{});
    }
};

struct transformFunctor {
    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return detail::transform_impl(
            std::forward<Tup>(tup)
          , std::forward<F>(f)
          , std::make_index_sequence<N>{}
            );
    }
};

template <typename Tup, typename F>
using expanded_call = detail::expanded_call_impl<Tup, F>;

template <typename Tup, typename F>
using expanded_call_t = typename expanded_call<Tup, F>::call_type;

struct applyFunctor {
    template <typename Tup, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, F&& f) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return detail::apply_impl(
            std::is_void<std::result_of_t<expanded_call_t<Tup, F>>>{}
          , std::forward<Tup>(tup)
          , std::forward<F>(f)
          , std::make_index_sequence<N>{}
            );
    }
};

struct concatFunctor {
    template <typename ATup, typename BTup>
    constexpr auto operator()(ATup&& a, BTup&& b) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<ATup>>::value;
        constexpr size_t M = std::tuple_size<std::decay_t<BTup>>::value;
        return detail::concat_impl(
            std::forward<ATup>(a), std::forward<BTup>(b)
          , std::make_index_sequence<N>{}
          , std::make_index_sequence<M>{}
            );
    }
};

struct composeFunctor {
    template <typename F, typename G>
    struct composition {
        F f; G g;
        template <typename... A>
        constexpr auto operator()(A&&... a) const
        {
            return f(g(std::forward<A>(a)...));
        }
    };

    template <typename F, typename G>
    constexpr auto operator()(F&& f, G&& g) const
    {
        return composition<F, G>{std::forward<F>(f), std::forward<G>(g)};
    }
};

struct curryFunctor {
    template <class F, typename... A>
    struct curried {
        F f;
        std::tuple<A...> a;
        constexpr curried(F&& f_, A&&... a_) : f{std::forward<F>(f_)}, a{std::forward<A>(a_)...} {};

        template <typename... B>
        constexpr auto operator()(B&&... b) const
        {
            return detail::curry_impl(f, a, std::make_index_sequence<sizeof...(A)>{}, std::forward<B>(b)...);
        }
    };

    template <typename F, typename... Args>
    constexpr auto operator()(F&& f, Args&&... args) const
    {
        return curried<F, Args...>{std::forward<F>(f), std::forward<Args>(args)...};
    }
};

struct valueFunctor {
    template <typename T>
    constexpr decltype(auto) operator()(T&& t) const
    {
        return T::value;
    }

    template <typename T>
    constexpr decltype(auto) operator()(type_constant_t<T>) const
    {
        return T::value;
    }
};

struct choiceFunctor {
    template <typename BranchTaken, typename _>
    decltype(auto) operator()(bool_constant_t<true>, BranchTaken&& f, _&&) const
    {
        return f();
    }

    template <typename _, typename BranchTaken>
    decltype(auto) operator()(bool_constant_t<false>, _&&, BranchTaken&& f) const
    {
        return f();
    }

    template <typename Conditional, typename ABranch, typename BBranch>
    decltype(auto) operator()(Conditional&& c, ABranch&& a, BBranch&& b) const
    {
        constexpr bool result = valueFunctor{}(std::forward<Conditional>(c));
        return operator()(bool_c<result>, std::forward<ABranch>(a), std::forward<BBranch>(b));
    }

    template <typename F, typename A = identityFunctor, typename B = identityFunctor>
    struct asPredicateFunctor {
        F f; A a; B b;
        asPredicateFunctor(F&& f_, A&& a_ = {}, B&& b_ = {}) : f{f_}, a{a_}, b{b_} {};

        template <typename T>
        decltype(auto) operator()(T&& t) const
        {
            return choiceFunctor{}(
                f(std::forward<T>(t))
              , curryFunctor{}(a, t)
              , curryFunctor{}(b, t)
                );
        }
    };

    template <typename F, typename A, typename B>
    static constexpr decltype(auto) asPredicate(F&& f, A&& a, B&& b)
    {
        return asPredicateFunctor<F, A, B>{std::forward<F>(f), std::forward<A>(a), std::forward<B>(b)};
    }
};

struct forEachFunctor {
    template <typename Tup, typename F>
    auto operator()(Tup&& tup, F&& fn) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return detail::for_each_impl(
            std::forward<Tup>(tup)
          , std::forward<F>(fn)
          , std::make_index_sequence<N>{}
            );
    }
};

struct foldFunctor {
    template <typename Tup, typename Init, typename F>
    constexpr auto operator()(Tup&& tup, Init&& i, F&& f) const
    {
        return detail::fold_impl(
            std::forward<Tup>(tup)
          , std::forward<Init>(i)
          , std::forward<F>(f)
          , index_c<lengthFunctor{}(tup)>
            );
    }

    /*
    template <typename... T, typename F>
    constexpr auto operator()(std::tuple<T&&...>&& tup, F&& f) const
    {
        using Tup = std::tuple<T&&...>;
        static_assert(lengthFunctor{}(type_sequence_c<T...>));
        return detail::fold_impl(
            std::forward<Tup>(tup)
          , std::get<0>(std::forward<Tup>(tup))
          , std::forward<F>(f)
          , index_c<lengthFunctor{}(type_sequence_c<T...>)>
            );
    }
    */
};

struct foldRightFunctor {
    template <typename Tup, typename Init, typename F>
    constexpr auto operator()(Tup&& tup, Init&& i, F&& f) const
    {
        return detail::foldr_impl(
            std::forward<Tup>(tup)
          , std::forward<Init>(i)
          , std::forward<F>(f)
          , index_c<lengthFunctor{}(tup)>
            );
    }
};

static constexpr auto identity = identityFunctor{};
static constexpr auto tupify = tupifyFunctor{};
static constexpr auto nothing = nothingFunctor{};
static constexpr auto prepend = prependFunctor{};
static constexpr auto append = appendFunctor{};
static constexpr auto transform = transformFunctor{};
static constexpr auto apply = applyFunctor{};
static constexpr auto concat = concatFunctor{};
static constexpr auto choice = choiceFunctor{};
static constexpr auto for_each = forEachFunctor{};
static constexpr auto fold = foldFunctor{};
static constexpr auto foldr = foldFunctor{};
static constexpr auto curry = curryFunctor{};
static constexpr auto value = valueFunctor{};
static constexpr auto size = sizeFunctor{};
static constexpr auto len = lengthFunctor{};
static constexpr auto align = alignFunctor{};
static constexpr auto compose = composeFunctor{};
static constexpr auto stringify = stringifyFunctor{};

template <typename T>
static constexpr auto just(T&& t) { return justFunctor<T>{std::forward<T>(t)}; };

}; // namespace aetee

#endif
