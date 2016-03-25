#ifndef HEADER_AETEE_AXIOMS_NOTHING_H_INCLUDED
#define HEADER_AETEE_AXIOMS_NOTHING_H_INCLUDED
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

struct nothingFunctor {

    constexpr auto operator()(...) const
    {
        return nothingFunctor{};
    }

} /*struct nothingFunctor*/;

} /*namespace detail*/;

static constexpr auto nothing = detail::nothingFunctor{};

} /*namespace aetee*/;

#endif
