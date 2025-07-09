//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------- o
    FFT for std::vector
  o ------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

#ifndef __VTOOL_FFT_H__
#define __VTOOL_FFT_H__

#include <vector>
#include <complex>
#include <cstddef>

#include "vtool_utils.h"
#include "vtool_traits.h"

#include "pocketfft/pocketfft_hdronly.h"


namespace vtool {

namespace pfft = pocketfft;

namespace fft_c {

    static const std::size_t
    nThread
#ifdef USE_DEFAULT_MULTITHREADING
    = 0;
#else
    = 1;
#endif
    
    static const
    pfft::shape_t AXIS{ 0 };
    
#ifdef _CXX14_FLAG
    template <typename T>
    static const
    pfft::stride_t _real_stride{sizeof(T)};
    
    template <typename T>
    static const
    pfft::stride_t _cmplx_stride{sizeof(std::complex<T>)};
    
#   define _REAL_STRIDE(T)  fft_c::_real_stride<T>
#   define _CMPLX_STRIDE(T) fft_c::_cmplx_stride<T>
#else
#   define _REAL_STRIDE(T)  pfft::stride_t{sizeof(T)}
#   define _CMPLX_STRIDE(T) pfft::stride_t{sizeof(std::complex<T>)}
#endif
}   // namespace fft_c

#define _SHAPE(N) pfft::shape_t{ N }
#define _AXIS     fft_c::AXIS

//////////////////////////////////////////////////////////////////////////////
// ----------------------------- forward fft ------------------------------ //
// complex to complex
template <typename T, typename Alloc>
std::vector<std::complex<T>, Alloc>
fft(const std::vector<std::complex<T>, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<std::complex<T>, Alloc> fft_vec(N, 0);
    
    pfft::c2c(_SHAPE(N), _CMPLX_STRIDE(T), _CMPLX_STRIDE(T), _AXIS, pfft::FORWARD,
              vec.data(), fft_vec.data(), static_cast<T>(1.0), fft_c::nThread);
    return fft_vec;
}

template <typename T, typename Alloc>
std::vector<std::complex<T>, vtool::rebinded_alloc<Alloc, std::complex<T>>>
fft(const std::vector<T, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<std::complex<T>,
                vtool::rebinded_alloc<Alloc, std::complex<T>>>
    fft_vec = vtool::vector_cast<std::complex<T>>(vec);

    pfft::c2c(_SHAPE(N), _CMPLX_STRIDE(T), _CMPLX_STRIDE(T), _AXIS, pfft::FORWARD,
              fft_vec.data(), fft_vec.data(), static_cast<T>(1.0), fft_c::nThread);
    return fft_vec;
}
    
template <typename T, typename Alloc>
_CXX20_CONSTEXPR
std::vector<std::complex<T>, Alloc>
conjugate_rfft_result(const std::vector<std::complex<T>, Alloc>& vec)
{
    const std::size_t N = (vec.size()-1) * 2;
    std::vector<std::complex<T>, Alloc> conj_vec(vec);
    conj_vec.resize(N, std::complex<T>(0, 0));
    
    for (std::size_t i = N/2+1; i < N; ++i)
        conj_vec[i] = std::conj(vec[N-i]);
    
    return conj_vec;
}

template <typename T, typename Alloc,
          typename vtool::is_arithmetic<T>::type = true>
_CXX20_CONSTEXPR
std::vector<T, Alloc>
conjugate_rfft_result(const std::vector<T, Alloc>& vec)
{
    const std::size_t N = (vec.size()-1) * 2;
    std::vector<T, Alloc> conj_vec(vec);
    conj_vec.resize(N, 0);
    
    for (std::size_t i = N/2+1; i < N; ++i)
        conj_vec[i] = vec[N-i];
    
    return conj_vec;
}

// real to complex
template <typename T, typename Alloc>
std::vector<std::complex<T>, Alloc>
rfft(const std::vector<std::complex<T>, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<std::complex<T>, Alloc> fft_vec(N/2+1, 0);
    std::vector<T, vtool::rebinded_alloc<Alloc, T>> real_vec(N, 0);
    
    for (std::size_t i = 0; i < N; ++i)
        real_vec[i] = vec[i].real();
    
    pfft::r2c(_SHAPE(N), _REAL_STRIDE(T), _CMPLX_STRIDE(T), 0, pfft::FORWARD,
              real_vec.data(), fft_vec.data(), static_cast<T>(1.0), fft_c::nThread);
    return fft_vec;
}

template <typename T, typename Alloc>
std::vector<std::complex<T>, vtool::rebinded_alloc<Alloc, std::complex<T>>>
rfft(const std::vector<T, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<std::complex<T>,
                vtool::rebinded_alloc<Alloc, std::complex<T>>>
    fft_vec(N/2+1, 0);

    pfft::r2c(_SHAPE(N), _REAL_STRIDE(T), _CMPLX_STRIDE(T), 0, pfft::FORWARD,
              vec.data(), fft_vec.data(), static_cast<T>(1.0), fft_c::nThread);
    return fft_vec;
}

// ----------------------------- inverse fft ------------------------------ //
// complex to complex
template <typename T, typename Alloc>
std::vector<std::complex<T>, Alloc>
ifft(const std::vector<std::complex<T>, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<std::complex<T>, Alloc> ifft_vec(N, 0);
    
    pfft::c2c(_SHAPE(N), _CMPLX_STRIDE(T), _CMPLX_STRIDE(T), _AXIS, pfft::BACKWARD,
              vec.data(), ifft_vec.data(), static_cast<T>(1.0)/N, fft_c::nThread);
    return ifft_vec;
}

template <typename T, typename Alloc>
std::vector<std::complex<T>, vtool::rebinded_alloc<Alloc, std::complex<T>>>
ifft(const std::vector<T, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<std::complex<T>,
                vtool::rebinded_alloc<Alloc, std::complex<T>>>
    ifft_vec = vtool::vector_cast<std::complex<T>>(vec);
    
    pfft::c2c(_SHAPE(N), _CMPLX_STRIDE(T), _CMPLX_STRIDE(T), _AXIS, pfft::BACKWARD,
              ifft_vec.data(), ifft_vec.data(), static_cast<T>(1.0)/N, fft_c::nThread);
    return ifft_vec;
}

// complex to real
template <typename T, typename Alloc>
std::vector<T, vtool::rebinded_alloc<Alloc, T>>
irfft(const std::vector<std::complex<T>, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<T, vtool::rebinded_alloc<Alloc, T>> ifft_vec(2*(N-1), 0);
    
    pfft::c2r(_SHAPE(N), _CMPLX_STRIDE(T), _REAL_STRIDE(T), 0, pfft::BACKWARD,
              vec.data(), ifft_vec.data(), static_cast<T>(1.0)/N, fft_c::nThread);
    return ifft_vec;
}

template <typename T, typename Alloc>
std::vector<T, Alloc>
irfft(const std::vector<T, Alloc>& vec)
{
    const std::size_t N = vec.size();
    std::vector<T, Alloc> ifft_vec(N, 0);
    
    pfft::r2r_fftpack(_SHAPE(N), _REAL_STRIDE(T), _REAL_STRIDE(T), _AXIS, true, pfft::BACKWARD,
                      vec.data(), ifft_vec.data(), static_cast<T>(1.0)/N, fft_c::nThread);
    return ifft_vec;
}

}   // namespace vtool

#undef _SHAPE
#undef _AXIS
#undef _REAL_STRIDE
#undef _CMPLX_STRIDE

#endif  // __VTOOL_FFT_H__