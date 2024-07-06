#include <cmath>
#include <vector>
#include <complex>
#include <iomanip>
#include <iostream>

#include "vectortools.h"

namespace vtool {

using ::operator<<;

namespace test {

static constexpr
std::complex<long double>
operator""_j(const long double arg)
{ return std::complex<long double>{0.0, static_cast<long double>(arg)}; }

static const
std::vector<double>
test_dbl{
    1.1, 2.2, 3.3, 4.4, 5.5, 6.6
};

static const
std::vector<std::complex<long double>>
test_cmplx{
    1.0l+2.0_j, 3.0l+4.0_j, 5.0l+6.0_j, 7.0l+8.0_j, 9.0l+10.0_j
};

static const
std::vector<int>
test_int{
    1, 2, 3, 4, 5, 6
};

static const
std::size_t win_width = 5;

void
vectortools_test_plan()
{
    const auto forward_c2c_dbl   = vtool::fft(test_dbl);
    const auto forward_c2c_cmplx = vtool::fft(test_cmplx);
    const auto forward_r2c_dbl   = vtool::rfft(test_dbl);
    const auto forward_r2c_cmplx = vtool::rfft(test_cmplx);

    std::cout
        << std::fixed << std::setprecision(3)
        << "[ FFT TEST VECTOR ]\n"
        << "  vector<double>:          " << test_dbl << "\n"
        << "  vector<complex<double>>: " << test_cmplx << "\n\n";
    
    std::cout
        << "| Forward FFT |\n"
        << "  < c2c >\n"
        << "  " << forward_c2c_dbl   << "\n"
        << "  " << forward_c2c_cmplx << "\n\n"
        << "  < r2c >\n"
        << "  " << forward_r2c_dbl   << "\n"
        << "  " << forward_r2c_cmplx << "\n\n";
    
    std::cout
        << "| Inverse FFT |\n"
        << "  < c2c >\n"
        << "  " << vtool::ifft(forward_c2c_dbl)    << "\n"
        << "  " << vtool::ifft(forward_c2c_cmplx)  << "\n\n"
        << "  < r2c >\n"
        << "  " << vtool::irfft(forward_r2c_dbl)   << "\n"
        << "  " << vtool::irfft(forward_r2c_cmplx) << "\n\n";

    std::cout
        << "──────────────────────────────────────────────────"
        << "──────────────────────────────────────────────────" << "\n\n";

    std::cout
        << "[ OPERATOR OVERLOAD TEST VECTOR ]\n"
        << "  vector<int>:    " << test_int << "\n"
        << "  vector<double>: " << test_dbl << "\n\n";

    std::cout
        << "| operator+ |\n"
        << "  (double)3.3 + vector<int>:    " << 3.3 + test_int      << "\n"
        << "  (int)3 + vector<double>:      " << 3 + test_dbl        << "\n"
        << "  vector<double> + vector<int>: " << test_dbl + test_int << "\n\n";

    std::cout
        << "| operator- |\n"
        << "  (double)3.3 - vector<int>:    " << 3.3 - test_int      << "\n"
        << "  (int)3 - vector<double>:      " << 3 - test_dbl        << "\n"
        << "  vector<double> - vector<int>: " << test_dbl - test_int << "\n\n";

    std::cout
        << "| operator* |\n"
        << "  (double)3.3 * vector<int>:    " << 3.3 * test_int      << "\n"
        << "  (int)3 - vector<double>:      " << 3 * test_dbl        << "\n"
        << "  vector<double> * vector<int>: " << test_dbl * test_int << "\n\n";

    std::cout
        << "| operator/ |\n"
        << "  (double)3.3 / vector<int>:    " << 3.3 / test_int      << "\n"
        << "  (int)3 / vector<double>:      " << 3 / test_dbl        << "\n"
        << "  vector<double> / vector<int>: " << test_dbl / test_int << "\n\n";

    std::cout
        << "──────────────────────────────────────────────────"
        << "──────────────────────────────────────────────────" << "\n\n";

    std::cout
        << "[ VECTORTOOLS UTILS TEST ]\n";

    std::cout
        << "| isSameSize(std::vector<int>, std::vector<double>) |\n"
        << "  size 2 vs size 3: " << vtool::isSameSize(std::vector<int>{1, 2}, std::vector<double>{1, 2, 3}) << "\n"
        << "  size 2 vs size 2: " << vtool::isSameSize(std::vector<int>{1, 2}, std::vector<double>{1, 2})    << "\n\n";

    std::cout
        << "| linspace(0, 14, 7) |\n"
        << "  endpoint = true:  " << vtool::linspace(0, 14, 7, true)  << "\n"
        << "  endpoint = false: " << vtool::linspace(0, 14, 7, false) << "\n\n";

    std::cout
        << "| mean() |\n"
        << "  {-1, 0, 1}: " << vtool::mean(std::vector<int>{-1, 0, 1})    << "\n"
        << "  {0.2, 0.2}: " << vtool::mean(std::vector<double>{0.2, 0.2}) << "\n\n";
        
    std::cout
        << "| norm() |\n"
        << " {-3, 5}:       " << vtool::norm(std::vector<int>{-3, 5})        << "\n"
        << " {2, 2, -2, -2}:" << vtool::norm(std::vector<int>{2, 2, -2, -2}) << "\n\n";

    std::cout
        << "| rms() |\n"
        << "  {1, 2, 3}:        " << vtool::rms(std::vector<int>{1, 2, 3})           << "\n"
        << "  {1, -2, 3}:       " << vtool::rms(std::vector<int>{1, -2, 3})          << "\n"
        << "  {1.0, -2.0, 3.0}: " << vtool::rms(std::vector<double>{1.0, -2.0, 3.0}) << "\n\n";

    const std::vector<int> intvec{1, 10, 100};
    const std::vector<double> dblvec{-10.0, -5.0, -3.0, 0.0};

    std::cout
        << "| max, min, median |\n"
        << "  {1, 10, 100}"                      << "\t\t" << "{-10.0, -5.0, -3.0, 0.0}" << "\n"
        << "  max:    " << vtool::max(intvec)    << "\t\t" << vtool::max(dblvec)         << "\n"
        << "  min:    " << vtool::min(intvec)    << "\t\t" << vtool::min(dblvec)         << "\n"
        << "  median: " << vtool::median(intvec) << "\t\t" << vtool::median(dblvec)      << "\n\n";

    std::cout
        << "| abs() |\n"
        << "  {1, 2, 3}:            " << vtool::abs(std::vector<int>{1, 2, 3})                                                    << "\n"
        << "  {1, -2, 3}:           " << vtool::abs(std::vector<int>{1, -2, 3})                                                   << "\n"
        << "  {1.0, -2.0, 3.0}:     " << vtool::abs(std::vector<double>{1.0, -2.0, 3.0})                                          << "\n"
        << "  {3+4j, 5+12j, 7+24j}: " << vtool::abs(std::vector<std::complex<long double>>{3.0l+4.0_j, 5.0l+12.0_j, 7.0l+24.0_j}) << "\n\n";

    std::cout
        << "| differential() |\n"
        << "  {1, 2, 3}:           " << vtool::differential(std::vector<int>{1, 2, 3})                                                   << "\n"
        << "  {1+1j, 0+1j, -1+0j}: " << vtool::differential(std::vector<std::complex<long double>>{1.0l+1.0_j, 0.0l+0.1_j, -1.0l+0.0_j}) << "\n\n";

    std::cout
        << "| duplicate_append() |\n"
        << "  +3×{1, 2, 3}:        " << vtool::duplicate_append(std::vector<int>{1, 2, 3}, 3)          << "\n"
        << "  +0×{1.0, 2.0, 3.0}:  " << vtool::duplicate_append(std::vector<double>{1.0, 2.0, 3.0}, 0) << "\n\n";

    const auto test_il0 = std::vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3};
    const auto test_il1 = vtool::interleave(test_il0, 3);
    const auto test_il2 = vtool::interleave(test_il1, 3);

