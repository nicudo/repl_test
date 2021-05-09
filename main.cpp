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
    std::cout
        << "\nstd::apply (cppreference) tests"
        << "\n-------------------------------\n";

    // OK
    std::cout << std::apply(add, std::pair(1, 2)) << '\n';
 
    // Error: can't deduce the function type
    // std::cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << '\n'; 
 
    // OK
    std::cout << std::apply(add_lambda, std::pair(2.0f, 3.0f)) << '\n'; 
 
    // advanced example
    std::tuple myTuple(25, "Hello", 9.31f, 'c');
    std::cout << myTuple << '\n';

    std::cout
        << "\ntuple hash tests"
        << "\n----------------\n";

    // Tuple hash test
    std::unordered_map<std::tuple<float, int>, std::string> mmap;
    mmap[{1.2f, 5}] = "t1";
    mmap[{1.2f, 5}] = "t2";
    mmap[{1.1f, 5}] = "t3";
    mmap[{1.2f, 4}] = "t4";

    for (auto&& [k,v] : mmap)
        std::cout << k << ": " << v << '\n';

    if (auto&&[it, res] = mmap.try_emplace({1.1f, 1}, "t5"); !res)
        std::cout << "Error 1" << '\n';
    if (auto&&[it, res] = mmap.try_emplace({1.1f, 5}, "t6"); res)
        std::cout << "Error 2" << '\n';

    for (auto&& [k,v] : mmap)
        std::cout << k << ":1: " << v << '\n';

    // Item tests
    std::cout
        << "\nItem tests"
        << "\n----------\n";

    using FItem = nicudo::Item<std::tuple<int, char>, std::tuple<std::string>>;
    FItem
        i1 = {std::make_tuple(1, 'a'), std::make_tuple(std::string("test"))},
        i2 = {std::make_tuple(1, 'a'), std::make_tuple(std::string("test2"))};
    std::cout
        << i1 << '\n'
        << i2 << '\n';

    std::unordered_set<FItem> us;
    if (auto it = us.emplace(i1); it.second)
        std::cout << "ok: " << *it.first << '\n';
    if (auto it = us.emplace(i2); !it.second)
        std::cout << "ok: " << *it.first << '\n';

    auto&& [a_int, a_char, a_string] = i2.Attributes();
    std::cout << "int=" << a_int
        << " char=" << a_char
        << " string=" << a_string << '\n';

    std::cout
        << "**before\n"
        << i2 << '\n';
    a_string = "modified";
    std::cout
        << "**after\n"
        << i2 << '\n';
    
    auto&& [a_int_copy, a_char_copy, a_string_copy] = i1.AttributesCopy();
    std::cout << "int=" << a_int_copy
        << " char=" << a_char_copy
        << " string=" << a_string_copy << '\n';

    std::cout
        << "**before\n"
        << i1 << '\n';
    a_int_copy = 2;
    a_char_copy = 'b';
    a_string_copy = "modified";
    std::cout
        << "**after\n"
        << i1 << '\n';

    FItem i1_copy = {std::make_tuple(a_int_copy, a_char_copy), std::make_tuple(a_string_copy)};
    std::cout
        << "**copy\n"
        << i1_copy << '\n';
}
