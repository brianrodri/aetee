#ifndef HEADER_AETEE_HOF_ZIP_H_INCLUDED
#define HEADER_AETEE_HOF_ZIP_H_INCLUDED

namespace aetee {

namespace detail {

template <size_t... I, typename... Tup>
static constexpr auto zip_impl(std::index_sequence<I...>, Tup&&... tup)
{
    return std::make_tuple(
        (index_c<I>, std::make_tuple(
            (type_c<Tup>, std::get<I>(std::forward<Tup>(tup)))...
            ))...
        );
}

};

struct zipFunctor {
    template <typename... Tup>
    auto operator()(Tup&&... tup) const
    {
        constexpr auto tupsizes = transform(std::make_tuple(type_c<Tup>...), lengthFunctor{});
        constexpr auto M = fold(tupsizes, 0, maxFunctor{});
        return zip_impl(std::make_index_sequence<M>, std::forward<Tup>(tup)...);
    }

    template <typename Dummy>
    struct longestFunctor {
        Dummy d;
        longestFunctor(Dummy&& d_) : d{d_} {};

        template <typename... Tup>
        auto operator()(Tup&&... tup) const
        {
            auto most = fold(transform(std::make_tuple(type_c<Tup>...), lengthFunctor{}), 0, maxFunctor{});
            auto normalized = std::make_tuple(
                concat(std::forward<Tup>(tup), replicate(d, most - lengthFunctor{}(type_c<Tup>)))...
                );
            return zipFunctor{}(normalized, std::make_index_sequence<sizeof...(Tup)>{});
        }
    };

    template <typename Dummy>
    static constexpr auto longestWithDummy(Dummy&& d)
    {
        return longestFunctor<Dummy>{std::forward<Dummy>(d)};
    }

    //static const decltype(auto) longest = longestWithDummy(type_c<void>);
};

static constexpr auto zip = zipFunctor{};

}; // namespace aetee

#endif
