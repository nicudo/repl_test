#pragma once
#include <boost/functional/hash.hpp>
#include <utility>
#include <tuple>
#include <ostream>

/***************************************************************************************
*    Original Source: Example at https://en.cppreference.com/w/cpp/utility/apply
***************************************************************************************/
template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}

/***************************************************************************************
*    Author: Nicolae Tudor
*    Date: 2020
*    Availability: https://github.com/nicudo
***************************************************************************************/
template<typename... Ts>
struct std::hash<std::tuple<Ts...>>
{
    size_t operator()(std::tuple<Ts...> const& theTuple) const
    {
        size_t seed=0;
        std::apply([&seed](Ts const&... tupleArgs)
        {
            (boost::hash_combine(seed, boost::hash_value(tupleArgs)), ...);
        }, theTuple);
        return seed;
    }
};

/***************************************************************************************
*    Original Source: An answer at https://stackoverflow.com/questions/13101061/detect-if-a-type-is-a-stdtuple/48458312
***************************************************************************************/
template <typename> struct is_tuple: std::false_type {};
template <typename ...T> struct is_tuple<std::tuple<T...>>: std::true_type {};

template<typename ...T, size_t... I>
auto tuple_ref(std::tuple<T...>& t ,  std::index_sequence<I...>)
{ return std::tie(std::get<I>(t)...) ;}