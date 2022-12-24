#include <iostream>

#include "graph.h"
#include "DrawGraph.h"
#include "ArraySequence.h"
#include "Sequence.h"
#include "searchForConnectedComponents.h"
#include "travllingSalesmanProblem.h"
#include "minOstov.h"

int cmpInt(int a, int b){
    return a == b;
}

template <typename T>
void init(Graph<T>* graph, int weighed) {
    while (true) {
        cout << "0 - exit\n";
        cout << "1 - draw graph\n";
        cout << "2 - print graph\n";
        cout << "3 - bfs\n";
        cout << "4 - Dijkstra\n";
        cout << "5 - ColorING graph\n";
        cout << "6 - Find min ostov\n";
        cout << "7 - Search Connected Components (not oriented)\n";
        cout << "8 - Add point\n";
        cout << "9 - Delete point\n";
        cout << "10 - Delete edge\n";
        cout << "11 - Add edge\n";
        int action;
        cin >> action;
        if (action == 0) {
            exit(0);
        }
        if (action == 1) {
            DrawGraph<int>* dr = new DrawGraph<int>(*graph);
            dr->Draw();
        }
        if (action == 2) {
            graph->Print();
        }
        if (action == 3) {
            int start_point;
            cout << "start point:\n";
            cin >> start_point;
            graph->bfs(start_point);
        }
        if (action == 4) {
            int start_point;
            cout << "start point:\n";
            cin >> start_point;
            graph->Dijkstra(start_point);
        }
        if (action == 5) {
            auto res = graph->colorGraph();
            DrawGraph<int>* dr = new DrawGraph<int>(*graph, &res);
            dr->Draw();
        }
        if (action == 6) {
            auto vec = FindMinOstov(graph);
            if (vec.size() == 0) {
                continue;
            }
            for (int i = 0; i < vec.size(); i++)
            {
                cout << vec[i]->p1->GetData() << " "  << vec[i]->p2->GetData() << "| ";
            }
            auto res = graph->colorGraph();
            DrawGraph<int>* dr_ost = new DrawGraph<int>(*graph, &res);
            dr_ost->Draw(&vec);
        }
        if (action == 7) {
            FindConComponents(graph);
        }
        if (action == 8) {
            cout << "Print point: ";
            int data; cin >> data;
            cout << "Count of neighbors: ";
            int n; cin >> n;
            if (weighed == 2) {
                Sequence<int>* sec = new ArraySequence<int>();
                for (int i = 0; i < n; i++) {
                    int neigh; cin >> neigh;
                    sec->Append(neigh);
                }
                graph->AddNewPoint(data, sec);
            }
            if (weighed == 1) {
                Sequence<pair<int, double>>* sec = new ArraySequence<pair<int, double>>();
                for (int i = 0; i < n; i++) {
                    int neigh; cin >> neigh;
                    int weight; cin >> weight;
                    sec->Append(make_pair(neigh, weight));
                }
                graph->AddNewPointWithWeight(data, sec);
            }

        }
        if (action == 9) {
            cout << "Point: ";
            int point; cin >> point;
            graph->DeletePoint(point);
        }
        if (action == 10) {
            cout << "from/to: ";
            int point1;
            int point2; cin >> point1 >> point2;
            graph->DeleteEdge(point1, point2);
        }
        if (action == 11) {
            cout << "from/to/weight(-1 if not): ";
            int point1;
            int point2; cin >> point1 >> point2;
            int weight; cin >> weight;
            graph->AddNewAdge(point1, point2, weight);
        }


    }

}

