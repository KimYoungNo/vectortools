//////////////////////////////////////////////////////////////////////////////
/*
  o --------------------------------- o
    Utility Functions for std::vector
  o --------------------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

#ifndef __VTOOL_UTILS_H__
#define __VTOOL_UTILS_H__

#include <string>
#include <vector>
#include <complex>
#include <cstddef>
#include <type_traits>

#include <memory>
#include <cstring>

#include <cmath>
#include <numeric>
#include <algorithm>

#include "vtool_traits.h"

namespace vtool {

/* Syntax: vtool::isSameSize(std::vector lhv, std::vector rhv);
 * Return: Boolean value indicating whether the sizes of lhv and rhv are the same.
 */
template <typename T1, typename T2,
          typename Alloc1, typename Alloc2>
_CXX20_CONSTEXPR
inline bool
isSameSize(const std::vector<T1, Alloc1>& lhv, const std::vector<T2, Alloc2>& rhv)
{
    return lhv.size() == rhv.size();
}

/* Syntax: vtool::sum(std::vector vec);
 * Return: Sum of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
VTOOL_DBL
sum(const std::vector<T, Alloc>& vec)
{
    VTOOL_DBL SUM = 0;
    
    for (const T value: vec)
        SUM += static_cast<VTOOL_DBL>(value);
    
    return SUM;
}

/* Syntax: vtool::sum(std::vector vec, UnaryOp op);
 * Return: Sum of the operated elements in the input vector.
 */
template <typename T, typename Alloc, typename UnaryOp,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
VTOOL_DBL
sum(const std::vector<T, Alloc>& vec, const UnaryOp& op)
{
    VTOOL_DBL SUM = 0;
    
    for (const T value: vec)
        SUM += static_cast<VTOOL_DBL>(op(value));
    
    return SUM;
}

/* Syntax: vtool::mean(std::vector vec);
 * Return: Mean value of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
inline VTOOL_DBL
mean(const std::vector<T, Alloc>& vec)
{   
    return vtool::sum(vec) / static_cast<T>(vec.size());
}

/* Syntax: vtool::norm(std::vector vec);
 * Return: Magnitude of the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
inline VTOOL_DBL
norm(const std::vector<T, Alloc>& vec)
{
    return std::sqrt(
        vtool::sum(vec, [](const T value){
            return value*value;
        })
    );
}

/* Syntax: vtool::rms(std::vector vec);
 * Return: Root mean square value of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
VTOOL_DBL
rms(const std::vector<T, Alloc>& vec)
{
    const size_t len = vec.size();
    
    return std::sqrt(
        vtool::sum(vec, [len](const T value){
            return value*value / static_cast<T>(len);
        })
    );
}

/* Syntax: vtool::max(std::vector vec);
 * Return: Maximum value of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
T
max(const std::vector<T, Alloc>& vec)
{
    T MAX = vec[0];

    for (const T value: vec)
        MAX = value > MAX ? value : MAX;

    return MAX;
}

/* Syntax: vtool::min(std::vector vec);
 * Return: Minimum value of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
T
min(const std::vector<T, Alloc>& vec)
{
    T MIN = vec[0];

    for (const T value: vec)
        MIN = value < MIN ? value : MIN;

    return MIN;
}

#define _ABS(value) ((value) > 0 ? (value) : -(value))

/* Syntax: vtool::median(std::vector vec);
 * Return: Median value of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
inline T
median(const std::vector<T, Alloc>& vec)
{
    std::vector<T, Alloc> med_vec(vec);
    std::sort(med_vec.begin(), med_vec.end());

    return med_vec[vec.size()/2 - (1-vec.size()%2)];
}

/* Syntax: vtool::abs(std::vector vec);
 * Return: Absolute value of the elements in the input vector.
 */
template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
std::vector<T, Alloc>
abs(const std::vector<T, Alloc>& vec)
{
    std::vector<T, Alloc> abs_vec(vec);
    for (T& value: abs_vec) value = _ABS(value);

    return abs_vec;
}

#undef _ABS

// speciallized for complex vector
template <typename C, typename AllocC,
          typename Alloc = std::allocator<C>>
std::vector<C, Alloc>
abs(const std::vector<std::complex<C>, AllocC>& vec)
{
    const std::size_t N = vec.size();
    std::vector<C, Alloc> abs_vec(N, 0);
    
    for (std::size_t n = 0; n < N; ++n)
        abs_vec[n] = std::abs(vec[n]);
    
    return abs_vec;
}

