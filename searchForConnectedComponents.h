#ifndef SEM2LAB3_SEARCHFORCONNECTEDCOMPONENTS_H
#define SEM2LAB3_SEARCHFORCONNECTEDCOMPONENTS_H


#include <vector>
#include <map>
#include <limits>
#include "graph.h"
using namespace std;

template <typename T>
map<T, int> FindConComponents(Graph<T>* graph) {
    cout << "imax " << INT_MAX << endl;
    map<T, int> points;
    int cast = 1;
    for (int i = 0; i < graph->GetPoints()->GetLength(); i++) {
        if (!points[graph->GetPoints()->Get(i)->GetData()]) {
            points[graph->GetPoints()->Get(i)->GetData()] = cast;
            auto vec = graph->bfs(graph->GetPoints()->Get(i)->GetData());
            for (int j = 0; j < vec.size(); j++) {
                if (vec[j].second < INT_MAX) {
                    points[vec[j].first] = cast;
                }
            }
            cast++;
        }
    }

    for (auto p : points) {
        cout << p.first << " cast: " << p.second << endl;
    }
    return points;

}

#endif //SEM2LAB3_SEARCHFORCONNECTEDCOMPONENTS_H
