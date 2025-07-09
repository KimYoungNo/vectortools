//////////////////////////////////////////////////////////////////////////////
/*
  o -------------------------------- o
    Window Functions for std::vector
  o -------------------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

#ifndef __VTOOL_WINDOWS_H__
#define __VTOOL_WINDOWS_H__
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

namespace vtool {
    namespace windows {
    
    namespace _c
    {
        static const
        long double pi = M_PI;
    }
    namespace _hamming_c
    {
        static constexpr const
        long double a0 = 25.0l/46.0l;
    }
    namespace _blackman_c
    {
        static constexpr const
        long double a0 = 7938.0l/18608.0l,
                    a1 = 9240.0l/18608.0l,
                    a2 = 1430.0l/18608.0l;
    }

#define _typed_div(T, L, R) \
    (static_cast<T>(L) / R)

#define _n_domain(T, n, m)  \
    (_c::pi * _typed_div(T, n, m))

#define _1st_cosine_sum(T, n, N, a)   \
    (a - (1-a) * std::cos(2*_n_domain(T, n, N-1)))


#define sine_(T, n, N)  \
    std::sin(_n_domain(T, n, N-1))

#define hanning_(T, n, N)   \
    _1st_cosine_sum(T, n, N, 0.5)

#define hamming_(T, n, N)   \
    _1st_cosine_sum(T, n, N, _hamming_c::a0)

#define bartlett_(T, n, N)  \
    _typed_div(T, 2*n, N-1)

#define barthann_(T, n, N)  \
    _1st_cosine_sum(T, n, N, 0.62) + 0.48 * (_typed_div(T, n, N-1) - 0.5)

#define blackman_(T, n, N)                              \
    _blackman_c::a0                                     \
  - _blackman_c::a1 * std::cos(2*_n_domain(T, n, N-1))  \
  + _blackman_c::a2 * std::cos(4*_n_domain(T, n, N-1))


#define _WINDOWS_FUNCTION(_win)                     \
template <typename T = double,                      \
          typename Alloc = std::allocator<T>>       \
std::vector<T, Alloc>                               \
_win(const std::size_t N)                           \
{                                                   \
    std::vector<T, Alloc> win_vec(N, 1);            \
                                                    \
    if (N > 1) _CXX20_LIKELY                        \
        for (std::size_t n = 0; n < N/2; ++n)       \
            win_vec[n] = win_vec[N-n-1]             \
                = static_cast<T>(_win##_(T, n, N)); \
    return win_vec;                                 \
}

//////////////////////////////////////////////////////////////////////////////
// -------------------------- window functions ---------------------------- //
    _WINDOWS_FUNCTION(sine)
    _WINDOWS_FUNCTION(hanning)
    _WINDOWS_FUNCTION(hamming)
    _WINDOWS_FUNCTION(bartlett)
    _WINDOWS_FUNCTION(barthann)
    _WINDOWS_FUNCTION(blackman)

    }   // namespace windows
}   // namespace vtool

#undef _typed_div
#undef _n_domain
#undef _1st_cosine_sum

#undef sine_
#undef hanning_
#undef hamming_
#undef bartlett_
#undef barthann_
#undef blackman_

#undef _WINDOWS_FUNCTION

#endif  // __VTOOL_WINDOWS_H__