/* Syntax: vtool::differential(std::vector vec);
 * Return: std::vector containing differential value of the elements
 *         in the input vector.
 */
template <typename T, typename Alloc>
_CXX20_CONSTEXPR
std::vector<T, Alloc>
differential(const std::vector<T, Alloc>& vec)
{
    std::vector<T, Alloc> diff_vec(vec);
    std::adjacent_difference(diff_vec.cbegin(), diff_vec.cend(),
                                                diff_vec.begin());
    return diff_vec;
}

/* Syntax: vtool::duplicate_append(std::vector vec, std::size_t num=1);
 * Return: std::vector appended with itself "num" times.
 */
template <typename T, typename Alloc>
_CXX20_CONSTEXPR
std::vector<T, Alloc>
duplicate_append(const std::vector<T, Alloc>& vec, const std::size_t num=1)
{
    const std::size_t N = vec.size();
    const std::size_t M = N * num;
    std::vector<T, Alloc> dup_vec(M, 0);

    for (std::size_t n = 0; n < M; ++n)
        dup_vec[n] = vec[n%N];

    return dup_vec;
}

/* Syntax: vtool::interleave(std::vector vec, std::size_t ch);
 * Return: std::vector with elements interleaved in periods of "ch".
 */
template <typename T, typename Alloc>
std::vector<T, Alloc>
interleave(const std::vector<T, Alloc>& vec, const std::size_t ch)
{
    const std::size_t N = vec.size();
    std::vector<T, Alloc> il_vec(N, 0);

    for (std::size_t n = 0; n < N; ++n)
        il_vec[n] = vec[n*ch - (N-1)*(n*ch/N)];

    return il_vec;
}

/* Syntax: vtool::apply(std::vector vec, UnaryOp fn);
 * Return: std::vector with elements applied "fn" from "vec".
 */
template <typename T, typename Alloc, typename UnaryOp>
_CXX20_CONSTEXPR
std::vector<T, Alloc>
apply(const std::vector<T, Alloc>& vec, const UnaryOp& op)
{
    std::vector<T, Alloc> op_vec(vec);
    
    for (T& value: op_vec)
        value = op(value);

    return op_vec;
}

/* Syntax: vtool::vector_cast<value_type>(std::vector vec);
 * Return: std::vector with elements casted to the specified value_type.
 */
template <typename To, typename From, typename AllocFrom,
          typename AllocTo = vtool::rebinded_alloc<AllocFrom, To>,
          typename std::enable_if<!std::is_same<To, From>::value, bool>::type = true>
_CXX20_CONSTEXPR
inline std::vector<To, AllocTo>
vector_cast(const std::vector<From, AllocFrom>& vec)
{
    return std::vector<To, AllocTo>(vec.cbegin(), vec.cend());
}

//specialized for same value type
template <typename T, typename Alloc>
_CXX20_CONSTEXPR
__forceinline std::vector<T, Alloc>
vector_cast(const std::vector<T, Alloc>& vec)
{
    return vec;
}

/* Syntax: vtool::linspace(arithmetic_type start, arithmetic_type stop, std::size_t num, bool endpoint);
 * Return: std::vector containing "num" values ranging from "start" to "stop".
 *         If endpoint is true, the returned vector includes the "stop" value.
 *         Otherwise, the "stop" value is excluded from the returned vector.
 */
template <typename T1, typename T2,
          typename Alloc = std::allocator<VTOOL_DBL>,
          typename vtool::is_arithmetic<T1, T2>::type = true>
_CXX20_CONSTEXPR
std::vector<VTOOL_DBL, Alloc>
linspace(const T1 start, const T2 stop, const std::size_t num,
         const bool endpoint=true)
{
    const std::size_t  D = num - static_cast<std::size_t>(endpoint);
    const VTOOL_DBL step = (stop - start) /
                            static_cast<VTOOL_DBL>(D + (D==0));
    std::vector<VTOOL_DBL, Alloc> lin_vec(num, 0);

    for (std::size_t n = 0; n < num; ++n)
        lin_vec[n] = static_cast<VTOOL_DBL>(start + step*n);

    return lin_vec;
}

//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------- o
    Exception Functions
  o ------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

[[noreturn]]
inline void
throw_vector_length_error(const char *FuncName)
{
    throw std::length_error(
        std::string("Invalid Vector Length: ").append(FuncName, std::strlen(FuncName))
    );
}

}   // namespace vtool

#endif  // __VTOOL_UTILS_H__