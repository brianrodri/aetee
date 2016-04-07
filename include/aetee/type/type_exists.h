#ifndef HEADER_AETEE_TYPE_TYPE_EXISTS_H_INCLUDED
#define HEADER_AETEE_TYPE_TYPE_EXISTS_H_INCLUDED
#include <aetee/type/type_idx.h>
#include <aetee/int_c.h>

namespace aetee {

template<typename T, typename... L>
static constexpr auto type_exists_c = bool_c<(type_idx_c<T, L...> != arity_c<L...>)>;

} /*namespace aetee*/;

#endif
