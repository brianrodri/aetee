#ifndef HEADER_AETEE_AXIOMS_SIZEOF_H_INCLUDED
#define HEADER_AETEE_AXIOMS_SIZEOF_H_INCLUDED
#include <aetee/type_c.h>
#include <type_traits>

namespace aetee {

namespace detail {

//! Returns a compile-time sizeof value for an input type
struct sizeOfFunctor {
    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return index_c<sizeof(std::decay_t<T>)>;
    }

    template <typename T>
    constexpr auto operator()(T&&) const
    {
        return index_c<sizeof(std::decay_t<T>)>;
    }
} /*struct sizeOfFunctor*/;

} /*namespace detail*/;

static constexpr auto sizeof_ = detail::sizeOfFunctor{};

} /*namespace aetee*/;

#endif
