#ifndef SEM2LAB3_DRAWGRAPH_H
#define SEM2LAB3_DRAWGRAPH_H
#include <SFML/Graphics.hpp>
#include "graph.h"
#include "searchForConnectedComponents.h"
#include "minOstov.h"
#include <cmath>
#include "windows.h"

using namespace std;

template <typename T>
class DrawGraph {
private:
    Graph<T> gr;
    map<Point<T>*, pair<float, float>> points;
    map<Point<T>*, int> piked;
    map<Point<T>*, int> distanses;


    float r;
    int SIZE = 800;
    map<Point<T>*, int> colors;
    int countOfColors = 1;
    vector<sf::Color> colorVector;
    vector<Edge<T>*>* otherColorPoints;


public:
    DrawGraph(Graph<T> graph_, vector<pair<Point<T>*, int>>* colors_=NULL) {
        if (colors_ != NULL) {
//            this->colors = new map<Point<T>*, int>();
            for (int i = 0; i < colors_->size(); i++) {
                colors[colors_->at(i).first] = colors_->at(i).second;
            }
            GetCountOfColors();
        }
        gr = graph_;
        float angle = 2 * M_PI / gr.GetPoints()->GetLength();
        this->r = M_PI * (SIZE / 2) / (gr.GetPoints()->GetLength() * 4);
        for (int i = 0; i < gr.GetPoints()->GetLength(); i++) {
            float x = -r/2 + (SIZE / 2 - r) * sin(angle * i);
            float y = -r/2 + (SIZE / 2 - r) * cos(angle * i);
            points[gr.GetPoints()->Get(i)] = make_pair((SIZE - r) / 2 - x, (SIZE - r) / 2 - y);
        }
    }

