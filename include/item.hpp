#pragma once
#include <tuple_utils.hpp>

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
        Item(Key key)
        : key_{key}
        {}
        Item(Key key, Args args)
        : key_{key}, args_{args}
        {}
        Item() = delete;

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
