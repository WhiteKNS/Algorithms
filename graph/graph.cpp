// graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <stack>
#include <iostream>

typedef unsigned int u32;

#define MARK_VISITED 1
#define MARK_UNVISITED 0

class graph {
	int **matrix;
	u32 size;

public:
	graph (const u32 s) : size(s) {

		matrix = new int*[size];

		for (u32 i = 0; i < size; ++i) {
			matrix[i] = new int[size];
		}

		for(u32 i = 0; i < size; ++i) {
			for (u32 j = 0; j < size; ++j) {
				matrix[i][j] = 0;
			}
		}
	}

	graph (int **arr, const u32 s) : size(s) {
		for(u32 i = 0; i < size; ++i) {
			for (u32 j = 0; j < size; ++j) {
				matrix[i][j] = arr[i][j];
			}
		}
	}

	~graph() {
		for(u32 i = 0; i < size; ++i) {
			delete matrix[i];
		}

		delete matrix;
	}

	void print_matrix () {
		for(u32 i = 0; i < size; ++i) {
			for (u32 j = 0; j < size; ++j)
				std::cout << matrix[i][j] << " ";

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	void add_edge (const u32 source, const u32 dest) {
		matrix[source][dest] = 1;
	}

	void breadth_first_traversal (const int started_data) {
		std::cout << "Breadth First Traversal" << std::endl;

		int *visited_matrix  = new int[size];

		for(u32 i = 0; i < size; ++i) {
			visited_matrix[i] = MARK_UNVISITED;
		}

		std::list<int> visited_list;

		visited_list.push_back(started_data);

		while(!visited_list.empty()) {
			int data = visited_list.front();

			visited_list.pop_front();

			if (visited_matrix[data] == MARK_VISITED)
				continue;

			std::cout << data << " ";
			
			visited_matrix[data] = MARK_VISITED;

			for (u32 i = 0; i < size; ++i) {
				if (matrix[data][i]) {
					visited_list.push_back(i);
				}
			}
		}

		std::cout << std::endl;

		delete visited_matrix;
	}

	void depth_first_traversal(const int started_data) {
		std::cout << "Depth First Traversal" << std::endl;

		int *visited_matrix = new int[size];

		for (u32 i = 0; i < size; ++i)
			visited_matrix[i] = MARK_UNVISITED;

		std::stack<int> visited;

		visited.push(started_data);

		while(!visited.empty()) {
			int data = visited.top();

			if (visited_matrix[data] == MARK_UNVISITED) {
				visited_matrix[data] = MARK_VISITED;

				std::cout << data << " ";
			}

			bool added_to_stack = false;
			for (u32 i = 0; i < size; ++i) {
				if (matrix[data][i] && visited_matrix[i] == MARK_UNVISITED) {
					visited.push(i);
					added_to_stack = true;
					break;
				}
			}

			if (!added_to_stack) {
				visited.pop();
			}
		}

		std::cout << std::endl;

		delete visited_matrix;
	}
};

int main ()
{
	graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 3);

    g.depth_first_traversal(2);

	g.breadth_first_traversal(2);

	system("pause");
    return 0;
}

