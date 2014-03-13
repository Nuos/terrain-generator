#include "random.h"

Random::Random() {
  srand(static_cast <unsigned> (time(0)));
}

Random::Random(int seed) {
  srand(seed);
}

Random::Random(double seed) {
  srand(seed);
}

Random::Random(float seed) {
  srand(seed);
}

int Random::Integer(int minimum, int maximum) {
  return minimum + (std::rand() % (maximum - minimum + 1));
}

double Random::Double(double minimum, double maximum) {
  return minimum + fmod(std::rand(), (maximum - minimum + 1.0));
}

float Random::Float(float minimum, float maximum) {
  return minimum + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maximum - minimum)));
}