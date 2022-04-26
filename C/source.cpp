// Magdalena Lipka

#include <cmath>
#include <iomanip>
#include <iostream>

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

double epsilon = 10e-13;
double iterationLimit = 50;

void printVector(const double* x, unsigned int N) {
  std::cout << std::setprecision(17) << std::fixed;
  for (unsigned int i = 0; i < N; ++i) {
    std::cout << x[i] << " ";
  }
  std::cout << "\n";
}

int findCurve(FuncPointer function, double* approximatePoint, unsigned amountOfPointsToFind, double parameterDelta) {
  double pointCopy[3] = {approximatePoint[0], approximatePoint[1], approximatePoint[2]};
  double values[2];
  double derivatives[6];

  for (unsigned int i = 0; i < amountOfPointsToFind; ++i) {
    pointCopy[2] += parameterDelta;

    for (unsigned int j = 0; j < iterationLimit; ++j) {
      function(pointCopy, values, derivatives);

      if (std::max(std::abs(values[0]), std::abs(values[1])) <= epsilon) {
        break;
      }

      double value = derivatives[0] * derivatives[4] - derivatives[1] * derivatives[3];

      if (std::abs(value) < epsilon || j == iterationLimit - 1) {
        return i + 1;
      }

      pointCopy[0] -= (values[0] * derivatives[4] - values[1] * derivatives[1]) / value;
      pointCopy[1] -= (values[1] * derivatives[0] - values[0] * derivatives[3]) / value;
    }

    printVector(pointCopy, 3);
  }
}

int findSurface(FuncPointer function, double* approximatePoint, unsigned amountOfPointsToFind1, unsigned amountOfPointsToFind2, double parameter1Delta, double parameter2Delta) {
  double pointCopy[3] = {approximatePoint[0], approximatePoint[1], approximatePoint[2]};
  double values[2];
  double derivatives[6];

  for (unsigned int i = 0; i < amountOfPointsToFind1; ++i) {
    pointCopy[0] += parameter1Delta;

    for (unsigned int j = 0; j < amountOfPointsToFind2; ++j) {
      pointCopy[1] += parameter2Delta;

      for (unsigned int k = 0; k < iterationLimit; ++k) {
        function(pointCopy, values, derivatives);

        if (std::max(std::abs(values[0]), std::abs(values[1])) <= epsilon) {
          break;
        }

        double value = derivatives[0] * derivatives[4] - derivatives[1] * derivatives[3];

        if (std::abs(value) < epsilon || k == iterationLimit - 1) {
          return i + 1;
        }

        pointCopy[0] -= (values[0] * derivatives[4] - values[1] * derivatives[1]) / value;
        pointCopy[1] -= (values[1] * derivatives[0] - values[0] * derivatives[3]) / value;
      }

      printVector(pointCopy, 3);
    }
  }
}

int findFixedPoints(FuncPointer function, double* approximatePoint, unsigned amountOfPointsToFind1, unsigned amountOfPointsToFind2, double parameter1Delta, double parameter2Delta) {
  double pointCopy[4] = {approximatePoint[0], approximatePoint[1], approximatePoint[2], approximatePoint[3]};
  double values[2];
  double derivatives[8];

  for (unsigned int i = 0; i < amountOfPointsToFind1; ++i) {
    pointCopy[0] += parameter1Delta;

    for (unsigned int j = 0; j < amountOfPointsToFind2; ++j) {
      pointCopy[1] += parameter2Delta;

      for (unsigned int k = 0; k < iterationLimit; ++k) {
        function(pointCopy, values, derivatives);

        if (std::max(std::abs(values[0]), std::abs(values[1])) <= epsilon) {
          break;
        }

        double value = derivatives[0] * derivatives[4] - derivatives[1] * derivatives[3];

        if (std::abs(value) < epsilon || k == iterationLimit - 1) {
          return i + 1;
        }

        pointCopy[0] -= (values[0] * derivatives[4] - values[1] * derivatives[1]) / value;
        pointCopy[1] -= (values[1] * derivatives[0] - values[0] * derivatives[3]) / value;
      }

      printVector(pointCopy, 3);
    }
  }
}