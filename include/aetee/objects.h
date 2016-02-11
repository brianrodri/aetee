#ifndef HEADER_AETEE_OBJECTS_STRINGIFY_H_INCLUDED
#define HEADER_AETEE_OBJECTS_STRINGIFY_H_INCLUDED
#include <string>
#include <type_traits>
#include <aetee/type_c.h>

namespace aetee {

namespace detail {

struct tupifyFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::make_tuple(std::forward<T>(t)...);
    }
} /*struct tupifyFunctor*/;

struct stringifyFunctor {
    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return std::to_string(std::forward<T>(t));
    }
} /*struct stringifyFunctor*/;

struct nothingFunctor {
    constexpr auto operator()(...) const
    {
        return nothingFunctor{};
    }
} /*struct nothingFunctor*/;

struct valueFunctor {
    template <typename T>
    constexpr decltype(auto) operator()(T&& t) const
    {
        return std::decay_t<T>::value;
    }
    template <typename T>
    constexpr decltype(auto) operator()(type_constant_t<T>) const
    {
        return std::decay_t<T>::value;
    }
} /*struct valueFunctor*/;

struct justFunctor {
    template <typename T>
    constexpr auto operator()(T&&) const
    {
        return just<T>{std::forward<T>};
    }

private:
    template <typename T>
    struct just {
        constexpr just(T&& t_) : t{std::forward<T>(t_)} {};

        constexpr operator T() const
        {
            return t;
        }

        constexpr T operator()(...) const
        {
            return t;
        }

    private:
        T t;
    } /*struct just*/;
} /*struct justFunctor*/;

struct decltypeFunctor {
    template <typename T>
    constexpr auto operator()(T&&) const {
        return type_c<std::decay_t<T>>;
    }

    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return type_c<T>;
    }
} /*struct decltypeFunctor*/;

struct alignToFunctor {
    template <typename S, typename A>
    constexpr auto operator()(S&& s, A&& a) const
    {
        return ((s + a - 1) / a) * a;
    }
} /*struct alignToFunctor*/;

struct offsetOfFunctor {
    template <typename... T, size_t I>
    constexpr auto operator()(type_constant_t<T>... ts, index_constant_t<I> is) const
    {
        namespace stx = std::experimental;
        constexpr std::array<size_t, sizeof...(T)> szs{sizeof(T)...};
        constexpr std::array<size_t, sizeof...(T) + 1> als{alignof(T)..., alignof(std::aligned_union_t<1, char, T...>)};
        size_t result{0};
        for (size_t i{1}; i <= I; ++i) {
            result = ((result + szs[i-1] + als[i] - 1) / als[i]) * als[i];
        }
        return result;
    }

    template <typename... T, size_t I = sizeof...(T)>
    constexpr auto operator()(type_sequence_t<T...> ts, index_constant_t<I> is = {}) const
    {
        namespace stx = std::experimental;
        constexpr std::array<size_t, sizeof...(T)> szs{sizeof(T)...};
        constexpr std::array<size_t, sizeof...(T) + 1> als{alignof(T)..., 1};
        size_t result{0};
        for (size_t i{1}; i <= I; ++i) {
            result = ((result + szs[i-1] + als[i] - 1) / als[i]) * als[i];
        }
        return result;
    }
} /*struct offsetOfFunctor*/;

} /*namespace detail*/;

static constexpr auto stringify = detail::stringifyFunctor{};
static constexpr auto nothing = detail::nothingFunctor{};
static constexpr auto just = detail::justFunctor{};
static constexpr auto value = detail::valueFunctor{};
static constexpr auto tupify = detail::tupifyFunctor{};
static constexpr auto decltype_ = detail::decltypeFunctor{};
static constexpr auto alignto = detail::alignToFunctor{};
static constexpr auto offsetof_ = detail::offsetOfFunctor{};

} /*namespace aetee*/;

#endif
