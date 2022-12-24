#ifndef SEM2LAB3_GRAPH_H
#define SEM2LAB3_GRAPH_H

#include "Sequence.h"
#include "ArraySequence.h"
#include "IMap.h"
#include <map>
#include <set>
#include <queue>
#include <algorithm>

template <typename T>
class Edge;

template <typename T>
class Point;

template <typename T>
class Edge {
public:
    Point<T>* p1;
    Point<T>* p2;
    double weight;
    Edge(Point<T>* from_, Point<T>* to_, double weight_) {
        p1 = from_;
        p2 = to_;
        weight = weight_;
    }
};


template <typename T>
class Point {
private:
    T data;
    Sequence<Edge<T>>* edges;
public:
    Point(T data_, Sequence<Edge<T>>* edges_) {
        this->data = data_;
        this->edges = edges_;
    }

    Point(T data_) {
        this->data = data_;
        this->edges = new ArraySequence<Edge<T>>();
    }

    void AddPoint(Point<T>* point, double weight=-1) {
        this->edges->Append(Edge<T>(point, this, weight));
    }

    Sequence<Edge<T>>* GetEdges() {
        return this->edges;
    }

    T GetData() {
        return data;
    }

    void SetData(T data_) {
        this->data = data_;
    }
};




template <typename T>
class Graph {
private:
    Sequence<Point<T>*>* graph;
public:
    bool oriented;
    bool weight;
private:
    bool IsNewPoint(Point<T>* point, Point<T>* newPoint, int indexPointInGraph=-1) {
        int i = 0;
        if (indexPointInGraph != -1) {
            i = indexPointInGraph;
        }
        for (i; i < graph->GetLength(); i++) {
            if (graph->Get(i)->GetData() == point->GetData()) {
                for (int j = 0; j < graph->Get(i)->GetEdges()->GetLength(); j++) {
                    if (graph->Get(i)->GetEdges()->Get(j).p1->GetData() == newPoint->GetData()) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

public:
    Graph() {
        this->graph = new ArraySequence<Point<T>*>();
    }

    Graph(Sequence<pair<T, Sequence<T>*>>* gr, bool oriented_) {
        this->oriented = oriented_;
        this->weight = false;
        graph = new ArraySequence<Point<T>*>();
        for (int i = 0; i < gr->GetLength(); i++) {
            this->AddNewPoint(gr->Get(i).first, gr->Get(i).second);
        }
    }

    Graph(Sequence<pair<T, Sequence<pair<T, double>>*>>* gr, bool oriented_) {
        this->oriented = oriented_;
        this->weight = true;
        graph = new ArraySequence<Point<T>*>();
        for (int i = 0; i < gr->GetLength(); i++) {
            this->AddNewPointWithWeight(gr->Get(i).first, gr->Get(i).second);
        }
    }

    Sequence<Point<T>*>* GetPoints() {
        return this->graph;
    }


    void AddNewPoint(T data, Sequence<T>* points) {
        // Add to all Points
        Point<T>* newPoint;
        bool findPoint = false;
        for (int k = 0; k < this->graph->GetLength(); k++) {
            if (this->graph->Get(k)->GetData() == data) {
                newPoint = this->graph->Get(k);
                findPoint = true;
            }
        }
        if (!findPoint){
            newPoint = new Point<T>(data);
            graph->Append(newPoint);
        }
        for (int i = 0; i < points->GetLength(); i++) {
            bool addPoint = false;
            for (int j = 0; j < this->graph->GetLength(); j++) {
                // Если в графе есть вершина в которую мы хотим прийти
                if (this->graph->Get(j)->GetData() == points->Get(i)) {
                    if (!this->oriented and IsNewPoint(graph->Get(j), newPoint, j)){
                        graph->Get(j)->AddPoint(newPoint);
                    }
                    if (IsNewPoint(newPoint, graph->Get(j), j)) {
                        newPoint->AddPoint(graph->Get(j));
                    }
                    addPoint = true;
                    break;
                }
            }
            // Если в графе нет вершины в которую мы можем попасть из этой точки
            if (!addPoint) {
                auto point = new Point<T>(points->Get(i));
                graph->Append(point);
                if (!this->oriented) {
                    point->AddPoint(newPoint);
                }
                newPoint->AddPoint(point);
            }

        }
    }


    void AddNewAdge(T data1, T data2, int weight=-1) {
        if (this->oriented) {
            for (int i = 0; i < this->graph->GetLength(); i++) {
                if (this->graph->Get(i)->GetData() == data1) {
                    this->graph->Get(i)->GetEdges()->Append(Edge<T>(this->GetPointByValue(data2), this->graph->Get(i), weight));
                    return;
                }
            }
        }
        else {
            for (int i = 0; i < this->graph->GetLength(); i++) {
                if (this->graph->Get(i)->GetData() == data1) {
                    this->graph->Get(i)->GetEdges()->Append(Edge<T>(this->GetPointByValue(data2), this->graph->Get(i), weight));
                }
                if (this->graph->Get(i)->GetData() == data2) {
                    this->graph->Get(i)->GetEdges()->Append(Edge<T>(this->GetPointByValue(data1), this->graph->Get(i), weight));
                }
            }
        }
    }

    void DeletePoint(T data) {
        cout << "start delete\n";
        auto point = this->GetPointByValue(data);
        for (int i = 0; i < graph->GetLength(); i++) {
            for (int j = 0; j < graph->Get(i)->GetEdges()->GetLength(); j++) {
                if (graph->Get(i)->GetEdges()->Get(j).p1 == point || graph->Get(i)->GetEdges()->Get(j).p2 == point) {
                    graph->Get(i)->GetEdges()->Delete(j);
                    j--;
                }
            }
        }
        for (int i = 0; i < graph->GetLength(); i++) {
            if (graph->Get(i) == point) {
                this->graph->Delete(i);
                cout << "delete succes\n";
                return;
            }
        }
    }

    void DeleteEdge(T data1, T data2) {
        auto point1 = this->GetPointByValue(data1);
        auto point2 = this->GetPointByValue(data2);
        for (int i = 0; i < graph->GetLength(); i++) {
            for (int j = 0; j < graph->Get(i)->GetEdges()->GetLength(); j++) {
                if (oriented) {
                    if (graph->Get(i)->GetEdges()->Get(j).p2 == point1 and graph->Get(i)->GetEdges()->Get(j).p1 == point2) {
                        graph->Get(i)->GetEdges()->Delete(j);
                        j--;
                    }
                }
                else {
                    if ((graph->Get(i)->GetEdges()->Get(j).p1 == point1 and graph->Get(i)->GetEdges()->Get(j).p2 == point2) or (graph->Get(i)->GetEdges()->Get(j).p2 == point1 and graph->Get(i)->GetEdges()->Get(j).p1 == point2)) {
                        graph->Get(i)->GetEdges()->Delete(j);
                        j--;
                    }
                }

            }
        }
    }


    void AddNewPointWithWeight(T data, Sequence<pair<T, double>>* points) {
        // Add to all Points
        Point<T>* newPoint;
        bool findPoint = false;
        for (int k = 0; k < this->graph->GetLength(); k++) {
            if (this->graph->Get(k)->GetData() == data) {
                newPoint = this->graph->Get(k);
                findPoint = true;
            }
        }
        if (!findPoint){
            newPoint = new Point<T>(data);
            graph->Append(newPoint);
        }
        for (int i = 0; i < points->GetLength(); i++) {
            bool addPoint = false;
            for (int j = 0; j < this->graph->GetLength(); j++) {
                // Если в графе есть вершина в которую мы хотим прийти
                if (this->graph->Get(j)->GetData() == points->Get(i).first) {
                    if (!this->oriented and IsNewPoint(graph->Get(j), newPoint, j)){
                        graph->Get(j)->AddPoint(newPoint, points->Get(i).second);
                    }
                    if (IsNewPoint(newPoint, graph->Get(j), j)) {
                        newPoint->AddPoint(graph->Get(j), points->Get(i).second);
                    }
                    addPoint = true;
                    break;
                }
            }
            // Если в графе нет вершины в которую мы можем попасть из этой точки
            if (!addPoint) {
                auto point = new Point<T>(points->Get(i).first);
                graph->Append(point);
                if (!this->oriented) {
                    point->AddPoint(newPoint, points->Get(i).second);
                }
                newPoint->AddPoint(point, points->Get(i).second);
            }

        }
    }

    Point<T>* GetPointByValue(T value) {
        for (int i = 0; i < graph->GetLength(); i++) {
            if (value == graph->Get(i)->GetData()) {
                return graph->Get(i);
            }
        }
        throw "No value in graph";
    }

    void Print() {
        for (int i = 0; i < this->graph->GetLength(); i++) {
            cout << this->graph->Get(i)->GetData() << ": ";
            for (int j = 0; j < this->graph->Get(i)->GetEdges()->GetLength(); j++) {
                cout << this->graph->Get(i)->GetEdges()->Get(j).p1->GetData();
                if (1) {
                    cout << "(" << this->graph->Get(i)->GetEdges()->Get(j).weight << ")";
                }
                cout << " ";
            }
            cout << endl;

        }
    }


public:
    vector<pair<T, int>> bfs(T start, T end=NULL) {
        vector<pair<T, int>> ans;
        map<Point<T>*, bool> history;
        map<Point<T>*, Point<T>*> preview;
        Point<T>* start_point = this->GetPointByValue(start);
        queue<pair<Point<T>*, int>> q;
        q.push(make_pair(start_point, 0));
        int levl = 0;
        history[start_point] = true;
        while (!q.empty()) {
            auto edges = q.front().first->GetEdges();
            for (int i = 0; i < edges->GetLength(); i++) {
                if (history[edges->Get(i).p1] == false) {
                    history[edges->Get(i).p1] = true;
                    preview[edges->Get(i).p1] = q.front().first;
                    q.push(make_pair(edges->Get(i).p1, q.front().second + 1));
                    ans.push_back(make_pair(edges->Get(i).p1->GetData(), q.front().second + 1));
                    cout << "point " << edges->Get(i).p1->GetData() << " depth: " << q.front().second + 1 << "\n";
                }
            }
            q.pop();
            levl++;
        }
        if (end != NULL) {
            auto end_point = this->GetPointByValue(end);
            vector<T> way = {end_point->GetData()};
            while (start_point != end_point) {
                way.push_back(preview[end_point]->GetData());
                end_point = preview[end_point];
            }
            reverse(way.begin(), way.end());
            int ind = 1;
            for (auto el : way) {
                ans.push_back(make_pair(el, ind));
                cout << el << ' ';
                ind++;
            }
            cout << endl;
        }
        return ans;
    }

private:
    Point<T>* GetMinNotVisitedPoint(map<Point<T>*, int>& labels, map<Point<T>*, bool>& visited) {
        int min = INT_MAX;
        Point<T>* point = NULL;
        for (auto p : labels) {
            if (p.second < min and !visited[p.first]) {
                min = p.second;
                point = p.first;
            }
        }
        return point;
    }
public:
    map<Point<T>*, int> Dijkstra(T start, T end=NULL) {
        map<Point<T>*, int> labels; // metki
        map<Point<T>*, bool> visited;
        for (int i = 0; i < this->graph->GetLength(); i++) {
            labels[this->graph->Get(i)] = INT_MAX;
            visited[this->graph->Get(i)] = false;
        }
        auto start_point = this->GetPointByValue(start);
        labels[start_point] = 0;
        auto cur_point = GetMinNotVisitedPoint(labels, visited);
        while (cur_point != NULL) {
            for (int i = 0; i < cur_point->GetEdges()->GetLength(); i++) {
                if (labels[cur_point] + cur_point->GetEdges()->Get(i).weight < labels[cur_point->GetEdges()->Get(i).p1]){
                    labels[cur_point->GetEdges()->Get(i).p1] = labels[cur_point] + cur_point->GetEdges()->Get(i).weight;
                }
            }
            visited[cur_point] = true;
            cur_point = GetMinNotVisitedPoint(labels, visited);
        }

        for (auto p : labels) {
            cout << p.first->GetData() << " " << p.second << endl;
        }
        return labels;
    }


public:
    // Неориентированный граф
    vector<pair<Point<T>*, int>> colorGraph()
    {
        map<Point<T>*, int> result;
        for (int u = 0; u < this->graph->GetLength(); u++)
        {
            set<int> assigned;
            if (!this->oriented){
                for (int i = 0; i < this->graph->Get(u)->GetEdges()->GetLength(); i++)
                {
                    if (result[this->graph->Get(u)->GetEdges()->Get(i).p1]) {
                        assigned.insert(result[this->graph->Get(u)->GetEdges()->Get(i).p1]);
                    }
                }
            }
            else{
                for (int j = 0; j < this->graph->GetLength(); j++) {
                    for (int k = 0; k < this->graph->Get(j)->GetEdges()->GetLength(); k++) {
                        if (this->graph->Get(j)->GetEdges()->Get(k).p1 == this->graph->Get(u) and result[this->graph->Get(j)->GetEdges()->Get(k).p2]) {
                            assigned.insert(result[this->graph->Get(j)->GetEdges()->Get(k).p2]);
                        }
                        if (this->graph->Get(j)->GetEdges()->Get(k).p2 == this->graph->Get(u) and result[this->graph->Get(j)->GetEdges()->Get(k).p1]) {
                            assigned.insert(result[this->graph->Get(j)->GetEdges()->Get(k).p1]);
                        }
                    }
                }
            }

            int color = 1;
            for (auto &c: assigned )
            {
                if (color != c) {
                    break;
                }
                color++;
            }
            result[this->graph->Get(u)] = color;
        }
        vector<pair<Point<T>*, int>> res;
        //string color[] = {"", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK","BLACK", "BROWN", "WHITE", "PURPLE", "VOILET"};
        for (int v = 0; v < this->graph->GetLength(); v++)
        {
            res.push_back(make_pair(this->graph->Get(v), result[this->graph->Get(v)]));
//            cout << "The color assigned to vertex " << this->graph->Get(v)->GetData() << " is "
//                 << color[result[this->graph->Get(v)]] << endl;
        }
        return res;
    }




};

template <typename T>
ostream& operator << (ostream &os, Edge<T>& d) {
    return os << "(" << d.p1->GetData() << ", " << d.p2->GetData() << ")" << "(" << d.weight << ")";
}

#endif //SEM2LAB3_GRAPH_H
