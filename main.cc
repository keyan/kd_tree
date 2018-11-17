#include <ctime>
#include <iostream>
#include <random>

#include "kd_tree.h"

int main() {
  int num_points = 10000;

  // Seed with a real random value, if available
  std::random_device r;

  double lat_lower_bound = -90;
  double lat_upper_bound = 90;
  std::uniform_real_distribution<double> rand_lat(
      lat_lower_bound, lat_upper_bound);
  double lng_lower_bound = -180;
  double lng_upper_bound = 180;
  std::uniform_real_distribution<double> rand_lng(
      lng_lower_bound, lng_upper_bound);
  std::default_random_engine re(r());

  std::vector<Point> points;
  for (size_t i = 0; i < num_points; ++i) {
    Point p = {rand_lat(re), rand_lng(re)};
    points.emplace_back(p);
  }

  KDTree tree = KDTree(2);
  for (Point p : points) {
    tree.insert(p);
  }

  std::clock_t begin = std::clock();
  for (size_t i = 0; i < num_points; ++i) {
    Point p = {rand_lat(re), rand_lng(re)};
    tree.nearest(p);
  }
  std::clock_t end = std::clock();
  double total_secs = double(end - begin) / CLOCKS_PER_SEC;

  std::cout << "Total secs: " << total_secs << std::endl;
  std::cout << "Time per query: " << total_secs / num_points << std::endl;

  return 0;
}
