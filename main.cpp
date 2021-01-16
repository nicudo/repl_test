// example from: https://en.cppreference.com/w/cpp/utility/apply
// added tuple hash
#include <boost/functional/hash.hpp>
#include <iostream>
#include <tuple>
#include <utility>
#include <unordered_map>
#include <string>
 
int add(int first, int second) { return first + second; }
 
template<typename T>
T add_generic(T first, T second) { return first + second; }
 
auto add_lambda = [](auto first, auto second) { return first + second; };
 
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

int main()
{
    // OK
    std::cout << std::apply(add, std::pair(1, 2)) << '\n';
 
    // Error: can't deduce the function type
    // std::cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << '\n'; 
 
    // OK
    std::cout << std::apply(add_lambda, std::pair(2.0f, 3.0f)) << '\n'; 
 
    // advanced example
    std::tuple myTuple(25, "Hello", 9.31f, 'c');
    std::cout << myTuple << '\n';

    std::unordered_map<std::tuple<float, int>, std::string> mmap;
    mmap[std::make_tuple(1.2f, 5)] = "t1";
    mmap[std::make_tuple(1.2f, 5)] = "t2";
    mmap[std::make_tuple(1.1f, 5)] = "t3";
    mmap[std::make_tuple(1.2f, 4)] = "t4";

    for (auto&& [k,v] : mmap)
        std::cout << k << ": " << v << "\n";

}
