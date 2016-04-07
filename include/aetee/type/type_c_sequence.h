#ifndef HEADER_AETEE_TYPE_C_SEQUENCE_H_INCLUDED
#define HEADER_AETEE_TYPE_C_SEQUENCE_H_INCLUDED
#include <aetee/type/type_c.h>

namespace aetee {

template <typename... T>
using type_c_sequence_t = std::tuple<type_t<T>...>;

template <typename... T>
static constexpr auto type_c_sequence = type_c_sequence_t<T...>{};

} /*namespace aetee*/; 

#endif
