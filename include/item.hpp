#pragma once
#include <tuple_utils.hpp>

// Pre-declare template friends (see https://isocpp.org/wiki/faq/templates#template-friends)
namespace nicudo
{
    template<typename Key, typename Args> class Item;
}
template<typename Key, typename Args> std::ostream& operator<<(std::ostream&, nicudo::Item<Key, Args> const&);
template<typename Key, typename Args>
struct std::hash<nicudo::Item<Key, Args>>
{
    size_t operator()(nicudo::Item<Key, Args> const& item) const;
};

namespace nicudo
{

    template<typename Key, typename Args>
    class Item
    {
    public:
        Item(Key key)
        : key_(key)
        {}
        Item(Key key, Args args)
        : key_(key), args_(args)
        {}

        Item() = delete;

    private:
        Key key_;
        Args args_;

        friend std::ostream& operator<< <>(std::ostream&, Item<Key, Args> const&);
        friend struct std::hash<Item<Key, Args>>;
    };
}

template<typename Key, typename Args>
std::ostream& operator<<(std::ostream& os, nicudo::Item<Key, Args> const& item)
{
    os << '[' << item.key_ << ": " << item.args_ << ']';
}

template<typename Key, typename Args>
size_t std::hash<nicudo::Item<Key, Args>>::operator()(nicudo::Item<Key, Args> const& item) const
{
    return std::hash(item.key_);
}
