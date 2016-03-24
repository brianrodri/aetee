#ifndef HEADER_AETEE_AXIOMS_JUST_H_INCLUDED
#define HEADER_AETEE_AXIOMS_JUST_H_INCLUDED
#include <utility>

namespace aetee {

namespace detail {

struct justFunctor {
    template <typename T>
    constexpr auto operator()(T&&) const
    {
        return justImpl<T>{std::forward<T>};
    }

private:
    template <typename T>
    struct justImpl {
        constexpr justImpl(T&& t_) : t{std::forward<T>(t_)} {};

        constexpr operator T() const
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

} /*struct justFunctor*/;

} /*namespace detail*/;

static constexpr auto just = detail::justFunctor{};

} /*namespace aetee*/;

#endif
