#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <limits> 
#include <set>
#include <utility> 
#include <algorithm>
#include <iterator>


typedef int vertex_t;
typedef double weight_t;
typedef double average_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();
class character
{
public:
	static int getfirst() {
		return first;
	}
	int getsecond() {
		return second;
	}
private:
	int second;
	static int first;
};
struct neighbor {
	static int first;
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

void DijkstraComputePaths(vertex_t source,
	const adjacency_list_t &adjacency_list,
	std::vector<weight_t> &min_distance,
	std::vector<vertex_t> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());


		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
		neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));
				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));

			}

		}
	}
}

std::list<vertex_t> DijkstraGetShortestPathTo(
	vertex_t vertex, const std::vector<vertex_t> &previous)
{
	std::list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


int main()
{
	int a;
	std::fstream fileOne("c:\\Users\\rados\\Desktop\\distance.txt", std::ios_base::in);
	std::fstream fileTwo("c:\\Users\\rados\\Desktop\\MaxSpeed.txt", std::ios_base::in);
	std::fstream fileThree("c:\\Users\\rados\\Desktop\\Average.txt", std::ios_base::in);
	std::vector<double> distance, maxSpeed, average;
	std::vector<average_t> calculated;
	average_t sum = 0;
	while (fileOne >> a) { distance.push_back(a); }
	while (fileTwo >> a) { maxSpeed.push_back(a); }
	while (fileThree >> a) { average.push_back(a); }

	// first we make a graph to find the find the shortest distance
	adjacency_list_t adjacency_list(9);
	// 0 = Sofia
	adjacency_list[0].push_back(neighbor(1, distance.at(0)));
	adjacency_list[0].push_back(neighbor(2, distance.at(1)));
	adjacency_list[0].push_back(neighbor(3, distance.at(4)));
	// 1 = Plovdiv
	adjacency_list[1].push_back(neighbor(0, distance.at(0)));
	adjacency_list[1].push_back(neighbor(4, distance.at(2)));
	// 2 = Pernik
	adjacency_list[2].push_back(neighbor(0, distance.at(1)));
	adjacency_list[2].push_back(neighbor(8, distance.at(10)));
	adjacency_list[2].push_back(neighbor(6, distance.at(6)));
	adjacency_list[2].push_back(neighbor(7, distance.at(8)));
	// 3 = Karlovo
	adjacency_list[3].push_back(neighbor(0, distance.at(4)));
	adjacency_list[3].push_back(neighbor(4, distance.at(5)));
	// 4 = Stara Zagora
	adjacency_list[4].push_back(neighbor(3, distance.at(5)));
	adjacency_list[4].push_back(neighbor(5, distance.at(3)));
	adjacency_list[4].push_back(neighbor(1, distance.at(2)));
	// 5 = Burgas
	adjacency_list[5].push_back(neighbor(4, distance.at(3)));
	// 6 = Dupnica
	adjacency_list[6].push_back(neighbor(2, distance.at(6)));
	adjacency_list[6].push_back(neighbor(8, distance.at(9)));
	adjacency_list[6].push_back(neighbor(7, distance.at(7)));
	// 7 = Kustendil
	adjacency_list[7].push_back(neighbor(6, distance.at(7)));
	adjacency_list[7].push_back(neighbor(2, distance.at(8)));
	// 8 = Blagoevgrad
	adjacency_list[8].push_back(neighbor(6, distance.at(9)));
	adjacency_list[8].push_back(neighbor(2, distance.at(10)));

	std::vector<weight_t> min_distance;
	std::vector<vertex_t> previous;
	for (size_t i = 0; i < distance.size(); i++) { calculated.push_back(distance[i] / average[i]); }
	DijkstraComputePaths(0, adjacency_list, min_distance, previous);
	std::cout << "Shortest distance from 0(Sofia) to 5(Burgas): " << min_distance[5] << std::endl;
	std::list<vertex_t> path = DijkstraGetShortestPathTo(5, previous);
	std::cout << "Path : ";
	std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	for (size_t i = 3; i <= 5; i++) { sum += calculated[i]; }
	std::cout << std::endl;
	std::cout << "Expected time to arrive (Distance / Average Speed): " << sum << std::endl;
	std::cout << std::endl;
	std::cout << "Shortest distance from 0(Sofia) to 7(Kustendil): " << min_distance[7] << std::endl;
	sum = 0;
	sum += calculated[1] + calculated[8];
	std::cout << "Expected time to arrive (Distance / Average Speed): " << sum << std::endl;
	std::list<vertex_t> path2 = DijkstraGetShortestPathTo(7, previous);
	std::cout << "Path : ";
	std::copy(path2.begin(), path2.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	std::cout << std::endl;
	std::cout << std::endl;

	// second we create a graph to find the minimal time by dividing the distance by the maximum speed allowed
	adjacency_list_t adjacency_listTwo(9);
	// 0 = Sofia
	adjacency_listTwo[0].push_back(neighbor(1, distance.at(0) / maxSpeed.at(0)));
	adjacency_listTwo[0].push_back(neighbor(2, distance.at(1) / maxSpeed.at(1)));
	adjacency_listTwo[0].push_back(neighbor(3, distance.at(4) / maxSpeed.at(4)));
	// 1 = Plovdiv							   				  				  
	adjacency_listTwo[1].push_back(neighbor(0, distance.at(0) / maxSpeed.at(0)));
	adjacency_listTwo[1].push_back(neighbor(4, distance.at(2) / maxSpeed.at(2)));
	// 2 = Pernik												  			  
	adjacency_listTwo[2].push_back(neighbor(0, distance.at(1) / maxSpeed.at(1)));
	adjacency_listTwo[2].push_back(neighbor(8, distance.at(1) / maxSpeed.at(10)));
	adjacency_listTwo[2].push_back(neighbor(6, distance.at(6) / maxSpeed.at(6)));
	adjacency_listTwo[2].push_back(neighbor(7, distance.at(8) / maxSpeed.at(8)));
	// 3 = Karlovo												  	 		  
	adjacency_listTwo[3].push_back(neighbor(0, distance.at(4) / maxSpeed.at(4)));
	adjacency_listTwo[3].push_back(neighbor(4, distance.at(5) / maxSpeed.at(5)));
	// 4 = Stara Zagora											     			
	adjacency_listTwo[4].push_back(neighbor(3, distance.at(5) / maxSpeed.at(5)));
	adjacency_listTwo[4].push_back(neighbor(5, distance.at(3) / maxSpeed.at(3)));
	adjacency_listTwo[4].push_back(neighbor(1, distance.at(2) / maxSpeed.at(2)));
	// 5 = Burgas												     			
	adjacency_listTwo[5].push_back(neighbor(4, distance.at(3) / maxSpeed.at(3)));
	// 6 = Dupnica												    			
	adjacency_listTwo[6].push_back(neighbor(2, distance.at(6) / maxSpeed.at(6)));
	adjacency_listTwo[6].push_back(neighbor(8, distance.at(9) / maxSpeed.at(9)));
	adjacency_listTwo[6].push_back(neighbor(7, distance.at(7) / maxSpeed.at(7)));
	// 7 = Kustendil											   			 
	adjacency_listTwo[7].push_back(neighbor(6, distance.at(7) / maxSpeed.at(7)));
	adjacency_listTwo[7].push_back(neighbor(2, distance.at(8) / maxSpeed.at(8)));
	// 8 = Blagoevgrad										  			  
	adjacency_listTwo[8].push_back(neighbor(6, distance.at(9) / maxSpeed.at(9)));
	adjacency_listTwo[8].push_back(neighbor(2, distance.at(10) / maxSpeed.at(10)));

	std::vector<weight_t> min_time;
	std::vector<vertex_t> previousTwo;
	DijkstraComputePaths(0, adjacency_listTwo, min_time, previousTwo);
	std::cout << "Shortest time (Distance / Max Speed) from 0(Sofia) to 5(Burgas): " << min_time[5] << std::endl;
	std::list<vertex_t> pathTime = DijkstraGetShortestPathTo(5, previousTwo);
	std::cout << "Path : ";
	std::copy(pathTime.begin(), pathTime.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Shortest time (Distance / Max Speed) from 0(Sofia) to 7(Kustendil): " << min_time[7] << std::endl;
	std::list<vertex_t> pathTime2 = DijkstraGetShortestPathTo(7, previousTwo);
	std::cout << "Path : ";
	std::copy(pathTime2.begin(), pathTime2.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << character::getfirst;
	std::system("pause");

	return 0;
}