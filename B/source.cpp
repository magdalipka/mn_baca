// Magdalena Lipka
#include <cmath>
#include <iostream>
using namespace std;

bool areOppositeSigns(double a, double b) {
  return (a < 0 && b > 0) || (a > 0 && b < 0);
}

double findZero(double (*function)(double), double leftArgument, double rightArgument, int functionCallsLimit, double epsilon, double delta) {
  double functionValueAtLeft = function(leftArgument);
  double functionValueAtRight = function(rightArgument);
  double numberOfUsedFunctionCalls = 2;
  double gapBetweenArguments = rightArgument - leftArgument;

  double spacing = 0.3;

  double middleArgument = functionValueAtLeft == 0 ? leftArgument : rightArgument;
  double functionValueAtMiddle;
  while (numberOfUsedFunctionCalls < functionCallsLimit) {
    if (areOppositeSigns(functionValueAtLeft, functionValueAtRight) && gapBetweenArguments > spacing) {
      // bisection
      if (functionValueAtLeft == 0) return leftArgument;
      if (functionValueAtRight == 0) return rightArgument;

      gapBetweenArguments = (rightArgument - leftArgument);
      middleArgument = leftArgument + (gapBetweenArguments / 2);
      functionValueAtMiddle = function(middleArgument);
      numberOfUsedFunctionCalls++;

      if (abs(gapBetweenArguments / 2) < delta || abs(functionValueAtMiddle) < epsilon) {
        break;
      }

      if (areOppositeSigns(functionValueAtLeft, functionValueAtMiddle)) {
        rightArgument = middleArgument;
        functionValueAtRight = functionValueAtMiddle;
      } else {
        leftArgument = middleArgument;
        functionValueAtLeft = functionValueAtMiddle;
      }

    } else {
      // secant
      double intersectionArgument = (rightArgument - leftArgument) / (functionValueAtRight - functionValueAtLeft);

      rightArgument = leftArgument;
      functionValueAtRight = functionValueAtLeft;

      leftArgument = leftArgument - (functionValueAtLeft * intersectionArgument);
      functionValueAtLeft = function(leftArgument);
      numberOfUsedFunctionCalls++;

      middleArgument = leftArgument;
      functionValueAtMiddle = functionValueAtLeft;

      if (abs(functionValueAtLeft) < epsilon || abs(rightArgument - leftArgument) < delta) {
        break;
      }
    }
  }
  return middleArgument;
}

// double wielomian(double x) { return (((x - 6) * x + 11) * x) - 6; }
// double wielomianSinExp(double x) { return ((((x - 6) * x + 11) * x) - 4 + sin(15 * x)) * exp(-x * x); }
// double kwadrat(double x) { return (x * x - 2); }
// double kwadrat100(double x) { return 1e100 * (x * x - 2); }
// double kwadrat_10(double x) { return 1e-10 * (x * x - 2); }

// int main() {
//   cout.precision(17);
//   cout << "----------------wynik: " << endl;  // Spodziewany wynik
//   cout << "1, 2, 3" << endl;
//   cout << findZero(wielomian, 0, 4, 20, 1e-15, 1e-14) << endl;  // 1 lub 2 lub 3
//   cout << "----------------wynik: " << endl;                    // Spodziewany wynik
//   cout << "1, 2, 3" << endl;
//   cout << findZero(wielomian, 0, 40, 20, 1e-15, 1e-14) << endl;  // 1 lub 2 lub 3
//   cout << "----------------wynik: " << endl;                     // Spodziewany wynik
//   cout << "1, 2" << endl;
//   cout << findZero(wielomian, 1, 2, 2, 1e-15, 1e-14) << endl;  // 1 lub 2
//   cout << "----------------wynik: " << endl;                   // Spodziewany wynik
//   cout << "1" << endl;
//   cout << findZero(wielomian, -150, 1.9, 20, 1e-15, 1e-14) << endl;  // 1
//   cout << "----------------wynik: " << endl;                         // Spodziewany wynik
//   cout << "2" << endl;
//   cout << findZero(wielomian, 1.5, 2.99, 20, 1e-15, 1e-14) << endl;  // 2
//   cout << "----------------wynik: " << endl;                         // Spodziewany wynik
//   cout << "3" << endl;
//   cout << findZero(wielomian, 2.01, 40, 20, 1e-15, 1e-14) << endl;  // 3
//   cout << "----------------wynik: " << endl;                        // Spodziewany wynik
//   cout << "1, 2, 3" << endl;
//   cout << findZero(wielomian, 1.5, 6, 20, 1e-15, 1e-14) << endl;  // 1 lub 2 lub 3

//   cout << "----------------wynik: " << endl;  // Spodziewany wynik
//   cout << "0.43636925909804245" << endl;
//   cout << findZero(wielomianSinExp, -1, 3, 60, 1e-60, 1e-14) << endl;  // 0.43636925909804245
//   cout << "----------------wynik: " << endl;                           // Spodziewany wynik
//   cout << "0.43636925909804245" << endl;
//   cout << findZero(wielomianSinExp, -3, 3, 60, 1e-160, 1e-14) << endl;  // 0.43636925909804245

//   cout << "----------------wynik: " << endl;  // Spodziewany wynik
//   cout << "1.414213562373095" << endl;
//   cout << findZero(kwadrat, 0, 4, 15, 1e-11, 1e-14) << endl;  // 1.414213562373095
//   cout << "----------------wynik: " << endl;                  // Spodziewany wynik
//   cout << "1.414213562373095" << endl;
//   cout << findZero(kwadrat100, 0, 4, 15, 1e-11, 1e-14) << endl;  // 1.414213562373095
//   cout << "----------------wynik: " << endl;                     // Spodziewany wynik
//   cout << "każdy punkt z przedziału [1, 1.73205]" << endl;
//   cout << findZero(kwadrat_10, 0, 4, 10, 1e-10, 1e-14) << endl;  // każdy punkt z przedziału [1, 1.73205]
//   cout << "----------------wynik: " << endl;                     // Spodziewany wynik
//   cout << "1.414213562373095" << endl;
//   cout << findZero(kwadrat_10, 0, 4, 15, 1e-160, 1e-14) << endl;  // 1.414213562373095
//   return 0;
// }