#ifndef KD_TREE_H_
#define KD_TREE_H_

#include <iostream>
#include <stdexcept>
#include <vector>

using Point = std::vector<double>;

inline double distance(Point const& p1, Point const& p2) {
  double d = 0;

  for (size_t i = 0; i < p1.size(); ++i) {
    double di = p1.at(i) - p2.at(i);
    d += di * di;
  }

  return d;
}

class KDTree {
private:
  struct KDNode {
    KDNode(Point p)
        : point_(p) {}

    Point point_;
    KDNode* left_ = nullptr;
    KDNode* right_ = nullptr;
  };

  struct KDNNResultData {
    KDNNResultData(KDNode* node, double dist)
        : node_(node)
        , dist_(dist) {}

    KDNode* node_;
    double dist_;
  };

  KDNNResultData
  nearest(Point& p, KDNode* node, int cut_dimension, KDNNResultData best) {
    if (!node) {
      return best;
    }

    double dist = distance(node->point_, p);
    if (dist < best.dist_) {
      best.node_ = node;
      best.dist_ = dist;
    }

    if (p.at(cut_dimension) < node->point_.at(cut_dimension)) {
      best = nearest(p, node->left_, (cut_dimension + 1) % dimension_, best);

      Point split_point = p;
      split_point[cut_dimension] = node->point_.at(cut_dimension);
      if (distance(p, split_point) < best.dist_) {
        best = nearest(p, node->right_, (cut_dimension + 1) % dimension_, best);
      }
    } else {
      best = nearest(p, node->right_, (cut_dimension + 1) % dimension_, best);

      Point split_point = p;
      split_point[cut_dimension] = node->point_.at(cut_dimension);
      if (distance(p, split_point) < best.dist_) {
        best = nearest(p, node->left_, (cut_dimension + 1) % dimension_, best);
      }
    }

    return best;
  }

  KDNode* insert(Point& p, KDNode* node, int cut_dimension) {
    if (!node) {
      node = new KDNode(p);
    } else if (p == node->point_) {
      throw std::invalid_argument("Error, cannot add duplicate point to tree");
    } else if (p.at(cut_dimension) < node->point_.at(cut_dimension)) {
      node->left_ = insert(p, node->left_, (cut_dimension + 1) % dimension_);
    } else {
      node->right_ = insert(p, node->right_, (cut_dimension + 1) % dimension_);
    }

    return node;
  }

  int dimension_;
  KDNode* root_ = nullptr;

public:
  KDTree(int dimension)
      : dimension_(dimension) {}

  void insert(Point p) { root_ = insert(p, root_, 0); }

  Point nearest(Point p) {
    double dist = distance(root_->point_, p);
    KDNNResultData result = nearest(p, root_, 0, KDNNResultData(root_, dist));

    return result.node_->point_;
  }
};

#endif // KD_TREE_H_
