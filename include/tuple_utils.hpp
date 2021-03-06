#pragma once
#include <boost/functional/hash.hpp>
#include <utility>
#include <tuple>
#include <functional>
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
*    Original Source: An answer at https://stackoverflow.com/a/48458312
***************************************************************************************/
template <typename> struct is_tuple: std::false_type {};
template <typename ...T> struct is_tuple<std::tuple<T...>>: std::true_type {};

/***************************************************************************************
*    Original Source: https://stackoverflow.com/a/7858971
***************************************************************************************/
template <int...>
struct Seq {};

template <int n, int... s>
struct Gens : Gens<n-1, n-1, s...> {};

template <int... s>
struct Gens<0, s...> {
  typedef Seq<s...> Type;
};

/***************************************************************************************
*    Original Source (removed trailing return type): https://stackoverflow.com/a/13071033
***************************************************************************************/
template <int... s, typename Tuple>
auto ref_tuple_impl(Seq<s...> seq, Tuple& tup)
{
    return std::make_tuple(std::ref(std::get<s>(tup))...);
}

template <typename Tuple>
auto ref_tuple(Tuple& tup)
{
    return ref_tuple_impl(typename Gens<std::tuple_size<Tuple>::value>::Type(), tup);
}
