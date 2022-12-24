#pragma once
#include <iostream>
#include "Sequence.h"
#include "DynamicArray.h"


//
// Created by user on 11.04.2022.
//


using namespace std;


#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

template <class T> class ArraySequence : public Sequence<T>{
private:
    DynamicArray<T>* buffer;
    size_t count;
public:
    ArraySequence(T* items, size_t Count){
        count = Count;
        buffer = new DynamicArray<T>(items, count);
    }

    ArraySequence(){
        buffer = new DynamicArray<T>(0);
        count = 0;
    }

    ArraySequence (DynamicArray<T>* list){
        buffer = new DynamicArray<T>(*list);
        count = list->GetSize();
    }

    ~ArraySequence () {
        this->buffer->~DynamicArray();
    }

    ArraySequence (const ArraySequence & object)
    {
        count = object.count;
        buffer = new DynamicArray<T>(object.buffer, count);
    }

    virtual T GetFirst() override
    {
        if (this->count){
            return this->buffer->Get(0);

        } else{
            throw "Zero vector";
        }
    }

    virtual T GetLast() override{
        return buffer->Get(count - 1);
    }

    virtual T& Get(size_t index) override
    {
        if (this->count){
            return this->buffer->Get(index);
        }
        else{
            throw "Zero vector";
        }
    }

    virtual void Set(const T& element, int index) override{
        if(index < 0 || index >= count){
            throw "index out of range";
        }
        buffer->Set(index, element);

    }

    virtual ArraySequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
        if(startIndex < 0 || startIndex >= count){
            throw "index out of range";
        }
        if(endIndex < 0 || endIndex > count){
            throw "index out of range";
        }
        if(startIndex > endIndex){
            throw "index out of range";
        }

        //T subArray[endIndex - startIndex];
        T* subArray = (T*) malloc(sizeof(T) * (endIndex - startIndex));
        for(int i = 0; i < endIndex - startIndex; i++)
            subArray[i] = buffer->Get(i + startIndex);

        ArraySequence<T> *subSequence = new ArraySequence<T>(subArray, endIndex - startIndex);

        return subSequence;
    }

    virtual ArraySequence<T>* Concatenate(Sequence<T>& sequence) override{
        DynamicArray<T> *array = new DynamicArray<T>(count + sequence.GetLength());
        ArraySequence<T> *newSequence = new ArraySequence<T>(array);
        for(int i = 0; i < count; i++){
            newSequence->Set(buffer->Get(i), i);
        }

        for(int i = 0; i < sequence.GetLength(); i++)
            newSequence->Set(sequence.Get(i), i + count);

        return newSequence;
    }

    virtual int GetLength() const override{
        return count;
    }

    virtual void Append(const T& item) override{
        if (buffer->GetSize() > count){
            buffer->Set(count++, item);
        } else{
            if (buffer->GetSize() != 0){
                buffer->Resize(buffer->GetSize() * 2);
            }
            else{
                buffer->Resize(2);
            }
            buffer->Set(count++, item);
        }
    }



    virtual void Prepend(const T &item) override{
        if (buffer->GetSize() <= count) {
            buffer->Resize(buffer->GetSize() * 2);
        }
        for (int i = count - 1; i >= 0; i--){
            buffer->Set(i + 1, buffer->Get(i));
        }
        buffer->Set(0, item);
        count++;
    }

    virtual void InsertAt(const T &item, int index) override{
        if (buffer->GetSize() <= count) {
            buffer->Resize(buffer->GetSize() * 2);
        }
        for (int i = count - 1; i >= index; i--){
            buffer->Set(i + 1, buffer->Get(i));
        }
        buffer->Set(index, item);
        count++;

    }

    virtual void Delete(int index) override{
        if (index >= this->count || index < 0){
            throw "Incorrect index";
        }
        auto buf = new ArraySequence<T>();
        for (int i = 0; i < this->count; i++){
            if (i != index){
                buf->Append(buffer->Get(i));
            }
        }
        count--;
        buffer = buf->buffer;
//        delete buf;

    }

    virtual void PrintArray() override{
        for (int i = 0; i < count; i++){
            cout << buffer->Get(i) << " ";
        }
        cout << endl;
    }



    //Sequence<T>* Concat(Sequence <T> *list){}

};

ostream& operator<<(ostream &os, const pair<float, float>& d) {
    return os  << '(' << d.first << ", " << d.second << ')';
}

ostream& operator<<(ostream &os, const pair<int, double>& d) {
    return os  << '(' << d.first << ", " << d.second << ')';
}

ostream& operator<<(ostream &os, pair<int, Sequence<int>*> d) {

    os << "(" << d.first << ": ";
    for (int i = 0; i < d.second->GetLength(); i++) {
        os << d.second->Get(i) << " ";
    }
    os << ")";

    return os;
}

ostream& operator<<(ostream &os, pair<int, Sequence<std::pair<int, double> >*> d) {

    os << "(" << d.first << ": ";
    for (int i = 0; i < d.second->GetLength(); i++) {
        os << "[" << d.second->Get(i).first << ", " << d.second->Get(i).second << "] ";
    }
    os << ")";

    return os;
}


#endif