    void Draw(vector<Edge<T>*>* otherColorPoints_ = NULL) {
        otherColorPoints = otherColorPoints_;
        sf::RenderWindow window(sf::VideoMode(SIZE + 500, SIZE), "SFML works!");

        while (window.isOpen())
        {sf::Event event;


            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == event.MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {

                    for (auto p : points) {
                        if (sqrt(pow(p.second.first - event.mouseButton.x, 2) + pow(p.second.second - event.mouseButton.y, 2)) < this->r) {
                            if (!piked[p.first]) {
                                piked[p.first] = 1;
                            }
                            else {
                                piked[p.first] = 0;
                            }
                        }
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 30 and event.mouseButton.y <= 60) {
                        auto colors_ = gr.colorGraph();
                        for (int i = 0; i < (&colors_)->size(); i++) {
                            colors[(&colors_)->at(i).first] = (&colors_)->at(i).second;
                        }
                        GetCountOfColors();
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 50 + 30 and event.mouseButton.y <= 50 + 60) {
                        vector<Edge<T>*> vec = FindMinOstov(&gr);
                        if (vec.size() != 0) {
                            vector<Edge<T>*>* v = new vector<Edge<T>*>();
                            for (int i = 0; i < vec.size(); i++) {
                                v->push_back(vec[i]);
                            }
                            otherColorPoints = v;
                        }
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 100 + 30 and event.mouseButton.y <= 100 + 60) {
                        auto ps = FindConComponents(&gr);
                        colors.clear();
                        for (auto p : ps) {
                            colors[gr.GetPointByValue(p.first)] = p.second;
                        }
                        GetCountOfColors();
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 150 + 30 and event.mouseButton.y <= 150 + 60) {
                        //bfs
                        for (auto j : piked) {
                            if (j.second == 1) {
                                colors.clear();
                                T start_point_data;
                                start_point_data = j.first->GetData();
                                colors[gr.GetPointByValue(start_point_data)] = 1;
                                vector<pair<T, int>> distanses_ = gr.bfs(start_point_data);
                                for (int i = 0; i < distanses_.size(); i++) {
                                    auto pp = gr.GetPointByValue(distanses_[i].first);
                                    this->distanses[pp] = distanses_[i].second;
                                    colors[pp] = distanses_[i].second + 3;
                                }
                                GetCountOfColors();
                                piked.clear();
                                continue;
                            }
                        }
                    }

                    if (event.mouseButton.x >= SIZE + 230 and event.mouseButton.x <= SIZE + 380 and event.mouseButton.y >= 150 + 30 and event.mouseButton.y <= 150 + 60) {
                        //bfs clear
                        distanses.clear();
                        piked.clear();
                        colors.clear();
                        if (otherColorPoints != NULL) {
                            otherColorPoints->clear();
                        }
                        countOfColors = 1;
                    }


                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 200 + 30 and event.mouseButton.y <= 200 + 60) {
                        //djecstra
                        for (auto j : piked) {
                            if (j.second == 1) {
                                colors.clear();
                                T start_point_data;
                                start_point_data = j.first->GetData();
                                map<Point<T>*, int> distanses_ = gr.Dijkstra(start_point_data);
                                for (auto p: distanses_) {
                                    auto pp = p.first;
                                    this->distanses[pp] = p.second;
                                }
                                piked.clear();
                                continue;
                            }
                        }
                    }

                    if (event.mouseButton.x >= SIZE + 230 and event.mouseButton.x <= SIZE + 380 and event.mouseButton.y >= 200 + 30 and event.mouseButton.y <= 200 + 60) {
                        //djekstra clear
                        distanses.clear();
                        piked.clear();
                        colors.clear();
                        countOfColors = 1;
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 250 + 30 and event.mouseButton.y <= 250 + 60) {
                        //djecstra
                        for (auto j : piked) {
                            if (j.second) {
                                points.erase(j.first);
                                gr.DeletePoint(j.first->GetData());
                            }

                        }
                        piked.clear();
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 300 + 30 and event.mouseButton.y <= 300 + 60) {
                        Point<T>* fp = NULL;
                        Point<T>* sp = NULL;
                        for (auto j : piked) {
                            if (j.second) {
                                if (fp == NULL) {
                                    fp = j.first;
                                }
                                else if (sp == NULL) {
                                    sp = j.first;
                                    break;
                                }
                            }
                        }
                        if (fp != NULL and sp != NULL) {
                            gr.DeleteEdge(fp->GetData(), sp->GetData());
                            gr.DeleteEdge(sp->GetData(), fp->GetData());
                        }
                        piked.clear();
                    }




                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 350 + 30 and event.mouseButton.y <= 350 + 60) {
                        Sequence<pair<T, double>>* points_ = new ArraySequence<pair<T, double>>();
                        for (auto j : piked) {
                            if (j.second) {
                                if (gr.weight) {
                                    points_->Append(make_pair(j.first->GetData(), 1 + rand() % 20));
                                }
                                else {
                                    points_->Append(make_pair(j.first->GetData(), -1));
                                }
                            }
                        }
                        int m = 1;
                        for (int i = 0; i < gr.GetPoints()->GetLength(); i++) {
                            if (gr.GetPoints()->Get(i)->GetData() > m) {
                                m = gr.GetPoints()->Get(i)->GetData();
                            }
                        }
                        gr.AddNewPointWithWeight(m + 1, points_);
                        piked.clear();
                        points.clear();

                        float angle = 2 * M_PI / gr.GetPoints()->GetLength();
                        this->r = M_PI * (SIZE / 2) / (gr.GetPoints()->GetLength() * 4);
                        for (int i = 0; i < gr.GetPoints()->GetLength(); i++) {
                            float x = -r/2 + (SIZE / 2 - r) * sin(angle * i);
                            float y = -r/2 + (SIZE / 2 - r) * cos(angle * i);
                            points[gr.GetPoints()->Get(i)] = make_pair((SIZE - r) / 2 - x, (SIZE - r) / 2 - y);
                        }
                    }

                    if (event.mouseButton.x >= SIZE + 50 and event.mouseButton.x <= SIZE + 200 and event.mouseButton.y >= 400 + 30 and event.mouseButton.y <= 400 + 60) {

                        Point<T>* fp = NULL;
                        Point<T>* sp = NULL;
                        for (auto j : piked) {
                            if (j.second) {
                                if (fp == NULL) {
                                    fp = j.first;
                                }
                                else if (sp == NULL) {
                                    sp = j.first;
                                    break;
                                }
                            }
                        }
                        if (fp != NULL and sp != NULL) {
                            gr.AddNewAdge(fp->GetData(), sp->GetData());
                            gr.AddNewAdge(sp->GetData(), fp->GetData());
                        }
                        piked.clear();
                    }
                }





            }
            window.clear();
            for (auto p : points) {
                this->Draw_point(window, p.second.first, p.second.second, p.first);
                if (distanses[p.first] > 0 and distanses[p.first] < INT_MAX){
                    DrawText(window, p.second.first, p.second.second, to_string(p.first->GetData()) + " " + to_string(distanses[p.first]));
                }
                else {
                    DrawText(window, p.second.first, p.second.second, to_string(p.first->GetData()));
                }
            }
            map<pair<Point<T>*, Point<T>*>, bool> hist;
            for (auto p : points) {
                for (int i = 0; i < p.first->GetEdges()->GetLength(); i++) {
                    if (hist[make_pair(p.first->GetEdges()->Get(i).p1, p.first)]) {
                        DrawArrow(window, p.second.first, p.second.second, points[p.first->GetEdges()->Get(i).p1].first, points[p.first->GetEdges()->Get(i).p1].second, &p.first->GetEdges()->Get(i), p.first->GetEdges()->Get(i).p1, p.first->GetEdges()->Get(i).weight, false);
                        hist[make_pair(p.first, p.first->GetEdges()->Get(i).p1)] = true;
                    } else {
                        DrawArrow(window, p.second.first, p.second.second, points[p.first->GetEdges()->Get(i).p1].first, points[p.first->GetEdges()->Get(i).p1].second, &p.first->GetEdges()->Get(i), p.first->GetEdges()->Get(i).p1, p.first->GetEdges()->Get(i).weight);
                        hist[make_pair(p.first, p.first->GetEdges()->Get(i).p1)] = true;
                    }
                }
            }
            DrawMenu(window);
            window.display();
        }
    }

