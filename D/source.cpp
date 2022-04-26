// Magdalena Lipka

#include <cmath>
#include <iomanip>
#include <iostream>

#include "funkcja.h"

// template <typename T>
// T funkcja(const T& x) {
//   T y = sin(x * x - 2 * (x + 1)) / exp(-x + cos(x * x));
//   return y;
// }

// template <typename T>
// T funkcja2(const T& x) {
//   T y = x * x;
//   return y;
// }

// template <typename T>
// T funkcja3(const T& x) {
//   T y = 2 * (x + 1);
//   return y;
// }

// template <typename T>
// T funkcja4(const T& x) {
//   T y = funkcja2(x) - funkcja3(x);
//   return y;
// }

// template <typename T>
// T funkcja5(const T& x) {
//   T y = cos(x * x);
//   return y;
// }

// template <typename T>
// T funkcja6(const T& x) {
//   T y = exp(-x + funkcja5(x));
//   return y;
// }

// template <typename T>
// T funkcja7(const T& x) {
//   T y = sin(funkcja4(x));
//   return y;
// }

// template <typename T>
// T funkcja8(const T& x) {
//   T y = funkcja7(x) / funkcja6(x);
//   return y;
// }

// template <typename T>
// T funkcja(const T& x) {
//   T y1 = sin(x * x - 2 * (x + 1));
//   std::cout << y1 << std::endl;
//   T y2 = exp(-x + cos(x * x));
//   std::cout << y2 << std::endl;
//   T y3 = y1 / y2;
//   return y3;
// };

// template <typename T>
// T funkcja(const T& x) {
//   auto x1 = x * x;
//   std::cout << "1: \t" << x1 << std::endl;
//   auto x2 = x + 1;
//   std::cout << "2: \t" << x2 << std::endl;
//   auto x3 = 2 * (x2);
//   std::cout << "3: \t" << x3 << std::endl;
//   auto x3_5 = x1 - x3;
//   std::cout << "4: \t" << x3_5 << std::endl;
//   auto x4 = sin(x3_5);
//   std::cout << "5: \t" << x4 << std::endl;
//   auto x5 = -x;
//   std::cout << "6: \t" << x5 << std::endl;
//   auto x6 = x * x;
//   std::cout << "7: \t" << x6 << std::endl;
//   auto x6_5 = cos(x6);
//   std::cout << "8: \t" << x6_5 << std::endl;
//   auto x7 = x5 + x6_5;
//   std::cout << "9: \t" << x7 << std::endl;
//   auto x8 = exp(x7);
//   std::cout << "10: \t" << x8 << std::endl;
//   T y = x4 / x8;
//   std::cout << "11: \t" << y << std::endl;

//   return x4;
// }

class Jet {
 public:
  int order;
  long double* jets;

  Jet() {
    order = 1;
    jets = new long double[order];
  }

  Jet(int order) {
    this->order = order;
    jets = new long double[order];
  }

  Jet(int order, long double value) {
    this->order = order;
    this->jets = new long double[order];
    this->jets[0] = value;
  }

  Jet(const Jet& jet) {
    order = jet.order;
    jets = new long double[order];
    for (int i = 0; i < order; i++) {
      jets[i] = jet.jets[i];
    }
  }

  friend std::ostream& operator<<(std::ostream& output, const Jet& jet) {
    long int orderFactorial = 1;

    for (int i = 0; i < jet.order; i++) {
      output << jet.jets[i] * orderFactorial;
      orderFactorial *= (i + 1);
      if (i != jet.order - 1) {
        output << " ";
      }
    }
    return output;
  }

  void operator=(const Jet& jet) {
    this->order = jet.order;
    for (int i = 0; i < jet.order; i++) {
      this->jets[i] = jet.jets[i];
    }
  }

  friend Jet operator-(const Jet& jet) {
    Jet result(jet.order);
    for (int i = 0; i < jet.order; i++) {
      result.jets[i] = jet.jets[i] ? -jet.jets[i] : 0;
    }
    return result;
  }

  friend Jet operator+(const Jet& f, long double c) {
    Jet result(f.order, f.jets[0] + c);
    for (int i = 1; i < f.order; i++) {
      result.jets[i] = f.jets[i];
    }
    return result;
  }

  friend Jet operator+(long double c, const Jet& f) {
    return f + c;
  }

  friend Jet operator-(const Jet& f, long double c) {
    Jet result(f.order, f.jets[0] - c);
    for (int i = 1; i < f.order; i++) {
      result.jets[i] = f.jets[i];
    }
    return result;
  }

