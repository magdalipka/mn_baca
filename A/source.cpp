// Magdalena Lipka

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

bool areOppositeSigns(float a, float b) {
  return (a < 0 && b > 0) || (a > 0 && b < 0);
}

float findZero(float (*function)(float, float, float), float leftArgument, float rightArgument, int functionCallsLimit, float epsilon, float delta, float area, float perimeter) {
  float functionValueAtLeft = function(leftArgument, area, perimeter);
  float functionValueAtRight = function(rightArgument, area, perimeter);
  float numberOfUsedFunctionCalls = 2;
  float gapBetweenArguments = rightArgument - leftArgument;

  float spacing = 0.3;

  float middleArgument = functionValueAtLeft == 0 ? leftArgument : rightArgument;
  float functionValueAtMiddle;
  while (numberOfUsedFunctionCalls < functionCallsLimit) {
    if (areOppositeSigns(functionValueAtLeft, functionValueAtRight) && gapBetweenArguments > spacing) {
      // bisection
      if (functionValueAtLeft == 0) return leftArgument;
      if (functionValueAtRight == 0) return rightArgument;

      gapBetweenArguments = (rightArgument - leftArgument);
      middleArgument = leftArgument + (gapBetweenArguments / 2);
      functionValueAtMiddle = function(middleArgument, area, perimeter);
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
      float intersectionArgument = (rightArgument - leftArgument) / (functionValueAtRight - functionValueAtLeft);

      rightArgument = leftArgument;
      functionValueAtRight = functionValueAtLeft;

      leftArgument = leftArgument - (functionValueAtLeft * intersectionArgument);
      functionValueAtLeft = function(leftArgument, area, perimeter);
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

float quadraticEquation(float x, float area, float perimeter) {
  // return 2 * (x * x) - (perimeter * x) + 2 * area;
  return (x * x) - ((perimeter * x) / 2) + area;
}

float delta(float area, float perimeter) {
  return ((perimeter / 2) * (perimeter / 2)) - (4 * area);
}

int main() {
  int rectangesCount;
  std::cin >> rectangesCount;

  float normSum = 0.0;

  for (int i = 0; i < rectangesCount; i++) {
    float rectangleArea, rectanglePerimeter;
    std::cin >> rectangleArea;
    std::cin >> rectanglePerimeter;

    float a, b;
    if (rectanglePerimeter <= 0 || rectangleArea <= 0 || delta(rectangleArea, rectanglePerimeter) < 0) {
      a = 0.0;
      b = 0.0;
    } else {
      float left = 0.0;
      float right = rectanglePerimeter / 4;
      float leftValue = quadraticEquation(left, rectangleArea, rectanglePerimeter);
      float rightValue = quadraticEquation(right, rectangleArea, rectanglePerimeter);

      bool found = false;

      if (!areOppositeSigns(a, b)) {
        a = 0.0;
        b = 0.0;
        found = true;
      }

      bool diff = true;

      float zeroArgument = findZero(quadraticEquation, left, right, 50, 10.0e-26, 10.0e-26, rectangleArea, rectanglePerimeter);
      a = zeroArgument;
      b = rectangleArea / a;

      // while (right - left > 10.0e-26 && !found && diff) {
      //   // std::cout << "-----------------------------------------" << std::endl;
      //   // std::cout << "left: " << left << " value: " << leftValue << std::endl;
      //   // std::cout << "right: " << right << " value: " << rightValue << std::endl;

      //   float middle = (left + right) / 2;
      //   float middleValue = quadraticEquation(middle, rectangleArea, rectanglePerimeter);

      //   // std::cout << "middle: " << middle << " value: " << middleValue << std::endl;

      //   if (middleValue == 0) {
      //     // std::cout << "found" << std::endl;
      //     a = middle;
      //     b = rectangleArea / a;
      //     found = true;
      //   } else if (!areOppositeSigns(middleValue, leftValue)) {
      //     if (left == middle) {
      //       diff = false;
      //     }
      //     left = middle;
      //     leftValue = middleValue;
      //   } else if (!areOppositeSigns(middleValue, rightValue)) {
      //     if (right == middle) {
      //       diff = false;
      //     }
      //     right = middle;
      //     rightValue = middleValue;
      //   }
      // };
      // if (!found) {
      //   // std::cout << "not found" << std::endl;
      //   // std::cout << "left: " << left << " right: " << right << std::endl;
      //   a = (right - left) / 2;
      //   b = rectangleArea / a;
      // }
    }
    normSum += a * a + b * b;
    // std::cout << "a: " << a << " b: " << b << std::endl;
    if (a > b) {
      std::cout << std::scientific << std::setprecision(10) << a << " " << b << std::endl;
    } else {
      std::cout << std::scientific << std::setprecision(10) << b << " " << a << std::endl;
    }
  }
  std::cout << std::scientific << std::setprecision(10) << sqrt(normSum) << std::endl;
}