#ifndef RCCPMIP_H_
#define RCCPMIP_H_

#include "CycleList.h"
#include "CycleCover.h"
#include <ilcplex/ilocplex.h>

using namespace std;

CycleCover& OptimizeRCCP(CycleList &cl);

#endif /* RCCPMIP_H_ */
