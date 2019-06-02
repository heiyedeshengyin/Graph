#include "graph.cpp"
#include <string>

int main()
{
	hjr::graph<std::string, std::string> g1(true);
	g1.print();

	g1.remove_edge(1, 2);
	g1.print();

	std::cout << g1.get_ver_data(0) << std::endl;
	std::cout << g1.get_ver_indegree(0) << std::endl;
	std::cout << g1.get_ver_outdegree(0) << std::endl;

	return 0;
}