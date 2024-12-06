#ifndef MY_UTILS_HPP_
#define MY_UTILS_HPP_

#include <chrono>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <vector>

namespace my {

using Factor_List = std::unordered_map<int, int>;

template <typename int_type>
bool constexpr IsPrime(const int_type n) {
  if (n < 2) {
    return false;
  }
  if (n < 4) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }

  for (int_type i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

template <typename int_type>
bool constexpr IsPrimeLessChecks(const int_type n) {
  if ((n % 2 == 0) || (n % 3 == 0)) {
    return false;
  }

  for (int_type i = 5; i * i <= n; i += 6) {
    if ((n % i == 0) || (n % (i + 2) == 0)) {
      return false;
    }
  }
  return true;
}

template <typename int_type>
int_type constexpr DigitSum(int_type n) {
  int_type sum = 0;

  while (n) {
    sum += n % 10;
    n /= 10;
  }

  return sum;
}

template <typename data_type>
data_type constexpr Gcd(data_type a, data_type b) {
  while (b != 0) {
    const data_type t = a % b;
    a = b;
    b = t;
  }
  return a;
}

template <typename int_type>
int_type constexpr Pow(int_type a, int_type b) {
  int_type result = 1;
  while (b != 0) {
    if (b & 1) {
      result *= a;
    }
    a *= a;
    b >>= 1;
  }
  return result;
}

template <typename data_type>
data_type constexpr Pow(data_type a, data_type b, const data_type mod) {
  data_type result = 1;
  while (b != 0) {
    if (b & 1) {
      result = (result * a) % mod;
    }
    a = (a * a) % mod;
    b >>= 1;
  }
  return result;
}

template <typename data_type>
inline constexpr data_type Sqr(const data_type& x) {
  return x * x;
}

template <typename int_type>
bool constexpr IsSquare(const int_type x) {
  const int_type root = std::sqrt(x);

  return root * root == x;
}

template <typename int_type, typename functor = std::function<void(const int_type)>>
void IterateThruDivsFirstHalf(int_type n, const functor& func) {
  for (int_type i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      func(i);
    }
  }
}

template <typename int_type, typename functor = std::function<void(const int_type)>>
void IterateThruDivs(int_type n, const functor& func) {
  for (int_type i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      func(i);

      if (i * i != n) {
        func(n / i);
      }
    }
  }
}

template <typename int_type, typename functor = std::function<void(const int_type)>>
void IterateThruDivsInOrder(const int_type n, const functor& func) {
  std::vector<int_type> divs;
  for (int_type i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      func(i);

      if (i * i != n) {
        divs.push_back(n / i);
      }
    }
  }

  for (int i = divs.size() - 1; i >= 0; i--) {
    func(divs[i]);
  }
}

template <typename int_type>
Factor_List Factorize(int_type n, const int_type pow = 1) {
  Factor_List factors;
  while (n % 2 == 0) {
    ++factors[2];
    n /= 2;
  }
  for (int_type i = 3; i <= n; i += 2) {
    while (n % i == 0) {
      ++factors[i];
      n /= i;
    }
  }

  if (pow != 1) {
    for (auto& p : factors) {
      p.second *= pow;
    }
  }

  return factors;
}

class Timer {
 public:
  Timer() { Reset(); }

  void Reset() { start_ = std::chrono::steady_clock::now(); }

  [[nodiscard]] double ElapsedTime() const {
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    const std::chrono::duration<double> interval = now - start_;
    return interval.count();
  }

 private:
  std::chrono::steady_clock::time_point start_;
};

}  // namespace my

#endif  // MY_UTILS_HPP_
