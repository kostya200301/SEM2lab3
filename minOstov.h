#ifndef SEM2LAB3_MINOSTOV_H
#define SEM2LAB3_MINOSTOV_H

#include <vector>
#include <limits>
#include "graph.h"
using namespace std;
//Каждый раз находим минимальное ребро которое соединяет множество посещенных и не посещенных вершин
template <typename T>
vector<Edge<T>*> FindMinOstov(Graph<T>* graph) {
    vector<Edge<T>*> answer;
    vector<Point<T>*> points_ans;
    map<Point<T>*, bool> peaks;
    points_ans.push_back(graph->GetPoints()->Get(0));
    peaks[graph->GetPoints()->Get(0)] = true;
    while (points_ans.size() < graph->GetPoints()->GetLength()) {
        double minWeight = numeric_limits<double>::max();
        Point<T>* newPoint = NULL;
        Point<T>* p_last = NULL;
        for (auto p : peaks) {
            if (!p.second) {
                continue;
            }
            for (int j = 0; j < p.first->GetEdges()->GetLength(); j++) {
                if (!peaks[p.first->GetEdges()->Get(j).p1] and p.first->GetEdges()->Get(j).weight < minWeight) {
                    minWeight = p.first->GetEdges()->Get(j).weight;
                    newPoint = p.first->GetEdges()->Get(j).p1;
                    p_last = p.first;
                }
            }
        }
        if (newPoint == NULL || p_last == NULL) {
            return vector<Edge<T>*>();
        }
        peaks[newPoint] = true;
        points_ans.push_back(newPoint);
        for (int j = 0; j < p_last->GetEdges()->GetLength(); j++) {
            if (p_last->GetEdges()->Get(j).p1 == newPoint) {
                answer.push_back(&(p_last->GetEdges()->Get(j)));
            }
        }

//        cout << newPoint->GetData() << endl;

    }



    return answer;



}

#endif //SEM2LAB3_MINOSTOV_H
