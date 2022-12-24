#ifndef SEM2LAB3_TRAVLLINGSALESMANPROBLEM_H
#define SEM2LAB3_TRAVLLINGSALESMANPROBLEM_H

#include <iostream>
#include "graph.h"
using namespace std;
// Полным перебором
template <typename T>
int TravellingSalesmanProblem(Graph<T>* graph) {
    vector<Point<T>*> vertex;
    for (int i = 0; i < graph->GetPoints()->GetLength(); i++)
        vertex.push_back(graph->GetPoints()->Get(i));
    int min_path = INT_MAX;
    do {
        int current_pathWeight = 0;
        for (int i = 0; i < vertex.size() - 1; i++) {
            for (int j = 0; j < vertex[i]->GetEdges()->GetLength(); j++) {
                if (vertex[i]->GetEdges()->Get(j).p1 == vertex[i + 1]) {
                    current_pathWeight += vertex[i]->GetEdges()->Get(j).weight;
                }
            }
        }

        min_path = min(min_path, current_pathWeight);

    } while (
            next_permutation(vertex.begin(), vertex.end()));

    return min_path;
}

#endif //SEM2LAB3_TRAVLLINGSALESMANPROBLEM_H
