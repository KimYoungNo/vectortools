//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------------------------------------------ o
    Overloading Arithmetic Unary Operators for std::vector
  o ------------------------------------------------------ o
*/
//////////////////////////////////////////////////////////////////////////////

#ifndef __VTOOL_OPERATOR_H__
#define __VTOOL_OPERATOR_H__

#include <vector>
#include <algorithm>
#include <type_traits>

#include "vtool_utils.h"
#include "vtool_traits.h"

#ifdef NO_VECTOR_LENGTH_CHECK
#   define _vtool_length_check(lhv, rhv)
#else
#   define _vtool_length_check(lhv, rhv) if (!vtool::isSameSize(lhv, rhv)) vtool::throw_vector_length_error(__func__)
#endif

// ------------------------------ operator+= ------------------------------ //
// std::vector<arithmetic_type> += std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator+=(std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    _vtool_length_check(lhv, rhv);

    typename std::vector<T1, Alloc1>::iterator lIter = lhv.begin();
    typename std::vector<T1, Alloc1>::const_iterator lIter_end = lhv.cend();
    typename std::vector<T2, Alloc2>::const_iterator rIter = rhv.cbegin();

    while (lIter != lIter_end)
        *(lIter++) += *(rIter++);
        
    return lhv;
}

template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator+=(std::vector<T1, Alloc1>&& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) += rhv;
}

// std::vector<arithmetic_type> += arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator+=(std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    for (T1& value: lhv) value += rhs;
    return lhv;
}

template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator+=(std::vector<T1, Alloc1>&& lhv, const T2 rhs)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) += rhs;
}

// ------------------------------ operator-= ------------------------------ //
// std::vector<arithmetic_type> -= std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator-=(std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    _vtool_length_check(lhv, rhv);

    typename std::vector<T1, Alloc1>::iterator lIter = lhv.begin();
    typename std::vector<T1, Alloc1>::const_iterator lIter_end = lhv.cend();
    typename std::vector<T2, Alloc2>::const_iterator rIter = rhv.cbegin();

    while (lIter != lIter_end)
        *(lIter++) -= *(rIter++);

    return lhv;
}

template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator-=(std::vector<T1, Alloc1>&& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return static_cast<std::vector<T1>&>(lhv) -= rhv;
}

// std::vector<arithmetic_type> -= arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator-=(std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    for (T1& value: lhv) value -= rhs;
    return lhv;
}

template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator-=(std::vector<T1, Alloc1>&& lhv, const T2 rhs)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) -= rhs;
}

// ------------------------------ operator*= ------------------------------ //
// std::vector<arithmetic_type> *= std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator*=(std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    _vtool_length_check(lhv, rhv);

    typename std::vector<T1, Alloc1>::iterator lIter = lhv.begin();
    typename std::vector<T1, Alloc1>::const_iterator lIter_end = lhv.cend();
    typename std::vector<T2, Alloc2>::const_iterator rIter = rhv.cbegin();

    while (lIter != lIter_end)
        *(lIter++) *= *(rIter++);
        
    return lhv;
}

template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator*=(std::vector<T1, Alloc1>&& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) *= rhv;
}

// std::vector<arithmetic_type> *= arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator*=(std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    for (T1& value: lhv) value *= rhs;
    return lhv;
}

template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator*=(std::vector<T1, Alloc1>&& lhv, const T2 rhs)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) *= rhs;
}

// ------------------------------ operator/= ------------------------------ //
// std::vector<arithmetic_type> /= std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator/=(std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    _vtool_length_check(lhv, rhv);

    typename std::vector<T1, Alloc1>::iterator lIter = lhv.begin();
    typename std::vector<T1, Alloc1>::const_iterator lIter_end = lhv.cend();
    typename std::vector<T2, Alloc2>::const_iterator rIter = rhv.cbegin();

    while (lIter != lIter_end)
        *(lIter++) /= *(rIter++);
        
    return lhv;
}

template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator/=(std::vector<T1, Alloc1>&& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) /= rhv;
}

// std::vector<arithmetic_type> /= arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<T1, Alloc1>&
operator/=(std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    for (T1& value: lhv) value /= rhs;
    return lhv;
}

template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline std::vector<T1, Alloc1>&
operator/=(std::vector<T1, Alloc1>&& lhv, const T2 rhs)
{
    return static_cast<std::vector<T1, Alloc1>&>(lhv) /= rhs;
}

//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------------------------------------------- o
    Overloading Arithmetic Binary Operators for std::vector
  o ------------------------------------------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

