#ifndef HEADER_AETEE_TYPE_CONSTANT_H_INCLUDED
#define HEADER_AETEE_TYPE_CONSTANT_H_INCLUDED

namespace aetee {

template <typename T>
struct type_t { using type = T; };

template <typename T>
static constexpr auto type_c = type_t<T>{};

} /*namespace aetee*/;

#endif
