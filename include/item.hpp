#pragma once
#include <tuple_utils.hpp>
//#include <boost/mp11/algorithm.hpp> // needs boost 1.66
#include <utility>
#include <type_traits>

// Pre-declare template friends (see https://isocpp.org/wiki/faq/templates#template-friends)
namespace nicudo
{
    template<typename Key, typename Args> class Item;
}
template<typename Key, typename Args> std::ostream& operator<<(std::ostream&, const nicudo::Item<Key, Args>&);
template<typename Key, typename Args>
struct std::hash<nicudo::Item<Key, Args>>
{
    size_t operator()(const nicudo::Item<Key, Args>& item) const;
};

namespace nicudo
{
    template<typename Key, typename Args>
    class Item
    {
    public:
        Item(Key&& key)
        : key_{std::forward<Key>(key)}
        {}
        Item(Key&& key, Args&& args)
        : key_{std::forward<Key>(key)}, args_{std::forward<Args>(args)}
        {}
        Item() = delete;

        auto Attributes()
        {
            //boost::mp11::mp_transform<std::tie, Key> keyRefs = key_;
            if constexpr (is_tuple<Key>::value && is_tuple<Args>::value)
                //return std::tuple_cat(tuple_ref(key_), tuple_ref(args_));
                return std::tuple_cat(key_, args_);
        }

    private:
        const Key key_;
        Args args_;

        friend std::ostream& operator<< <>(std::ostream&, const Item<Key, Args>&);
        friend struct std::hash<Item<Key, Args>>;

        friend bool operator==(const Item<Key, Args>& lhs, const Item<Key, Args>& rhs)
        {
            return lhs.key_ == rhs.key_;
        }
    };
}

template<typename Key, typename Args>
std::ostream& operator<<(std::ostream& os, const nicudo::Item<Key, Args> & item)
{
    os << '[' << item.key_ << ": " << item.args_ << ']';
}

template<typename Key, typename Args>
size_t std::hash<nicudo::Item<Key, Args>>::operator()(const nicudo::Item<Key, Args>& item) const
{
    return std::hash<Key>{}(item.key_);
}
