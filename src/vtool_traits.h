//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------------------------ o
    Utilities for improved vector traits
  o ------------------------------------ o
*/
//////////////////////////////////////////////////////////////////////////////

#ifndef __VTOOL_TRAITS_H__
#define __VTOOL_TRAITS_H__

#include <vector>
#include <memory>
#include <complex>
#include <stdexcept>
#include <type_traits>

namespace vtool {

//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------------- o
    Metaprogramming Utilities
  o ------------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

// --------------------------- combination<...> --------------------------- //
template <typename...>
struct combination: std::true_type {};

template <typename B1>
struct combination<B1>: B1 {};

template <typename B1, typename... Bs>
struct combination<B1, Bs...>: std::conditional<
    bool(B1::value), combination<Bs...>, B1
>::type {};

// ----------------------- rebinded_alloc<From, To> ----------------------- //
template <typename AllocFrom, typename To>
using rebinded_alloc
    = typename std::allocator_traits<AllocFrom>::template rebind_alloc<To>;

// ---------------------------- is_vector<...> ---------------------------- //
template <typename T>
struct _is_vector: std::false_type {};

template <typename T, typename Allocator>
struct _is_vector<std::vector<T, Allocator>>: std::true_type {};

template <typename... Ts>
struct is_vector: std::enable_if<
    combination<_is_vector<Ts>...>::value, bool
> {};

// ------------------- is_convertible_alloc<From, To...> ------------------ //
template <typename From, typename... To>
struct is_convertible_alloc: std::enable_if<
    combination<std::is_same<
        rebinded_alloc<From, typename std::allocator_traits<To>::value_type>, To
    >...>::value, bool
> {};

// ------------------------- decltype_vector<...> ------------------------- //
template <typename V1, typename... Vs>
struct decltype_vector
{
    template <typename is_vector<V1, Vs...>::type = true,
              typename is_convertible_alloc<typename V1::allocator_type,
                                            typename Vs::allocator_type...>::type = true>
    using _dummy = void;

    using value_type
        = typename std::common_type<typename V1::value_type,
                                    typename Vs::value_type...>::type;
    using allocator_type
        = rebinded_alloc<typename V1::allocator_type, value_type>;
    
    using type = std::vector<value_type, allocator_type>;
};

template <typename T1, typename T2, typename Alloc1, typename Alloc2>
using decltype_vector_t = typename decltype_vector<
    std::vector<T1, Alloc1>, std::vector<T2, Alloc2>
>::type;

// -------------------------- is_arithmetic<...> -------------------------- //
template <typename... Ts>
struct is_arithmetic: std::enable_if<
    combination<std::is_arithmetic<Ts>...>::value, bool
> {};

// --------------------------- is_integral<...> --------------------------- //
template <typename... Ts>
struct is_integral: std::enable_if<
    combination<std::is_integral<Ts>...>::value, bool
> {};


}   // namespace vtool

#endif  // __VTOOL_TRAITS_H__