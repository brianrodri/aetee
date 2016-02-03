#ifndef HEADER_AETEE_COROLLARIES_FILTER_H_INCLUDED
#define HEADER_AETEE_COROLLARIES_FILTER_H_INCLUDED
#include <aetee/objects.h>
#include <aetee/hof/choice.h>
#include <aetee/hof/fold.h>
#include <aetee/hof/transform.h>

namespace aetee {

namespace detail {

struct filterFunctor {
    template <typename Tup, typename UnaryPredicate>
    auto operator()(Tup&& tup, UnaryPredicate&& f) const
    {
        return fold(
            transform(
                std::forward<Tup>(tup)
              , choice.transform(std::forward<UnaryPredicate>(f), tupify, nothing)
                )
          , std::make_tuple()
          , concat
            );
    }
} /*struct filterFunctor*/;

} /*namespace detail*/;

static constexpr auto filter = detail::filterFunctor{};

} /*namespace aetee*/;

#endif
