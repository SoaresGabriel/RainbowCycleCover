#ifndef CYCLE_H_
#define CYCLE_H_

#include <vector>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;

class Cycle : public vector<int> {
public:
	bool isTrivial();

	bool operator==(Cycle& other);

};

#endif /* CYCLE_H_ */
