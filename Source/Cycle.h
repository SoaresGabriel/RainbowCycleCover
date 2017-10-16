#ifndef CYCLE_H_
#define CYCLE_H_

#include <vector>

using namespace std;

class Cycle : public vector<int> {
public:
	bool isTrivial();

	bool operator==(Cycle& other);

};

#endif /* CYCLE_H_ */
