#include <ogdf/decomposition/StaticSPQRTree.h>
#include <ogdf/fileformats/GraphIO.h>
#include <chrono>
#include <ogdf/basic/graph_generators/randomized.h>
using namespace ogdf;

int main(int argc, char* argv[]){
	Graph G;
	std::ofstream myfile;
	
	// Replace FILENAME with the name of the file
	if(!GraphIO::read(G, "FILENAME", GraphIO::readGML)){
		std::cerr << "Could not read the input graph" << std::endl;
		return 1;
	}

	auto start = std::chrono::steady_clock::now();
	StaticSPQRTree *T= new StaticSPQRTree(G);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}