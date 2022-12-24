#pragma once
#include <iostream>
//
// Created by user on 11.04.2022.
//


using namespace std;


#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

template <class T> class Node
{
    T field;
    class Node *ptr;
    template<class U> friend class LinkedList;
};
template <class T> class LinkedList
{
    Node<T> *head;    // Корень списка
    int count = 0; // Количество узлов списка
    Node<T>* Prev(Node<T>* node) // Переход к предыдущему узлу
    {
        if (isEmpty()) return NULL;
        if (node == head) return NULL;
        Node<T> *p = head;
        while (p->ptr != node)
            p = p->ptr;
        return p;
    }

    Node<T>* GetNodeByIndex(int index){
        if (index >= count){
            return NULL;
        }
        Node<T>* ptr = head;
        while (index > 0){
            ptr = Next(ptr);
            index--;
        }
        return ptr;
    }
public:
    LinkedList() { head = NULL; } // Инициализация списка

    LinkedList(const LinkedList<T>& list){
        head = NULL;
        Node<T>* ptr = list.head;
        Node<T>* new_ptr = NULL;
        for (int i = 0; i < list.count; i++){
            new_ptr = Add(ptr->field, new_ptr);
            ptr = Next(ptr);
            count++;
        }
    }

    int getCount() { return count; } // Получение количества узлов списка
    bool isEmpty() { return head == NULL; }  // Проверка, пуст ли список
    T& getValue(Node<T>* p) { return p->field; } // Получение значения узла списка
    T& getValue(int p) { return GetNodeByIndex(p)->field; } // Получение значения узла списка
    void setValue(Node<T> *p, T val) { p->field = val; } // Установка значения узла списка
    void setValue(int p, T val) { GetNodeByIndex(p)->field = val; } // Установка значения узла списка
    //void InsertAt(int item, int index);
    Node<T>* getFirst() { return head; } // Получение корневого узла списка
    //Node<T>* getLast();      // Получение последнего узла списка
    //void Clear();        // Очистка списка
    //Node<T>* Next(Node<T> *);      // Переход к следующему узлу
    //Node<T>* Add(int, Node<T>*);    // Добавление узла списка
    //Node<T>* Delete(int);    // Удаление узла списка
    //void Print();        // Вывод значений узлов списка
    //void Swap(int, int);  // Взаимообмен двух узлов
    //LinkedList<T> getSublist(int, int);  // ПодЛист)

    void InsertAt(T item, int index){
        if (index == 0){
            Add(item, NULL);
        } else{
            Add(item, GetNodeByIndex(index - 1));
        }
    }

    Node<T>* Add(T num, Node<T>* node = NULL)
    {
        //Node<T> *elem = new Node<T>();
        Node<T> *elem = (Node<T>*) malloc(sizeof(Node<T>));

        elem->field = num;
        count++;
        if (node == NULL) // Добавление нового корня
        {
            if (head == NULL) {
                elem->ptr = NULL;
                head = elem;
            }
            else {
                elem->ptr = head;
                head = elem;
            }
            return elem;
        }
        elem->ptr = node->ptr; // Добавление узла после текущего
        node->ptr = elem;
        return elem;
    }

    Node<T>* Delete(int index)
    {

        Node<T>* node = GetNodeByIndex(index);
        if (node == NULL) { return NULL; } // В списке нет узлов
        count--;
        if (node == head)  // Удаление корневого узла
        {
            head = node->ptr;
            delete node;
            return head;
        }
        Node<T>* prev = Prev(node); // Удаление промежуточного узла
        prev->ptr = node->ptr;
        delete node;
        return prev;
    }

    Node<T>* Next(Node<T>* node)
    {
        if (isEmpty()) return NULL;
        return node->ptr;
    }

    Node<T>* getLast()
    {
        Node<T>* p = head;
        while (Next(p) != NULL)
            p = Next(p);
        return p;
    }

    LinkedList<T>* Concatinate(const LinkedList<T> &list) {
        LinkedList<T>* newlist = new LinkedList<T>();
        Node<T> *pointer = newlist->head;
        Node<T> *hedpoint = this->head;


        while (hedpoint != NULL){
            //cout << pointer << endl;
            pointer = newlist->Add(hedpoint->field, pointer);
            hedpoint = hedpoint->ptr;
        }

        Node<T> *listPointer = list.head;
        while (listPointer){
            pointer = Add(listPointer->field, pointer);
            listPointer = listPointer->ptr;
        }
        return newlist;
    }

    LinkedList<T>* getSublist(int startIndex, int endIndex){
        if(startIndex < 0 || startIndex >= count){
            throw "wrong indexes";
            //cout << "out of range\n";
        }
        if(endIndex < 0 || endIndex > count){
            throw "wrong indexes";
            //cout << "out of range\n";
        }
        if(startIndex > endIndex){
            throw logic_error("end must be not less than start");
            cout << "end must be not less than start\n";
        }
        LinkedList<T>* newList = new LinkedList<T>();
        Node<T>* ptr = newList->head;
        Node<T>* start = GetNodeByIndex(startIndex);
        for (int i = startIndex; i < endIndex; i++){
            ptr = newList->Add(start->field, ptr);
            start = start->ptr;
        }
        return newList;
    }

    void Clear()
    {
        class Node<T> *p = head;
        if (p == NULL) return;
        do {
            Node<T> *d = p;
            p = Next(p);
            delete d;
        } while (p != NULL);
        count = 0;
        head = NULL;
    }

    void Print()
    {
        if (isEmpty()) { cout << "Array is empty" << endl; return; }
        Node<T> *p = head;
        do {
            cout << getValue(p) << " ";
            p = Next(p);
        } while (p != NULL);
        cout << endl;
    }

    void Swap(int first, int second)
    {
        Node<T>* node1 = GetNodeByIndex(first);
        Node<T>* node2 = GetNodeByIndex(second);
        if (node1 == NULL || node2 == NULL) return; // не допускаем обмен с несуществующим узлом
        if (node1 == node2) return; // если один узел указан дважды, менять ничего не надо
        if (node2->ptr == node1) // если node2 находится перед node1, меняем их местами
        {
            Node<T> *p = node1;
            node1 = node2;
            node2 = p;
        }
        Node<T> *prev1 = Prev(node1);
        Node<T> *prev2 = Prev(node2);
        Node<T> *next1 = Next(node1);
        Node<T> *next2 = Next(node2);
        if (next1 == node2) // обмен соседних узлов
        {
            if (prev1 != NULL)
                prev1->ptr = node2;
            else
                head = node2;
            node2->ptr = node1;
            node1->ptr = next2;
            return;
        }
        if (prev1 != NULL)  // обмен отстоящих узлов
            prev1->ptr = node2;
        else
            head = node2;
        if (prev2 != NULL)
            prev2->ptr = node1;
        else
            head = node1;
        node2->ptr = next1;
        node1->ptr = next2;
    }
};


#endif