private:


    void DrawMenu(sf::RenderWindow& window) {
        sf::RectangleShape rectangle1(sf::Vector2f(120, 50));
        rectangle1.setSize(sf::Vector2f(150, 30));
        rectangle1.setPosition(SIZE + 50, 30);
        window.draw(rectangle1);
        DrawTextB(window, SIZE + 55, 28, "coloring", 25);

        sf::RectangleShape rectangle2(sf::Vector2f(120, 50));
        rectangle2.setSize(sf::Vector2f(150, 30));
        rectangle2.setPosition(SIZE + 50, 50 + 30);
        window.draw(rectangle2);
        DrawTextB(window, SIZE + 55, 50 + 28, "min ostov", 25);

        sf::RectangleShape rectangle3(sf::Vector2f(120, 50));
        rectangle3.setSize(sf::Vector2f(150, 30));
        rectangle3.setPosition(SIZE + 50, 100 + 30);
        window.draw(rectangle3);
        DrawTextB(window, SIZE + 55, 100 + 28, "con comps", 25);

        sf::RectangleShape rectangle4(sf::Vector2f(120, 50));
        rectangle4.setSize(sf::Vector2f(150, 30));
        rectangle4.setPosition(SIZE + 50, 150 + 30);
        window.draw(rectangle4);
        DrawTextB(window, SIZE + 55, 150 + 28, "bfs", 25);

        sf::RectangleShape rectangle4Clear(sf::Vector2f(120, 50));
        rectangle4Clear.setSize(sf::Vector2f(150, 30));
        rectangle4Clear.setPosition(SIZE + 230, 150 + 30);
        window.draw(rectangle4Clear);
        DrawTextB(window, SIZE + 235, 150 + 28, "CLEAR", 25);

        sf::RectangleShape rectangle5(sf::Vector2f(120, 50));
        rectangle5.setSize(sf::Vector2f(150, 30));
        rectangle5.setPosition(SIZE + 50, 200 + 30);
        window.draw(rectangle5);
        DrawTextB(window, SIZE + 55, 200 + 28, "Dijkstra", 25);

        sf::RectangleShape rectangle5Clear(sf::Vector2f(120, 50));
        rectangle5Clear.setSize(sf::Vector2f(150, 30));
        rectangle5Clear.setPosition(SIZE + 230, 200 + 30);
        window.draw(rectangle5Clear);
        DrawTextB(window, SIZE + 235, 200 + 28, "CLEAR", 25);

        sf::RectangleShape rectangle6(sf::Vector2f(120, 50));
        rectangle6.setSize(sf::Vector2f(150, 30));
        rectangle6.setPosition(SIZE + 50, 250 + 30);
        window.draw(rectangle6);
        DrawTextB(window, SIZE + 55, 250 + 28, "Del Sel Points", 25);

        sf::RectangleShape rectangle7(sf::Vector2f(120, 50));
        rectangle7.setSize(sf::Vector2f(150, 30));
        rectangle7.setPosition(SIZE + 50, 300 + 30);
        window.draw(rectangle7);
        DrawTextB(window, SIZE + 55, 300 + 28, "Del edge", 25);

        sf::RectangleShape rectangle8(sf::Vector2f(120, 50));
        rectangle8.setSize(sf::Vector2f(150, 30));
        rectangle8.setPosition(SIZE + 50, 350 + 30);
        window.draw(rectangle8);
        DrawTextB(window, SIZE + 55, 350 + 28, "Add point", 25);

        sf::RectangleShape rectangle9(sf::Vector2f(120, 50));
        rectangle9.setSize(sf::Vector2f(150, 30));
        rectangle9.setPosition(SIZE + 50, 400 + 30);
        window.draw(rectangle9);
        DrawTextB(window, SIZE + 55, 400 + 28, "Add Edge", 25);


    }

    void GetCountOfColors() {
        for (auto c : this->colors) {
            if (c.second > this->countOfColors) {
                this->countOfColors = c.second;
            }
        }
        for (int i = 0; i < this->countOfColors; i++) {
            colorVector.push_back(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }
    }

    void Draw_point(sf::RenderWindow& window, float x, float y, Point<T>* p) {
        sf::CircleShape shape(r);
        shape.setOrigin((float)r, (float)r);
        shape.setPosition(x, y);
        if (this->countOfColors > 1) {
            shape.setFillColor(colorVector[colors[p] - 1]);
        }
        else {
            shape.setFillColor(sf::Color(255, 255, 255));
        }

        if (piked[p]) {
            shape.setFillColor(sf::Color(250, 9, 197));
        }

        window.draw(shape);
    }

    void DrawArrow(sf::RenderWindow& window, float x1, float y1, float x2, float y2, Edge<T>* edge, Point<T>* dest, double length, bool drawEnd=true) {
        sf::Color color = sf::Color::Red;
        if (otherColorPoints != NULL) {
            for (int i = 0; i < otherColorPoints->size(); i++) {
                if ((otherColorPoints->at(i)->p1 == edge->p1 and otherColorPoints->at(i)->p2 == edge->p2) or (otherColorPoints->at(i)->p1 == edge->p2 and otherColorPoints->at(i)->p2 == edge->p1)){
                    color = sf::Color(255, 255, 255);
                }
            }
        }

//
//        if (otherColorPoints != NULL and find(this->otherColorPoints->begin(), this->otherColorPoints->end(), edge) != this->otherColorPoints->end()) {
//            color = sf::Color(255, 255, 255);
//        }

        this->DrawWeight(window, x1 + (x2 - x1) / 4, y1 + (y2 - y1) / 4,length);
        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(x1, y1), color),
                        sf::Vertex(sf::Vector2f(x2, y2), color)
                };
        window.draw(line, 2, sf::Lines);
        double angle = asin((y2 - y1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))) * (180.0/3.141592653589793238463);
        sf::Vector2f pp((x2 - x1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)), (y2 - y1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        if (drawEnd) {
            if (countOfColors == 1){
                sf::Vertex line2[] =
                        {
                                sf::Vertex(sf::Vector2f(x2 - pp.x * this->r, y2 - pp.y * this->r), sf::Color(255, 255, 255)),
                                sf::Vertex(sf::Vector2f(x2, y2), sf::Color(255, 255, 255))
                        };
                window.draw(line2, 2, sf::Lines);

            }else {
                sf::Vertex line2[] =
                        {
                                sf::Vertex(sf::Vector2f(x2 - pp.x * this->r, y2 - pp.y * this->r), this->colorVector[this->colors[dest] - 1]),
                                sf::Vertex(sf::Vector2f(x2, y2), this->colorVector[this->colors[dest] - 1])
                        };
                window.draw(line2, 2, sf::Lines);

            }

        }
    }

    void DrawText(sf::RenderWindow& window, float x, float y, string data) {
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\user\\CLionProjects\\lizard\\ofont.ru_Departura.ttf"))
        {
            cout << "cant found\n";
        }
        sf::Text text;
        text.setFont(font); // font is a sf::Font
        text.setString(data);
        text.setPosition(x - 3 * r / 4, y - r / 4);
        text.setCharacterSize(this->r / 2); // in pixels, not points!
        text.setFillColor(sf::Color::Red);
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        window.draw(text);
    }

    void DrawTextB(sf::RenderWindow& window, float x, float y, string data, int size) {
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\user\\CLionProjects\\lizard\\ofont.ru_Departura.ttf"))
        {
            cout << "cant found\n";
        }
        sf::Text text;
        text.setFont(font); // font is a sf::Font
        text.setString(data);
        text.setPosition(x, y);
        text.setCharacterSize(size); // in pixels, not points!
        text.setFillColor(sf::Color::Red);
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        window.draw(text);
    }

    void DrawWeight(sf::RenderWindow& window, float x, float y, double weight) {
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\user\\CLionProjects\\lizard\\ofont.ru_Departura.ttf"))
        {
            cout << "cant found\n";
        }
        sf::Text text;
        text.setFont(font); // font is a sf::Font
        if (weight == int(weight)){
            text.setString( to_string((int)weight));
        }
        else {
            text.setString( to_string(weight).substr(0, to_string(weight).find('.') + 3));
        }
        text.setPosition(x, y);
        text.setCharacterSize(10); // in pixels, not points!
        text.setFillColor(sf::Color::White);
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        window.draw(text);
    }
};

#endif //SEM2LAB3_DRAWGRAPH_H
