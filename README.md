# kdtree

C++11 single header file k-d tree implementation, supports dynamic insertion and nearest neighbor queries.

Implementation based on lecture notes from Dr. David Mount:
http://www.cs.umd.edu/users/mount/420/Lects/420lects.pdf

## Usage

- Copy `kdtree.h` to your project and include during compilation
- Only supports `insert()` and `nearest()` operations
- Example usage:
	```
	#include "kdtree.h"

	// Specify dimension count K
	KDTree tree = KDTree(3);

	// Insert points as std::vector with length K
	std::vector<double> p = {1, 2, 3};
	tree.insert(p);

	// Query for nearest point
	std::vector<double> s = {5, 6, 7};
	std::vector<double> nearby_point = tree.nearest(s);
	```
