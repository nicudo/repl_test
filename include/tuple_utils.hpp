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
