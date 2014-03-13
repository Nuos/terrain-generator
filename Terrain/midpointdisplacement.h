#include <vector>
#include <limits>
#include <iostream>

#include "random.h"

class MidpointDisplacement {
 public:
  MidpointDisplacement(int n, int wmult, int hmult, float smoothness, float fineness);
  ~MidpointDisplacement() {}
  std::vector<int> GetMap();
  int width() const { return width_; }
  int height() const { return height_; }
private:
  int CoordinatesToVectorIndex(int x, int y);
  std::pair<int, int> VectorIndexToCoordinates(int i);
  float grass_threshold_;
  float water_threshold_;
  float sand_threshold_;
  float deep_water_threshold_;
  float hills_threshold_;
  float shallow_mountains_threshold_;
  float high_mountains_threshold_;
  int n_;
  int wmult_;
  int hmult_;
  float smoothness_;
  float fineness_;
  int width_;
  int height_;
  Random random_;
};