#include <tuple_utils.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include <utility>
#include <tuple>
 
int add(int first, int second) { return first + second; }
 
template<typename T>
T add_generic(T first, T second) { return first + second; }
 
auto add_lambda = [](auto first, auto second) { return first + second; };

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

    // Tuple hash test
    std::unordered_map<std::tuple<float, int>, std::string> mmap;
    mmap[std::make_tuple(1.2f, 5)] = "t1";
    mmap[std::make_tuple(1.2f, 5)] = "t2";
    mmap[std::make_tuple(1.1f, 5)] = "t3";
    mmap[std::make_tuple(1.2f, 4)] = "t4";

    for (auto&& [k,v] : mmap)
        std::cout << k << ": " << v << "\n";

}
