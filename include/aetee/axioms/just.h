#ifndef HEADER_AETEE_AXIOMS_JUST_H_INCLUDED
#define HEADER_AETEE_AXIOMS_JUST_H_INCLUDED
#include <utility>

namespace aetee {

namespace detail {

// Forward Declaration
template <typename T> struct justImpl;

struct justFunctor {

    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return justImpl<T>{std::forward<T>(t)};
    }

} /*struct justFunctor*/;

template <typename T>
struct justImpl {

    constexpr justImpl(T&& t_) : t{std::forward<T>(t_)} {};

    constexpr operator T() const
    {
        return t;
    }

    constexpr T& operator()(...)
    {
        return t;
    }

    constexpr const T& operator()(...) const
    {
        return t;
    }

private:

    T t;

} /*struct justImpl*/;

} /*namespace detail*/;

template <typename T> using just_t = detail::justImpl<T>;
static constexpr auto just = detail::justFunctor{};

} /*namespace aetee*/;

#endif
