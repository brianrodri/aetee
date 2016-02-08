#ifndef HEADER_AETEE_AXIOMS_OBJECTS_H_INCLUDED
#define HEADER_AETEE_AXIOMS_OBJECTS_H_INCLUDED
#include <utility>

namespace aetee {

namespace detail {

template <typename T>
struct bindFunctor {
    constexpr bindFunctor(T&& t_) : t{std::forward<T>(t_)} {};

    constexpr auto& operator()()
    {
        return t;
    }

    constexpr const auto& operator()() const
    {
        return t;
    }

private:
    T t;
};

struct identityFunctor {
    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return std::forward<T>(t);
    }

    template <typename T>
    static constexpr auto of(T&& t)
    {
        return bindFunctor<T>{std::forward<T>(t)};
    }
} /*struct identityFunctor*/;

} /*namespace detail*/;

static constexpr auto identity = detail::identityFunctor{};

} /*namespace aetee*/;

#endif
