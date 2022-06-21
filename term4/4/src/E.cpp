#include <bit>
#include <complex>
#include <iostream>
#include <numbers>
#include <vector>

using complex = std::complex<double>;
using polynomial = std::vector<complex>;

template <bool Inverse = false>
void fft(polynomial & p)
{
    std::size_t n = p.size() / 2;
    if (n == 0) {
        return;
    }

    polynomial p0(n), p1(n);

    for (std::size_t i = 0; i < n; ++i) {
        p0[i] = p[i * 2];
        p1[i] = p[i * 2 + 1];
    }

    fft<Inverse>(p0);
    fft<Inverse>(p1);

    double angle = std::numbers::pi / static_cast<double>(n);
    if constexpr (Inverse) {
        angle *= -1;
    }

    complex w = 1, wn(std::cos(angle), std::sin(angle));

    for (std::size_t i = 0; i < n; ++i) {
        p[i] = p0[i] + w * p1[i];
        p[i + n] = p0[i] - w * p1[i];
        if constexpr (Inverse) {
            p[i] /= 2;
            p[i + n] /= 2;
        }
        w *= wn;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::cin >> n;

    std::size_t n2 = std::bit_ceil(++n) * 2;

    polynomial a(n2), b(n2);

    for (std::size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;
        a[i] = x;
    }

    for (std::size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;
        b[i] = x;
    }

    fft(a);
    fft(b);
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] *= b[i];
    }
    fft<true>(a);

    for (std::size_t i = 0; i < 2 * n - 1; ++i) {
        std::cout << static_cast<int>(std::round(std::abs(a[i]))) << ' ';
    }

    return 0;
}