// ------------------------------- operator+ ------------------------------ //
// std::vector<arithmetic_type> + std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
operator+(const std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
          (lhv.cbegin(), lhv.cend()) += rhv;
}

// std::vector<arithmetic_type> + arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1,
                                vtool::rebinded_alloc<Alloc1, T2>>
operator+(const std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1,
                                    vtool::rebinded_alloc<Alloc1, T2>>
          (lhv.cbegin(), lhv.cend()) += rhs;
}

// arithmetic_type + std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2,
                                vtool::rebinded_alloc<Alloc2, T1>, Alloc2>
operator+(const T1 lhs, const std::vector<T2, Alloc2>& rhv)
{
    using vType = vtool::decltype_vector_t<T1, T2,
                                           vtool::rebinded_alloc<Alloc2, T1>, Alloc2>;
    return vType(rhv.size(),
                 static_cast<typename vType::value_type>(lhs)) += rhv;
}

// ------------------------------- operator- ------------------------------ //
// std::vector<arithmetic_type> - std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
operator-(const std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
          (lhv.cbegin(), lhv.cend()) -= rhv;
}

// std::vector<arithmetic_type> - arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1,
                                    vtool::rebinded_alloc<Alloc1, T2>>
operator-(const std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1,
                                    vtool::rebinded_alloc<Alloc1, T2>>
          (lhv.cbegin(), lhv.cend()) -= rhs;
}

// arithmetic_type - std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2,
                                vtool::rebinded_alloc<Alloc2, T1>, Alloc2>
operator-(const T1 lhs, const std::vector<T2, Alloc2>& rhv)
{
    using vType = vtool::decltype_vector_t<T1, T2,
                                           vtool::rebinded_alloc<Alloc2, T1>, Alloc2>;
    return vType(rhv.size(),
                 static_cast<typename vType::value_type>(lhs)) -= rhv;
}

// ------------------------------- operator* ------------------------------ //
// std::vector<arithmetic_type> * std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
operator*(const std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
          (lhv.cbegin(), lhv.cend()) *= rhv;
}

// std::vector<arithmetic_type> * arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1,
                                    vtool::rebinded_alloc<Alloc1, T2>>
operator*(const std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1,
                                    vtool::rebinded_alloc<Alloc1, T2>>
          (lhv.cbegin(), lhv.cend()) *= rhs;
}

// arithmetic_type * std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2,
                                vtool::rebinded_alloc<Alloc2, T1>, Alloc2>
operator*(const T1 lhs, const std::vector<T2, Alloc2>& rhv)
{
    using vType = vtool::decltype_vector_t<T1, T2,
                                           vtool::rebinded_alloc<Alloc2, T1>, Alloc2>;
    return vType(rhv.size(),
                 static_cast<typename vType::value_type>(lhs)) *= rhv;
}

// ------------------------------- operator/ ------------------------------ //
// std::vector<arithmetic_type> / std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc1, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
operator/(const std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1, Alloc2>
          (lhv.cbegin(), lhv.cend()) /= rhv;
}

// std::vector<arithmetic_type> / arithmetic_type
template <typename T1, typename T2, typename Alloc1,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2, Alloc1,
                                vtool::rebinded_alloc<Alloc1, T2>>
operator/(const std::vector<T1, Alloc1>& lhv, const T2 rhs)
{
    return vtool::decltype_vector_t<T1, T2, Alloc1,
                                    vtool::rebinded_alloc<Alloc1, T2>>
          (lhv.cbegin(), lhv.cend()) /= rhs;
}

// arithmetic_type / std::vector<arithmetic_type>
template <typename T1, typename T2, typename Alloc2,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
inline vtool::decltype_vector_t<T1, T2,
                                vtool::rebinded_alloc<Alloc2, T1>, Alloc2>
operator/(const T1 lhs, const std::vector<T2, Alloc2>& rhv)
{
    using vType = vtool::decltype_vector_t<T1, T2,
                                           vtool::rebinded_alloc<Alloc2, T1>, Alloc2>;
    return vType(rhv.size(),
                 static_cast<typename vType::value_type>(lhs)) /= rhv;
}

#include <iostream>
// ------------------------------ operator<< ------------------------------ //
template <typename T, typename Alloc>
std::ostream&
operator<<(std::ostream& out, const std::vector<T, Alloc>& vec)
{
    for (const T& value: vec) out << value << "\t";
    return out;
}

#undef _vtool_length_check

#endif  // __VTOOL_OPERATOR_H__