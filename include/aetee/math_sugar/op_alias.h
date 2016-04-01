#ifndef HEADER_AETEE_MATH_SUGAR_OP_ALIAS_H_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_OP_ALIAS_H_INCLUDED

namespace aetee {

namespace detail {

struct plusFunctor {       template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs + rhs; } };
struct minusFunctor {      template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs - rhs; } };
struct multipliesFunctor { template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs * rhs; } };
struct dividesFunctor {    template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs / rhs; } };
struct modulusFunctor {    template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs % rhs; } };
struct negateFunctor {     template <typename LH>              constexpr auto operator()(LH lhs) const         { return -lhs; }      };

struct equalToFunctor {      template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs == rhs; } };
struct notEqualToFunctor {   template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs != rhs; } };
struct greaterFunctor {      template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs > rhs; }  };
struct lessFunctor {         template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs < rhs; }  };
struct greaterEqualFunctor { template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs >= rhs; } };
struct lessEqualFunctor {    template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs <= rhs; } };

struct logicalAndFunctor { template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs && rhs; } };
struct logicalOrFunctor {  template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs || rhs; } };
struct logicalNotFunctor { template <typename LH>              constexpr auto operator()(LH lhs) const         { return !lhs; }       };

struct bitAndFunctor { template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs & rhs; } };
struct bitOrFunctor {  template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs | rhs; } };
struct bitXorFunctor { template <typename LH, typename RH> constexpr auto operator()(LH lhs, RH rhs) const { return lhs ^ rhs; } };

} /*namespace detail*/;

static constexpr auto plus = detail::plusFunctor{};
static constexpr auto minus = detail::minusFunctor{};
static constexpr auto multiplies = detail::multipliesFunctor{};
static constexpr auto divides = detail::dividesFunctor{};
static constexpr auto modulus = detail::modulusFunctor{};
static constexpr auto negate = detail::negateFunctor{};

static constexpr auto equal_to = detail::equalToFunctor{};
static constexpr auto not_equal_to = detail::notEqualToFunctor{};
static constexpr auto less = detail::lessFunctor{};
static constexpr auto greater = detail::greaterFunctor{};
static constexpr auto less_equal = detail::lessEqualFunctor{};
static constexpr auto greater_equal = detail::greaterEqualFunctor{};

static constexpr auto logical_and = detail::logicalAndFunctor{};
static constexpr auto logical_or = detail::logicalOrFunctor{};
static constexpr auto logical_not = detail::logicalNotFunctor{};

static constexpr auto bit_and = detail::bitAndFunctor{};
static constexpr auto bit_or = detail::bitOrFunctor{};
static constexpr auto bit_xor = detail::bitXorFunctor{};

} /*namespace aetee*/;

#endif
