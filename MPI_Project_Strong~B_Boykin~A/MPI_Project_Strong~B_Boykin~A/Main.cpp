#include <mpi.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <KDTree.h>
#include <string>
#include <vector>
#include <sstream>


//Read the following commented out section for what to do:
/*
Process:
1. Generate KD-Tree using random points.
2. Read eval points from file
3. For each eval pt, pompute 1-nn  across all K-D trees.

``````````````````````
SO:
Eval pt.
NEarest pt
Dist
``````````````````````
TURN IN:
-Vis Studio project
-Experiment doc
-ReadMe

Xi MIN((y0,d0),(y1,d1))...)

	P0			P1
	/\   1000	/\
   ()()		   ()()
*/


//Read the following commented out section for how to do it (possibly)
/*

//STRUCTS are: X[dim]    owner
//CACHE are: Vector     MAX_Size


cache = {5}

vector results
que request
que recieved

while(KD){
	if(!s.empty){
		point P = s.front()
		results.push(tree dist(P,1))
		isend(p.owner)}
	}
	if(s.mem-size < s.len()){
		isend(any,"send points")
		}
	if(request.front()=="Cache not full"{
		isend(request.front.owner(), si[curr])
		request front().povoc()
		}
	if(recieved.front()="result"{
		result.push(recieved, front)
		recieved.p++
		}
	if( results){
		results.p***(1-ls[],1))
	
	recieve();
}



*/


using namespace std;

vector<vector<int>> getArrayFromFile(string fileName);
void take_input(int* n_p, int* local_n_p, int rank, int comm_size, MPI_Comm comm);
void chck_err(int local_chck, char f_name[], char msg[], MPI_Comm comm);
void readData(double localVector1[], double localVector2[], double* scalar_p, int localN, int rank, int comm_size, MPI_Comm comm);
void printVector(double localVector[], int localN, int n, char title[], int rank, MPI_Comm comm);
void output(vector<int> v, KDNode<int>* nearestptr, float disKD);


ifstream inputFile;
ofstream outputfile;						//outputs it to a text file named 1_NN_X.txt


//MPI_Comm commun = MPI_COMM_WORLD;



KDTree<int> Tree;

void generate_random_point(int* p, int sd)
{
	for (int k = 0; k<sd; k++)
		p[k] = rand() % RMAX;
}

void GenerateRandomTree(int nNodes)
{
	int p[SD]; // random point
	for (int n = 0; n<nNodes; n++)
	{
		generate_random_point(p, SD);
		Tree.add(p);
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN


int main(int argc, char **argv) {
	/*
	int n, localN;						//vector sizes
	int commun_size, rank;				//size and rank
	int numProcesses;
	int pointTarget[SD];
	double *localVec1, *localVec2;		//Vector
	float disKD;						//Distance in KDTree


//	MPI_Init(&argc, &argv);				//initializes the program

	
	


//	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);		//Number
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);				//Rank



	KDNode<int>* nearest = Tree.find_nearest(pointTarget); //Finds nearest pt.
	disKD = (float)sqrt(Tree.d_min);
	for (int i = 0; i < SD; i++)
		cout << nearest -> x[i] << " ";
	cout << endl;
	cout << "Distance: " << disKD << endl;

//	MPI_Barrier(MPI_COMM_WORLD);
	auto done = std::chrono::high_resolution_clock::now();
	cout << "Execution time (Ms):";
		//std::chrono::duration_cast <std::chrono::milliseconds>(done - started).count();




	
//	MPI_Finalize();*/
	vector<vector<int>> v = getArrayFromFile("F:\\benji\\Documents\\Visual Studio 2015\\PROJECTS FROM F\\MPI_Project_Strong~B_Boykin~A\\poop.txt");

	
	srand(time(NULL));
	GenerateRandomTree(POINTS_NUM);

	outputfile.open("outputFILE.txt", ios::out);
	auto start = std::chrono::high_resolution_clock::now();
	while (!v.empty()) {
		vector<int> subList = v.back();
		int* thisProjectSucksWhyAreYouMakingUsDoThisYouSadist = subList.data();

		KDNode<int>* nearest = Tree.find_nearest(thisProjectSucksWhyAreYouMakingUsDoThisYouSadist);
		float disKD = (float)sqrt(Tree.d_min);

		for (int i = 0; i < SD; i++)
			cout << nearest->x[i] << " ";
		cout << endl;
		cout << "Distance: " << disKD << endl;

		string temp = " ";
		while (!subList.empty()) {
			temp += to_string(subList.back()) + ";";
			subList.pop_back();
		}

		for (int i = 0; i < SD; i++) {
			temp += to_string(nearest->x[i]) + "__";
		}

		temp += to_string(disKD);
		outputfile << temp;
		v.pop_back();
		
	}
	auto end = std::chrono::high_resolution_clock::now();
	outputfile << "Time taken (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	outputfile.close();
	return 0;
}

vector<vector<int>> getArrayFromFile(string fileName) {		//This is an attempt.
	ifstream file;
	file.open(fileName, ios :: in);
	vector<vector<int>> vectors;
	if (file) {
		string line;
		while (getline(file, line)) {
			vector<int> elements;
			int i = 0;
			istringstream issLine(line);
			while (issLine >> i) {
				elements.push_back(i);
			}
			vectors.push_back(elements);
			elements.clear();
		}
	}
	else {
		cout << "Error opening file" << endl;
	}
	file.close();
	return vectors;
}


void output(vector<int> v, KDNode<int>* nearestptr, float disKD) {
	string temp = " ";
	while (!v.empty()) {
		temp += to_string(v.back()) + ";";
		v.pop_back();
	}

	for (int i = 0; i < SD; i++) {


		temp += to_string(nearestptr->x[i]) + "__";
	}

	temp += to_string(disKD);

	outputfile.open("outputFILE.txt", ios::out||ios::app);
	outputfile << temp;
	outputfile.close();

}