#include "Util.h"


void shakeArray(vector<int> &array){
	
	int n = array.size();
	
	int disp = rand() % n;
	
	int initial = array[disp];
	
	int next;
	
	for(int i = 0; i < n; i++){
		next = rand() % n;
		array[disp] = array[next];
		disp = next;
	}
	
	array[disp] = initial;
	
}

void shakeList(list<int> &l){

	vector<int> array(l.size());

	int i;
	list<int>::iterator it;

	for(it = l.begin(), i = 0; it != l.end(); it++, i++){
		array[i] = *it;
	}

	shakeArray(array);

	for(it = l.begin(), i = 0; it != l.end(); it++, i++){
		*it = array[i];
	}

}

string getInstanceName(string instance){
	
	string::size_type loc = instance.find_last_of(".", instance.size() );
	string::size_type loc2 = instance.find_last_of("/", instance.size() );
	if(loc2 == string::npos)
			loc2 = instance.find_last_of("\\", instance.size() );
	
	string instanceName;
	if (loc != string::npos) {
		instanceName.append(instance, loc2+1, loc-loc2-1 );
	}
	else {
		instanceName.append(instance, loc2+1, instance.size() );
	}
	
	return instanceName;
}

void printResult(CycleCover &cover, long executionTime, string instance){
	/*imprime resultado no terminal*/
		cout << "Cover Weight: " << cover.weight() << endl;
		cout << "Non Trivial Cycles: " << cover.nonTrivialCount() << endl;
		cout << "Trivial Cycles: " << cover.trivialCount() << endl;
		for (unsigned int i = 0; i < cover.size(); i++) {
			cout << cover[i].size() << " : ";
			for (unsigned int j = 0; j < cover[i].size(); j++) {
				cout << cover[i][j] << " -> ";
			}

		cout << endl;
		}
		cout << "Tempo de execucao: " << executionTime << " ms" << endl;


		/* imprime resultado no arquivo */
		string outFile = "./out/" + getInstanceName(instance) + ".out";
		ofstream outf(outFile, ios::out);

		outf << "Cover Weight: " << cover.weight() << endl;
		outf << "Non Trivial Cycles: " << cover.nonTrivialCount() << endl;
		outf << "Trivial Cycles: " << cover.trivialCount() << endl;
		for (unsigned int i = 0; i < cover.size(); i++) {
			outf << cover[i].size() << " : ";
			for (unsigned int j = 0; j < cover[i].size(); j++) {
				outf << cover[i][j] << " -> ";
			}

		outf << endl;
		}
		outf << "Tempo de execucao: " << executionTime << " ms" << endl;

		outf.close();
}
