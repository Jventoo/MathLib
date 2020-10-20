#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define EPSILON 0.000000001
#define PI 3.14159265358979323846
#define OPTIONS "sctea" // All command line input options

enum options { SIN, COS, TAN, EXP, ALL };

double Sin(double x);
double Cos(double x);
double Tan(double x);
double Exp(double x);

void sin_tests(void);
void cos_tests(void);
void tan_tests(void);
void exp_tests(void);

//
// Reduces or increases x to fit in the range [-2pi, 2pi]
//
// x:   Double above or below the trig domain
//
static double fit_to_domain(double x);

int main(int argc, char **argv) {
  int c = 0;
  enum options input_arg;

  if (argc == 1) {
    puts("Error: no arguments supplied!");
    return -1;
  }

  if (argc > 2) {
    puts(
        "Error: too many arguments supplied! Only processing the final arg...");
  }

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      input_arg = SIN;
      break;
    case 'c':
      input_arg = COS;
      break;
    case 't':
      input_arg = TAN;
      break;
    case 'e':
      input_arg = EXP;
      break;
    case 'a':
      input_arg = ALL;
      break;
    }
  }

  switch (input_arg) {
  case SIN:
    sin_tests();
    break;
  case COS:
    cos_tests();
    break;
  case TAN:
    tan_tests();
    break;
  case EXP:
    exp_tests();
    break;
  case ALL:
    sin_tests();
    cos_tests();
    tan_tests();
    exp_tests();
    break;
  }

  return 0;
}

double Sin(double x) {
  fit_to_domain(x);
  double sqr = x * x;
  double numerator
      = x
        * (sqr * (sqr * (52785432 - 479249 * sqr) - 1640635920) + 11511339840);
  double denom
      = sqr * (sqr * (18361 * sqr + 3177720) + 277920720) + 11511339840;
  return numerator / denom;
}

double Cos(double x) {
  fit_to_domain(x);
  double sqr = x * x;
  double numerator
      = sqr * (sqr * (1075032 - 14615 * sqr) - 18471600) + 39251520;
  double denom = ((127 * sqr + 16632) * sqr + 1154160) * sqr + 39251520;
  return numerator / denom;
}

double Tan(double x) {
  fit_to_domain(x);
  double sqr = x * x;
  double numerator
      = x * (sqr * (sqr * (sqr * (sqr - 990) + 135135) - 4729725) + 34459425);
  double denom
      = 45 * (sqr * (sqr * (sqr * (sqr - 308) + 21021) - 360360) + 765765);
  return numerator / denom;
}

double Exp(double x) {
  int n = 1;
  double ans = 1.0, term = 1.0;
  while (term > EPSILON) {
    term *= x / n++;
    ans += term;
  }
  return ans;
}

void sin_tests(void) {
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "x", "Sin", "Library", "Difference");
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "-", "---", "-------", "----------");
  double step = PI / 16;
  double two_pi = PI * 2;
  for (double i = -1 * two_pi; i <= two_pi; i += step) {
    double x = Sin(i);
    double y = sin(i);
    double diff = x - y;
    printf("%6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, x, y, diff);
  }
}

void cos_tests(void) {
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "x", "Cos", "Library", "Difference");
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "-", "---", "-------", "----------");
  double step = PI / 16;
  double two_pi = PI * 2;
  for (double i = -1 * two_pi; i <= two_pi; i += step) {
    double x = Cos(i);
    double y = cos(i);
    double diff = x - y;
    printf("%6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, x, y, diff);
  }
}

void tan_tests(void) {
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "x", "Tan", "Library", "Difference");
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "-", "---", "-------", "----------");
  double step = PI / 16;
  double third_pi = PI / 3;
  for (double i = -1 * third_pi; i <= third_pi; i += step) {
    double x = Tan(i);
    double y = tan(i);
    double diff = x - y;
    printf("%6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, x, y, diff);
  }
}

void exp_tests(void) {
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "x", "Exp", "Library", "Difference");
  printf("%-7s\t %-10s\t %-10s\t %-12s\n", "-", "---", "-------", "----------");
  for (double i = .0; i <= 9.0; i += 0.1) {
    double x = Exp(i);
    double y = exp(i);
    double diff = x - y;
    printf("%6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, x, y, diff);
  }
}

double fit_to_domain(double x) {
  double two_pi = PI * 2;
  if (x < (-1 * two_pi)) {
    x += two_pi;
    if (x < (-1 * two_pi)) {
      fit_to_domain(x);
    } else {
      return x;
    }
  } else if (x > two_pi) {
    x -= two_pi;
    if (x > two_pi) {
      fit_to_domain(x);
    } else {
      return x;
    }
  } else {
    return x;
  }
  return x;
}
