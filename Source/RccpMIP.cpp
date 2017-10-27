#include "RccpMIP.h"

CycleCover& OptimizeRCCP(CycleList &cl) {
	IloEnv env;

	// Criando um modelo
	IloModel modelo(env);

	// Variável x associada a cada cilco
	int n = cl.cycles.size();
	IloBoolVarArray x(env, n);

	// Adicionando a variável x no modelo
	char var[100];
	for (int i = 0; i < n; i++) {
		sprintf(var, "X(%d)", i);
		x[i].setName(var);
		modelo.add(x[i]);
	}

	IloExpr SumX(env);
	//Inclusao dos ciclos degenerados no custo da função objetivo
	for (unsigned int i = 0; i < cl.N; i++) {
		SumX += cl.M * x[i];
	}
	for (int i = cl.N; i < n; i++) {
		SumX += x[i];
	}

	// Adicionando a FO
	modelo.add(IloMinimize(env, SumX));

	// Restricoes 1 - Para cada vértice v do grafo original um e somente um ciclo ue passa por v estará na solução 
	for (unsigned int i = 0; i < cl.N; i++) {
		vector<int> &index = cl.vertexCycles[i];
		IloExpr SumCv(env);
		for (unsigned int j = 0; j < index.size(); ++j)
			SumCv += x[index[j]];

		modelo.add(SumCv == 1);
	}

	IloCplex RCCP(modelo);
	RCCP.setOut(env.getNullStream());

	RCCP.solve();

	// Constroe CycleCover da solução
	CycleCover& cover = *(new CycleCover((cl.N/3)+1));

	for (int i = 0; i < n; i++) {
		if (RCCP.getValue(x[i]) > 0.99){
			cover.push_back(cl.cycles[i]);
		}
	}

	return cover;

}