  friend Jet operator-(long double c, const Jet& f) {
    return -f + c;
  }

  friend Jet operator*(const Jet& f, long double c) {
    Jet result(f.order);
    for (int i = 0; i < f.order; i++) {
      result.jets[i] = f.jets[i] * c;
    }
    return result;
  }

  friend Jet operator*(long double c, const Jet& f) {
    return f * c;
  }

  friend Jet operator/(const Jet& f, long double c) {
    return f * (1 / c);
  }

  friend Jet operator/(long double c, const Jet& f) {
    Jet constantJet(f.order, c);
    for (int i = 1; i < f.order; i++) {
      constantJet.jets[i] = 0;
    }
    return constantJet / f;
  }

  friend Jet operator+(const Jet& f, const Jet& g) {
    Jet result(f.order);
    for (int i = 0; i < f.order; i++) {
      result.jets[i] = f.jets[i] + g.jets[i];
    }
    return result;
  };

  friend Jet operator-(const Jet& f, const Jet& g) {
    Jet result(f.order);
    for (int i = 0; i < f.order; i++) {
      result.jets[i] = f.jets[i] - g.jets[i];
    }
    return result;
  };

  friend Jet operator*(const Jet& f, const Jet& g) {
    // std::cout << "f: " << f.order << std::endl;
    // std::cout << "f: " << f << std::endl;
    // std::cout << "g: " << g.order << std::endl;
    // std::cout << "g: " << g << std::endl;
    Jet result(f.order);
    result.jets[0] = f.jets[0] * g.jets[0];
    for (int i = 1; i < result.order; i++) {
      // std::cout << "i: " << i << std::endl;
      result.jets[i] = 0;
      for (int j = 0; j <= i; j++) {
        // std::cout << " j: " << j << std::endl;
        result.jets[i] += f.jets[j] * g.jets[i - j];
        // std::cout << " result: " << result.jets[i] << std::endl;
      }
    }
    return result;
  };

  friend Jet operator/(const Jet& f, const Jet& g) {
    Jet result(f.order);
    result.jets[0] = f.jets[0] / g.jets[0];
    for (int i = 1; i < result.order; i++) {
      result.jets[i] = 0;
      long double acc = 0;
      for (int j = 0; j <= i - 1; j++) {
        acc += g.jets[i - j] * result.jets[j];
      }
      result.jets[i] = (f.jets[i] - acc) / g.jets[0];
      result.jets[i] = result.jets[i] ? result.jets[i] : 0;
    }
    return result;
  }

  friend long double calculateNthCos(const Jet& f, const Jet& sinJet, int k) {
    long double result = 0;

    for (int i = 1; i <= k; i++) {
      result += i * f.jets[i] * sinJet.jets[k - i];
    }

    return -result / k;
  }

  friend long double calculateNthSin(const Jet& f, const Jet& cosJet, int k) {
    long double result = 0;

    for (int i = 1; i <= k; i++) {
      result += i * f.jets[i] * cosJet.jets[k - i];
    }

    return result / k;
  }

  friend Jet cos(const Jet& f) {
    // std::cout << "trying to get cos: " << f << std::endl;

    if (f.order <= 1) {
      // std::cout << "cos1" << Jet(f.order, std::cos(f.jets[0])) << std::endl;
      return Jet(f.order, std::cos(f.jets[0]));
    }

    if (f.order == 2) {
      Jet result(f.order);
      result.jets[0] = std::cos(f.jets[0]);
      result.jets[1] = -f.jets[1] * std::sin(f.jets[0]);

      // std::cout << "cos2" << result << std::endl;

      return result;
    }

    Jet cosPairResult(2);
    Jet sinPairResult(2);

    for (int i = 0; i < 2; i++) {
      cosPairResult.jets[i] = f.jets[i];
      sinPairResult.jets[i] = f.jets[i];
    }

    cosPairResult = cos(cosPairResult);
    sinPairResult = sin(sinPairResult);

    Jet cosResult(f.order);
    Jet sinResult(f.order);

    for (int i = 0; i < 2; i++) {
      cosResult.jets[i] = cosPairResult.jets[i];
      sinResult.jets[i] = sinPairResult.jets[i];
    }

    for (int i = 2; i < f.order; i++) {
      cosResult.jets[i] = 0;
      sinResult.jets[i] = 0;
    }

    // std::cout << "got sin and cos for pairs:" << std::endl;
    // std::cout << "cos: " << cosResult << std::endl;
    // std::cout << "sin: " << sinResult << std::endl;

    for (int i = 2; i < f.order; i++) {
      // std::cout << "calculating cos: " << i << std::endl;
      cosResult.jets[i] = calculateNthCos(f, sinResult, i);
      sinResult.jets[i] = calculateNthSin(f, cosResult, i);
      // std::cout << "sinRestult: " << sinResult << std::endl;
      // std::cout << "cosRestult: " << cosResult << std::endl;
    }

    // std::cout << "got cos: " << cosResult << std::endl;

    return cosResult;
  }

