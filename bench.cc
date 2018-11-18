#include <ctime>
#include <iostream>
#include <random>

#include "kdtree.h"

using std::cout;
using std::endl;

std::vector<Point> generate_rand_locations(int num_points = 1000000) {
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
    Point p{rand_lat(re), rand_lng(re)};
    points.emplace_back(p);
  }

  return points;
}

int main() {
  std::clock_t begin;
  std::clock_t end;
  double secs;
  std::vector<Point> points = generate_rand_locations();

  KDTree tree = KDTree(2);
  begin = std::clock();
  for (Point p : points) {
    tree.insert(p);
  }
  end = std::clock();
  secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Inserted 1m points in " << secs << "s" << endl;

  std::vector<Point> search_points = generate_rand_locations();
  begin = std::clock();
  for (Point p : search_points) {
    tree.nearest(p);
  }
  end = std::clock();
  secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Searched for 1m points in: " << secs << "s" << endl;

  std::cout << "Time per search: " << ((secs / search_points.size()) * 1e6)
            << "ms" << std::endl;

  return 0;
}
