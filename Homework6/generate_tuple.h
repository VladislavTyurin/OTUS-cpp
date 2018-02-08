#pragma once

#include <tuple>

template<typename T, unsigned N, typename... REST>
struct generate_tuple_type
{
    typedef typename generate_tuple_type<T, N-1, T, REST...>::type type;
};

template<typename T, typename... REST>
struct generate_tuple_type<T, 0, REST...>
{
    typedef std::tuple<REST...> type;
};