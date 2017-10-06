/*
 * Cycle.h
 *
 *  Created on: 27 de set de 2017
 *      Author: gabri
 */

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
