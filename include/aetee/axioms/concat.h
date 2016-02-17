#ifndef HEADER_AETEE_AXIOMS_CONCAT_H_INCLUDED
#define HEADER_AETEE_AXIOMS_CONCAT_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct concatFunctor {
    template <typename ATup, typename BTup>
    constexpr auto operator()(ATup&& a, BTup&& b) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<ATup>>::value;
        constexpr size_t M = std::tuple_size<std::decay_t<BTup>>::value;
        return impl(
            std::forward<ATup>(a), std::forward<BTup>(b)
          , idx_sequence_c_of<ATup>, idx_sequence_c_of<BTup>
            );
    }

private:
    template <typename ATup, typename BTup, size_t... I, size_t... J>
    static constexpr auto impl(ATup&& a, BTup&& b, idx_sequence_t<I...>, idx_sequence_t<J...>)
    {
        return std::make_tuple(
            std::get<I>(std::forward<ATup>(a))...
          , std::get<J>(std::forward<BTup>(b))...
            );
    }
} /*struct concatFunctor*/;

} /*namespace detail*/;

static constexpr auto concat = detail::concatFunctor{};

} /*namespace aetee*/;

#endif
