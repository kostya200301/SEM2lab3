#pragma once
#include <iostream>
#include <malloc.h>
//
// Created by user on 11.04.2022.
//


using namespace std;


#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H



template <class T> class DynamicArray{
public:

    ~DynamicArray() {
        delete Array;
    }

    DynamicArray(int size){
        //Array = new T[size];
        Array = (T*) malloc(sizeof(T) * size);
        Size = size;
    }

    DynamicArray(T* items, int count){
        //Array = new T[count];
        Array = (T*) malloc(sizeof(T) * count);
        Size = count;
        for (int i = 0; i < Size; i++){
            *(Array + i) = *(items + i);
        }
    }

    DynamicArray(const DynamicArray<T> & dynamicArray){
        //Array = new T[dynamicArray.Size];
        Array = (T*) malloc(sizeof(T) * dynamicArray.Size);
        Size = dynamicArray.Size;
        for (int i = 0; i < Size; i++){
            *(Array + i) = *(dynamicArray.Array + i);
        }
    }


    int GetSize(){
        return Size;
    }
    void Set(int index, T value){
        *(Array + index) = value;

    }
    T& Get(int index){
        return *(Array + index);
    }

    void Resize(int newSize){
        if (newSize > Size){
            T* pointer = Array;
            //Array = new T[newSize];
            Array = (T*) malloc(sizeof(T) * newSize);
            for (int i = 0; i < Size; i++){
                *(Array + i) = *(pointer + i);
            }
            Size = newSize;
            delete[] pointer;
            //free(pointer);
        } else{
            Size = newSize;
        }
    }
private:
    int Size;
    T* Array;
};

#endif
