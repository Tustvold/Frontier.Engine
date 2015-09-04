#include <type_traits>
template <bool... b> struct static_all_of;

// do recursion if the first argument is true
template <bool... tail>
struct static_all_of<true, tail...> : static_all_of<tail...>{};

// end recursion if first argument is false
template <bool... tail>
struct static_all_of<false, tail...> : std::false_type{};

// end recursion if no more arguments need to be processed
template <> struct static_all_of<> : std::true_type{};

template <bool... b> struct static_one_of;

template <bool... tail>
struct static_one_of<true, tail...> : std::true_type {};

template <bool... tail>
struct static_one_of<false, tail...> : static_one_of<tail...> {};

template <> struct static_one_of<> : std::false_type{};