  friend Jet sin(const Jet& f) {
    // std::cout << "trying to get sin: " << f << std::endl;

    if (f.order <= 1) {
      // std::cout << "sin1" << Jet(f.order, std::sin(f.jets[0])) << std::endl;

      return Jet(f.order, std::sin(f.jets[0]));
    }

    if (f.order == 2) {
      Jet result(f.order);
      result.jets[0] = std::sin(f.jets[0]);
      result.jets[1] = f.jets[1] * std::cos(f.jets[0]);

      // std::cout << "sin2" << result << std::endl;

      return result;
    }

    Jet sinPairResult(2);
    Jet cosPairResult(2);

    for (int i = 0; i < 2; i++) {
      sinPairResult.jets[i] = f.jets[i];
      cosPairResult.jets[i] = f.jets[i];
    }

    sinPairResult = sin(sinPairResult);
    cosPairResult = cos(cosPairResult);

    Jet sinResult(f.order);
    Jet cosResult(f.order);

    for (int i = 0; i < 2; i++) {
      sinResult.jets[i] = sinPairResult.jets[i];
      cosResult.jets[i] = cosPairResult.jets[i];
    }

    for (int i = 2; i < f.order; i++) {
      sinResult.jets[i] = 0;
      cosResult.jets[i] = 0;
    }

    // std::cout << "got sin and cos for pairs:" << std::endl;
    // std::cout << "cos: " << cosResult << std::endl;
    // std::cout << "sin: " << sinResult << std::endl;

    for (int i = 2; i < f.order; i++) {
      // std::cout << "calculating sin: " << i << std::endl;
      sinResult.jets[i] = calculateNthSin(f, cosResult, i);
      cosResult.jets[i] = calculateNthCos(f, sinResult, i);
      // std::cout << "sinRestult: " << sinResult << std::endl;
      // std::cout << "cosRestult: " << cosResult << std::endl;
    }

    // std::cout << "got sin: " << sinResult << std::endl;

    return sinResult;
  }

  friend Jet exp(const Jet& f) {
    Jet result(f.order);
    result.jets[0] = std::exp(f.jets[0]);
    for (int i = 1; i < f.order; i++) {
      result.jets[i] = 0;
      for (int j = 0; j < i; j++) {
        result.jets[i] += (i - j) * (result.jets[j] * f.jets[i - j]);
      }
      result.jets[i] /= i;
    }
    return result;
  }
};

int main() {
  std::cout << std::setprecision(16) << std::fixed;

  int derivativeOrder;
  int numberOfPoints;

  std::cin >> derivativeOrder >> numberOfPoints;

  for (int i = 0; i < numberOfPoints; i++) {
    long double argument;
    std::cin >> argument;

    Jet* argumentJet = new Jet(derivativeOrder + 1, argument);
    argumentJet->jets[1] = 1;
    for (int j = 2; j < derivativeOrder + 1; j++) {
      argumentJet->jets[j] = 0;
    }

    Jet x = funkcja(*argumentJet);

    // std::cout << "f2(" << *argumentJet << ") = " << funkcja2(*argumentJet) << std::endl;
    // std::cout << "f3(" << *argumentJet << ") = " << funkcja3(*argumentJet) << std::endl;
    // std::cout << "f4(" << *argumentJet << ") = " << funkcja4(*argumentJet) << std::endl;
    // std::cout << "f5(" << *argumentJet << ") = " << funkcja5(*argumentJet) << std::endl;
    // std::cout << "f6(" << *argumentJet << ") = " << funkcja6(*argumentJet) << std::endl;
    // std::cout << "f7(" << *argumentJet << ") = " << funkcja7(*argumentJet) << std::endl;
    // std::cout << "f8(" << *argumentJet << ") = " << funkcja8(*argumentJet) << std::endl;

    std::cout << x << std::endl;
  }

  return 0;
}
