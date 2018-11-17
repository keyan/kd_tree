#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "kd_tree.h"

const double LAT = 47.6043313, LNG = -122.3312752;

TEST_CASE("Add single point to root", "[construct]") {
  KDTree tree = KDTree(2);

  Point p1{LAT, LNG};
  REQUIRE_NOTHROW(tree.insert(p1));
}

TEST_CASE("Add duplicate point throws", "[construct]") {
  KDTree tree = KDTree(2);

  Point p1{LAT, LNG};
  tree.insert(p1);
  REQUIRE_THROWS(tree.insert(p1));
}

TEST_CASE("Add multiple unique points", "[construct]") {
  KDTree tree = KDTree(2);

  Point p1{1.1, 1.1};
  Point p2{2.2, 2.2};
  REQUIRE_NOTHROW(tree.insert(p1));
  REQUIRE_NOTHROW(tree.insert(p2));
}

TEST_CASE("Nearest queries return expected result", "[nearest]") {
  KDTree tree = KDTree(2);

  Point p0{47.604054, -122.355645};
  Point p1{47.628161, -122.309537};
  Point p2{47.619346, -122.274770};
  Point p3{47.573457, -122.376723};
  Point p4{47.618413, -122.303735};
  Point p5{47.624561, -122.330777};
  Point p6{47.718667, -122.331095};
  Point p7{47.562896, -122.348915};
  Point p8{47.642946, -122.360560};
  Point p9{47.565632, -122.337248};
  tree.insert(p0);
  tree.insert(p1);
  tree.insert(p2);
  tree.insert(p3);
  tree.insert(p4);
  tree.insert(p5);
  tree.insert(p6);
  tree.insert(p7);
  tree.insert(p8);
  tree.insert(p9);

  Point source{LAT, LNG};

  std::vector<Point> points = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9};
  Point& best_point = p0;
  double best_dist = 99999999;
  for (Point p : points) {
    double dist = distance(source, p);
    if (dist < best_dist) {
      best_dist = dist;
      best_point = p;
    }
  }

  REQUIRE(tree.nearest(source) == best_point);
}
