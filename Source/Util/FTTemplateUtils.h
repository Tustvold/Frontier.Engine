#pragma once
#include <type_traits>
#include <memory>

template <bool... b>
struct static_all_of;

// do recursion if the first argument is true
template <bool... tail>
struct static_all_of<true, tail...> : static_all_of<tail...> {
};

// end recursion if first argument is false
template <bool... tail>
struct static_all_of<false, tail...> : std::false_type {
};

// end recursion if no more arguments need to be processed
template <>
struct static_all_of<> : std::true_type {
};

template <bool... b>
struct static_one_of;

template <bool... tail>
struct static_one_of<true, tail...> : std::true_type {
};

template <bool... tail>
struct static_one_of<false, tail...> : static_one_of<tail...> {
};

template <>
struct static_one_of<> : std::false_type {
};


template <typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del>
static_unique_ptr_cast(std::unique_ptr<Base, Del>&& p) {
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
}

template <typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del>
dynamic_unique_ptr_cast(std::unique_ptr<Base, Del>&& p) {
    if (Derived* result = dynamic_cast<Derived *>(p.get())) {
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}
