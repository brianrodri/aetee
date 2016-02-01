#ifndef HEADER_AETEE_PRETTYPRINT_H_INCLUDED
#define HEADER_AETEE_PRETTYPRINT_H_INCLUDED
#include <aetee/aetee.h>
#include <tuple>

template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tup)
{
    aetee::for_each(tup, [&](const auto& v) { os << v << "  "; });
    return os;
}

#endif