template <typename T>
void travel() {
    Sequence<pair<int, Sequence<pair<int, double>>*>>* gr = new ArraySequence<pair<int, Sequence<pair<int, double>>*>>();
    cout << "count of points!:\n";
    int n;
    cin >> n;
    map<pair<int, int>, int> weighs;
    for (int i = 0; i < n; i++) {
        auto neighbors = new ArraySequence<pair<int, double>>();
        map<int, bool> genereted;
        for (int j = 0; j < n; j++) {
            int neighbor = 1 + rand() % (n);
            if (neighbor != i + 1 and !genereted[neighbor]) {
                if (weighs[make_pair(neighbor, i + 1)] != 0){
                    neighbors->Append(make_pair(neighbor, weighs[make_pair(neighbor, i + 1)]));
                }
                else {
                    int w = 1 + rand() % 20;
                    neighbors->Append(make_pair(neighbor, w));
                    weighs[make_pair(i + 1, neighbor)] = w;
                }
                genereted[neighbor] = true;
            }
        }
        gr->Append(make_pair(i + 1, neighbors));
    }

    Graph<T>* graph = new Graph<T>(gr, false);
    cout << "pyt: " << TravllingSalesmanProblem(graph) << endl;
    graph->Print();
    DrawGraph<int>* dr = new DrawGraph<int>(*graph);
    dr->Draw();
    exit(0);
}