    std::cout
        << "| interleave() |\n"
        << "  before interleaved:  " << test_il0 << "\n"
        << "  1st interleaving:    " << test_il1 << "\n"
        << "  2nd interleaving:    " << test_il2 << "\n\n";

    const auto test_apply0 = std::vector<double>{0, 1, 2, 3};
    const auto test_apply1 = vtool::apply(test_apply0, (double (*)(double))std::exp);

    std::cout
        << "| apply(exp) |\n"
        << "  before applied: " << test_apply0 << "\n"
        << "  after applied:  " << test_apply1 << "\n\n";

    std::cout
        << "──────────────────────────────────────────────────"
        << "──────────────────────────────────────────────────" << "\n\n";

    std::cout
        << "[ WINDOWS FUNCTION TEST ]\n";

    std::cout
        << "  sine:     " << vtool::windows::sine(win_width)     << "\n"
        << "  hanning:  " << vtool::windows::hanning(win_width)  << "\n"
        << "  hamming:  " << vtool::windows::hamming(win_width)  << "\n"
        << "  bartlett: " << vtool::windows::bartlett(win_width) << "\n"
        << "  barthann: " << vtool::windows::barthann(win_width) << "\n"
        << "  blackman: " << vtool::windows::blackman(win_width) << "\n";
}


}   // namespace test

using test::vectortools_test_plan;
}   // namespace vtool