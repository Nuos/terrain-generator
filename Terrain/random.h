#include <time.h>
#include <cstdlib>
#include <cmath>

class Random {
 public:
  Random();
  Random(int seed);
  Random(double seed);
  Random(float seed);
  ~Random() {}
  int Integer(int minimum, int maximum);
  double Double(double minimum, double maximum);
  float Float(float minimum, float maximum);
};