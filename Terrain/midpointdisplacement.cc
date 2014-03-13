#include "midpointdisplacement.h"

MidpointDisplacement::MidpointDisplacement(int n, int wmult, int hmult, float smoothness, float fineness) {
  n_ = n;
  wmult_ = wmult;
  hmult_ = hmult;
  smoothness_ = smoothness;
  fineness_ = fineness;
  grass_threshold_ = 1.25;
  water_threshold_ = 0.55;
  sand_threshold_ = 0.70;
  deep_water_threshold_ = 0.0001;
  hills_threshold_ = 2.60;
  shallow_mountains_threshold_ = 2.92;
  high_mountains_threshold_ = 0;
  random_ = Random();
}

int MidpointDisplacement::CoordinatesToVectorIndex(int x, int y) {
  int i = 0;
  i = x + y * width_;
  return i;
}
std::pair<int, int> MidpointDisplacement::VectorIndexToCoordinates(int i) {
  int x = 0;
  int y = 0;
  y = i / width_;
  x = i % width_;
  return std::make_pair(x, y);
}

std::vector<int> MidpointDisplacement::GetMap() {
  int power = pow(2, n_);
  int width = wmult_ * power + 1;
  int height = hmult_ * power + 1;

  width_ = width;
  height_ = height;

  std::vector<float> map;
  std::vector<int> return_map;

  map.resize(width_ * height_);
  return_map.resize(width_ * height_);

  int step = power / 2;
  float sum;
  int count;

  float h = fineness_;

  for (int i = 0; i < width_; i += 2 * step) {
    for (int j = 0; j < height_; j+= 2 * step) {
      map.at(CoordinatesToVectorIndex(i, j)) = random_.Float(0, 2 * h); //???
    }
  }

  for (int i = 0; i < width_; i++) {
    map.at(CoordinatesToVectorIndex(i, 0)) = random_.Float(-3, -2);
    map.at(CoordinatesToVectorIndex(i, height_ - 1)) = random_.Float(-2, -1);
  }

  for (int i = 0; i < height_; i++) {
    map.at(CoordinatesToVectorIndex(0, i)) = random_.Float(-3, -2);
    map.at(CoordinatesToVectorIndex(width_ - 1, i)) = random_.Float(-3, -2);
  }

  map.at(CoordinatesToVectorIndex((width_ - 1) / 2, (height_ - 1) / 2)) = (2 * h) + random_.Float(1, 5);
  /*map.at(CoordinatesToVectorIndex(0, 0)) = -3;
  map.at(CoordinatesToVectorIndex((width_ - 1), 0)) = -3;
  map.at(CoordinatesToVectorIndex(0, (height_ - 1))) = -3;
  map.at(CoordinatesToVectorIndex((width_ - 1), (height_ - 1))) = -3;
  map.at(CoordinatesToVectorIndex((width_ - 1) / 2, (height_ - 1) / 2)) = 3;*/

  while(step > 0) {

    //Diamond
    for (int x = step; x < width_; x += 2 * step) {
      for (int y = step; y < height_; y += 2 * step) {
        sum = map.at(CoordinatesToVectorIndex(x - step, y - step)) + map.at(CoordinatesToVectorIndex(x - step, y + step)) + map.at(CoordinatesToVectorIndex(x + step, y - step)) + map.at(CoordinatesToVectorIndex(x + step, y + step));
        map.at(CoordinatesToVectorIndex(x, y)) = sum / 4 + random_.Float(-h, h); //???
      }
    }

    //Square
    for (int x = 0; x < width_; x += step) {
      for (int y = step * (1 - (x / step) % 2); y < height_; y += 2 * step) {
        sum = 0;
        count = 0;
        if(x - step >= 0) {
          sum += map.at(CoordinatesToVectorIndex(x - step, y));
          count++;
        }
        if(x + step < width) {
          sum += map.at(CoordinatesToVectorIndex(x + step, y));
          count++;
        }
        if(y - step >= 0) {
          sum += map.at(CoordinatesToVectorIndex(x, y - step));
          count++;
        }
        if(y + step < height_) {
          sum += map.at(CoordinatesToVectorIndex(x, y + step));
          count++;
        }
        if(count > 0) {
          map.at(CoordinatesToVectorIndex(x, y)) = sum / count + random_.Float(-h, h); //???
        } else {
          map.at(CoordinatesToVectorIndex(x, y)) = 0;
        }
      }
    }
    h /= smoothness_;
    step /= 2;
  }

  float max = std::numeric_limits<float>::max();
  float min = std::numeric_limits<float>::min();

  for (unsigned int i = 0; i < map.size(); i++) {
    if(map.at(i) > max) {
      map.at(i) = max;
    }
    if(map.at(i) < min) {
      map.at(i) = min;
    }
  }

  for (unsigned int i = 0; i < map.size(); i++) {
    //std::cout << map.at(i);
    //map.at(i) = (map.at(i) - min) / (max - min);
    //std::cout << map.at(i);
    float value = map.at(i);
    int new_value = 0;
    if(value < deep_water_threshold_) {
      new_value = 1;
    } else if (value < water_threshold_) {
      new_value = 2;
    } else if (value < sand_threshold_) {
      new_value = 3;
    } else if (value < grass_threshold_) {
      new_value = 4;
    } else if (value < hills_threshold_) {
      new_value = 5;
    } else if (value < shallow_mountains_threshold_) {
      new_value = 6;
    } else if (value < high_mountains_threshold_) {
      new_value = 7;
    } else {
      new_value = 7;
    }
   // new_value = (value * 255) + 255;
    return_map.at(i) = new_value;
  }
  return return_map;
}

