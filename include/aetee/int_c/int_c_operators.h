#ifndef HEADER_AETEE_INT_C_INT_C_OPERATORS_H_INCLUDED
#define HEADER_AETEE_INT_C_INT_C_OPERATORS_H_INCLUDED

namespace aetee {

template <typename T, T V>
constexpr auto operator++(int_t<T, V>)
{
    return int_t<T, (V + 1)>{};
}

template <typename T, T V>
constexpr auto operator--(int_t<T, V>)
{
    return int_t<T, (V - 1)>{};
}

template <typename T, T V>
constexpr auto operator+(int_t<T, V>)
{
    return int_t<T, (+V)>{};
}

template <typename T, T V>
constexpr auto operator-(int_t<T, V>)
{
    return int_t<T, (-V)>{};
}

template <typename T, T V>
constexpr auto operator~(int_t<T, V>)
{
    return int_t<T, (~V)>{};
}

template <typename T, T V>
constexpr auto operator!(int_t<T, V>)
{
    return int_t<T, (!V)>{};
}

template <typename T, T V, typename U>
constexpr auto operator+(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V + std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator+(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V + W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator-(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V - std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator-(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V - W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator*(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V * std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator*(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V * W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator%(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V % std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator%(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V % W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator/(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V / std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator/(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V / W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator&(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V & std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator&(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V & W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator|(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V | std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator|(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V | W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator^(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V ^ std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator^(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V ^ W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator<<(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V << std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator<<(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V << W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator>>(int_t<T, V>, U&& w)
{
    return int_t<std::common_type_t<T, U>, (V >> std::forward<U>(w))>{};
}

template <typename T, T V, typename U, U W>
constexpr auto operator>>(int_t<T, V>, int_t<U, W>)
{
    return int_t<std::common_type_t<T, U>, (V >> W)>{};
}

template <typename T, T V, typename U>
constexpr auto operator&&(int_t<T, V>, U&& w)
{
    return bool_c<(V && std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator&&(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V && W)>;
}

template <typename T, T V, typename U>
constexpr auto operator||(int_t<T, V>, U&& w)
{
    return bool_c<(V || std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator||(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V || W)>;
}

template <typename T, T V, typename U>
constexpr auto operator==(int_t<T, V>, U&& w)
{
    return bool_c<(V == std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator==(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V == W)>;
}

template <typename T, T V, typename U>
constexpr auto operator!=(int_t<T, V>, U&& w)
{
    return bool_c<(V != std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator!=(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V != W)>;
}

template <typename T, T V, typename U>
constexpr auto operator<(int_t<T, V>, U&& w)
{
    return bool_c<(V < std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator<(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V < W)>;
}

template <typename T, T V, typename U>
constexpr auto operator>(int_t<T, V>, U&& w)
{
    return bool_c<(V > std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator>(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V > W)>;
}

template <typename T, T V, typename U>
constexpr auto operator<=(int_t<T, V>, U&& w)
{
    return bool_c<(V <= std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator<=(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V <= W)>;
}

template <typename T, T V, typename U>
constexpr auto operator>=(int_t<T, V>, U&& w)
{
    return bool_c<(V >= std::forward<U>(w))>;
}

template <typename T, T V, typename U, U W>
constexpr auto operator>=(int_t<T, V>, int_t<U, W>)
{
    return bool_c<(V >= W)>;
}

} /*namespace aetee*/;

#endif
