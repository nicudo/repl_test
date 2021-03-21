#include <item.hpp>
#include <tuple_utils.hpp>
#include <unordered_map>
#include <unordered_set>
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
    mmap[{1.2f, 5}] = "t1";
    mmap[{1.2f, 5}] = "t2";
    mmap[{1.1f, 5}] = "t3";
    mmap[{1.2f, 4}] = "t4";

    for (auto&& [k,v] : mmap)
        std::cout << k << ": " << v << "\n";

    if (auto&&[it, res] = mmap.try_emplace({1.1f, 1}, "t5"); !res)
        std::cout << "Error 1" << std::endl;
    if (auto&&[it, res] = mmap.try_emplace({1.1f, 5}, "t6"); res)
        std::cout << "Error 2" << std::endl;

    for (auto&& [k,v] : mmap)
        std::cout << k << ":1: " << v << "\n";

    nicudo::Item i1(std::make_tuple(1, 'a'), std::make_tuple(std::string("test")));
    std::cout << i1 << std::endl;

    nicudo::Item i2(std::make_tuple(1, 'a'), std::make_tuple(std::string("test2")));
    std::cout << i2 << std::endl;

    //std::unordered_set us({i1, i2});
}
