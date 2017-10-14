#ifndef RCCPMIP_H_
#define RCCPMIP_H_

#include "CycleList.h"
#include "CycleCover.h"
#include <ilcplex/ilocplex.h>
#include <algorithm>
#include <iostream>
#include <sys/time.h>

using namespace std;

CycleCover& OptimizeRCCP(CycleList &cl);

#endif /* RCCPMIP_H_ */