int main() {
    srand(time(NULL));
//    Sequence<pair<int, Sequence<pair<int, double>>*>>* gr = new ArraySequence<pair<int, Sequence<pair<int, double>>*>>();
//    auto neighbors1 = new ArraySequence<pair<int, double>>();
//    neighbors1->Append(make_pair(2, 5));
//    neighbors1->Append(make_pair(3, 4));
//    neighbors1->Append(make_pair(4, 10.5));
//    neighbors1->Append(make_pair(5, 1));
//    gr->Append(make_pair(1, neighbors1));
//
//    auto neighbors2 = new ArraySequence<pair<int, double>>();
//    neighbors2->Append(make_pair(3, 2));
//    neighbors2->Append(make_pair(4, 9));
//    neighbors2->Append(make_pair(1, 5));
//    neighbors2->Append(make_pair(5, 1));
//    gr->Append(make_pair(2, neighbors2));
//
//    auto neighbors3 = new ArraySequence<pair<int, double>>();
//    neighbors3->Append(make_pair(2, 2));
//    neighbors3->Append(make_pair(1, 4));
//    neighbors3->Append(make_pair(4, 6.5));
//    neighbors3->Append(make_pair(5, 1));
//    gr->Append(make_pair(3, neighbors3));
//
//    auto neighbors4 = new ArraySequence<pair<int, double>>();
//    neighbors4->Append(make_pair(1, 10.5));
//    neighbors4->Append(make_pair(2, 9));
//    neighbors4->Append(make_pair(3, 6.5));
//    neighbors4->Append(make_pair(5, 1));
//    gr->Append(make_pair(4, neighbors4));
//
//    auto neighbors5 = new ArraySequence<pair<int, double>>();
//    neighbors5->Append(make_pair(1, 1));
//    neighbors5->Append(make_pair(2, 1));
//    neighbors5->Append(make_pair(3, 1));
//    neighbors5->Append(make_pair(4, 1));
//    gr->Append(make_pair(5, neighbors4));


//    Sequence<pair<int, Sequence<pair<int, double>>*>>* gr = new ArraySequence<pair<int, Sequence<pair<int, double>>*>>();
//    auto neighbors1 = new ArraySequence<pair<int, double>>();
//    neighbors1->Append(make_pair(2, 5));
//    neighbors1->Append(make_pair(3, 4));
//    neighbors1->Append(make_pair(4, 10));
//    gr->Append(make_pair(1, neighbors1));
//
//    auto neighbors2 = new ArraySequence<pair<int, double>>();
//    neighbors2->Append(make_pair(6, 8));
//    neighbors2->Append(make_pair(3, 2));
//    neighbors2->Append(make_pair(4, 9));
//    gr->Append(make_pair(2, neighbors2));
//
//    auto neighbors3 = new ArraySequence<pair<int, double>>();
//    neighbors3->Append(make_pair(2, 3));
//    neighbors3->Append(make_pair(1, 11));
//    neighbors3->Append(make_pair(4, 6));
//    gr->Append(make_pair(3, neighbors3));
//
//    auto neighbors4 = new ArraySequence<pair<int, double>>();
//    neighbors4->Append(make_pair(5, 5));
//    neighbors4->Append(make_pair(6, 122));
//    gr->Append(make_pair(4, neighbors4));
//
//    auto neighbors6 = new ArraySequence<pair<int, double>>();
//    neighbors6->Append(make_pair(6, 4));
//    gr->Append(make_pair(5, neighbors6));


//    Sequence<pair<int, Sequence<int>*>>* gr = new ArraySequence<pair<int, Sequence<int>*>>();
//    auto neighbors1 = new ArraySequence<int>();
//    neighbors1->Append(2);
//    neighbors1->Append(3);
//    neighbors1->Append(4);
//    gr->Append(make_pair(1, neighbors1));
//
//    auto neighbors2 = new ArraySequence<int>();
//    neighbors2->Append(6);
//    neighbors2->Append(3);
//    neighbors2->Append(4);
//    gr->Append(make_pair(2, neighbors2));
//
//    auto neighbors3 = new ArraySequence<int>();
//    neighbors3->Append(2);
//    neighbors3->Append(1);
//    neighbors3->Append(4);
//    gr->Append(make_pair(3, neighbors3));
//
//    auto neighbors4 = new ArraySequence<int>();
//    neighbors4->Append(5);
//    neighbors4->Append(6);
//    gr->Append(make_pair(4, neighbors4));
//
//    auto neighbors6 = new ArraySequence<int>();
//    neighbors6->Append(6);
//    gr->Append(make_pair(5, neighbors6));



//    Sequence<pair<int, Sequence<int>*>>* gr = new ArraySequence<pair<int, Sequence<int>*>>();
//    auto neighbors1 = new ArraySequence<int>();
//    neighbors1->Append(2);
//    neighbors1->Append(3);
//    neighbors1->Append(4);
//    gr->Append(make_pair(1, neighbors1));
//
//    auto neighbors2 = new ArraySequence<int>();
//    neighbors2->Append(6);
//    neighbors2->Append(3);
//    neighbors2->Append(4);
//    gr->Append(make_pair(2, neighbors2));
//
//    auto neighbors3 = new ArraySequence<int>();
//    neighbors3->Append(2);
//    neighbors3->Append(1);
//    neighbors3->Append(4);
//    gr->Append(make_pair(3, neighbors3));
//
//    auto neighbors4 = new ArraySequence<int>();
//    neighbors4->Append(5);
//    neighbors4->Append(6);
//    gr->Append(make_pair(4, neighbors4));
//
//    auto neighbors6 = new ArraySequence<int>();
//    neighbors6->Append(6);
//    gr->Append(make_pair(5, neighbors6));
//
//
//    auto neighbors7 = new ArraySequence<int>();
//    gr->Append(make_pair(7, neighbors7));
//
//
//    auto neighbors8 = new ArraySequence<int>();
//    neighbors8->Append(9);
//    gr->Append(make_pair(8, neighbors8));
//
//    auto neighbors9 = new ArraySequence<int>();
//    neighbors9->Append(10);
//    gr->Append(make_pair(9, neighbors9));
//
//    auto neighbors10 = new ArraySequence<int>();
//    gr->Append(make_pair(10, neighbors10));



//    Graph<int>* graph = new Graph<int>(gr, false);
//    graph->Print();
//    graph->Dijkstra(1, 4);
//    auto res = graph->colorGraph();
//    DrawGraph<int>* dr = new DrawGraph<int>(*graph, &res);
//    dr->Draw();
//    cout << "pyt: " << TravllingSalesmanProblem(graph) << endl;
//    auto vec = FindMinOstov(graph);
//    for (int i = 0; i < vec.size(); i++)
//    {
//        cout << vec[i]->p1->GetData() << " "  << vec[i]->p2->GetData() << "| ";
//    }
//    DrawGraph<int>* dr_ost = new DrawGraph<int>(*graph, &res);
//    dr_ost->Draw(&vec);
//    cout << endl;

//    FindConComponents(graph);
//    auto neighbors5 = new ArraySequence<int>();
//    neighbors5->Append(5);
//    graph->AddNewPoint(3, neighbors5);
//    graph->Print();
//
//    graph->bfs(1, 6);





    cout << "1 - directed graph\n";
    cout << "2 - no directed graph\n";
    cout << "3 - Travelling Salesman Problem\n";
    int orientation;
    cin >> orientation;

    if (orientation == 3) {
        travel<int>();
    }

    cout << "weighed?\n1 - da\n2 - net\n";
    int weighed;
    cin >> weighed;

    cout << "1 - generate random graph\n";
    cout << "2 - input graph\n";
    int inType;
    cin >> inType;
    cout << "count of points: ";
    int n;
    cin >> n;
    if (weighed == 2){
        Sequence<pair<int, Sequence<int>*>>* gr = new ArraySequence<pair<int, Sequence<int>*>>();
        for (int i = 0; i < n; i++) {
            if (inType == 2){
                cout << "point, count of neighbors and neighbors(point, count, data): ";
                int p;
                cin >> p;
                int nn;
                cin >> nn;
                auto neighbors = new ArraySequence<int>();
                for (int j = 0; j < nn; j++) {
                    int neighbor;
                    cin >> neighbor;
                    neighbors->Append(neighbor);
                }
                gr->Append(make_pair(p, neighbors));
            }
            else {
                int nn = rand() % (n - 1);
                auto neighbors = new ArraySequence<int>();
                map<int, bool> genereted;
                for (int j = 0; j < nn; j++) {
                    int neighbor = 1 + rand() % (n);
                    if (neighbor != i + 1 and !genereted[neighbor]){
                        neighbors->Append(neighbor);
                        genereted[neighbor] = true;
                    }
                }
                gr->Append(make_pair(i + 1, neighbors));
            }

        }
        bool o = false;
        if (orientation == 1){
            o = true;
        }
        Graph<int>* graph = new Graph<int>(gr, o);
        init(graph, weighed);

    }
    else {
        Sequence<pair<int, Sequence<pair<int, double>>*>>* gr = new ArraySequence<pair<int, Sequence<pair<int, double>>*>>();
        map<pair<int, int>, int> weighs;

        for (int i = 0; i < n; i++) {
            if (inType == 2){
                cout << "point, count of neighbors and neighbors(point, count, data(point, weight)): ";
                int p;
                cin >> p;
                int nn;
                cin >> nn;
                auto neighbors = new ArraySequence<pair<int, double>>();
                for (int j = 0; j < nn; j++) {
                    int neighbor, weight;
                    cin >> neighbor >> weight;
                    neighbors->Append(make_pair(neighbor, weight));
                }
                gr->Append(make_pair(p, neighbors));
            }
            else {
                if (orientation == 1) {
                    int nn = rand() % (n - 1);
                    auto neighbors = new ArraySequence<pair<int, double>>();
                    map<int, bool> genereted;
                    for (int j = 0; j < nn; j++) {
                        int neighbor = 1 + rand() % (n);
                        if (neighbor != i + 1 and !genereted[neighbor]){
                            neighbors->Append(make_pair(neighbor, 1 + rand() % 20));
                            genereted[neighbor] = true;
                        }
                    }
                    gr->Append(make_pair(i + 1, neighbors));
                }
                else {
                    int nn = rand() % (n - 1);
                    auto neighbors = new ArraySequence<pair<int, double>>();
                    map<int, bool> genereted;
                    for (int j = 0; j < nn; j++) {
                        int neighbor = 1 + rand() % (n);
                        if (neighbor != i + 1 and !genereted[neighbor]){
                            if (weighs[make_pair(neighbor, i + 1)] != 0){
                                neighbors->Append(make_pair(neighbor, weighs[make_pair(neighbor, i + 1)]));
                            }
                            else {
                                int w = 1 + rand() % 20;
                                neighbors->Append(make_pair(neighbor, w));
                                weighs[make_pair(i + 1, neighbor)] = w;
                            }
//                            neighbors->Append(make_pair(neighbor, 1 + rand() % 20));
//                            genereted[neighbor] = true;
                        }
                    }
                    gr->Append(make_pair(i + 1, neighbors));
                }

            }

        }
        bool o = false;
        if (orientation == 1){
            o = true;
        }
        Graph<int>* graph = new Graph<int>(gr, o);
        init(graph, weighed);
    }




    return 0;
}
