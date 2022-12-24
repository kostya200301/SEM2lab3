#pragma once
#include <iostream>
#include "Sequence.h"
//
// Created by user on 11.04.2022.
//


using namespace std;


#ifndef LAB2_LINKEDLISTSEQUENCE_H
#define LAB2_LINKEDLISTSEQUENCE_H

template <class T> class LinkedListSequence : public Sequence<T>{
private:
    LinkedList<T>* buffer;
    size_t count;
public:
    LinkedListSequence (T* items, int Count){
        buffer = LinkedList<T>(items, count);
        count = Count;
    }
    LinkedListSequence(){
        buffer = new LinkedList<T>();
        count = 0; //Определиться с размерами
    }

    LinkedListSequence (LinkedList <T> & list){
        buffer = new LinkedList<T>(list);
        count = list.getCount();
    }

    virtual T GetFirst() override{
        return buffer->getValue(0);
    }

    virtual T GetLast() override{
        return buffer->getValue(count - 1);
    }

    virtual T& Get(size_t index) override{
        return buffer->getValue(index);
    }

    virtual void Set(const T& element, int index) override{
        return buffer->setValue(index, element);
    }



    //Sequence<T>* GetSubsequence(int startIndex, int endIndex);

    virtual int GetLength() const override{
        return count;
    }

    virtual void Append(const T &item) override{
        buffer->InsertAt(item, count++);
    }

    virtual void Prepend(const T &item) override{
        buffer->InsertAt(item, 0);
        count++;
    }

    virtual void InsertAt(const T &item, int index) override{
        buffer->InsertAt(item, index);
        count++;

    }

    virtual void Delete(int index) override{
        if (index >= this->count || index < 0){
            throw "Incorrect index";
        }
        this->buffer->Delete(index);
        this->count--;

    }

    virtual void PrintArray() override{
        for (int i = 0; i < count; i++){
            cout << buffer->getValue(i) << " ";
        }
        cout << endl;
    }


    virtual LinkedListSequence<T>* Concatenate(Sequence<T>& sequence) override {
        LinkedListSequence<T> *newSequence = new LinkedListSequence<T>();

        for(int i = 0; i < this->count; i++)
            newSequence->Append(this->Get(i));

        for(int i = 0; i < sequence.GetLength(); i++)
            newSequence->Append(sequence.Get(i));

        return newSequence;
    }

    virtual LinkedListSequence<T>* GetSubSequence(int startIndex, int endIndex) const override{
        LinkedList<T> *subList = this->buffer->getSublist(startIndex, endIndex);
        LinkedListSequence<T> *seq = new LinkedListSequence<T>(*subList);
        return seq;
    }





};

#endif