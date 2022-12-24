#pragma once
#include <iostream>
//
// Created by user on 11.04.2022.
//


using namespace std;


#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

template <class T>
class Sequence
{
public:

    virtual ~Sequence() = default;

    virtual T GetFirst() = 0;

    virtual T& Get(size_t index) = 0;

    virtual void Append(const T& item) = 0;

    virtual void Prepend(const T &item) = 0;

    virtual void InsertAt(const T &item, int index) = 0;

    virtual T GetLast() = 0;

    virtual void Set(const T& element, int index) = 0;

    virtual void Delete(int index) = 0;

    virtual int GetLength() const = 0;

    virtual void PrintArray() = 0;

    virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) const = 0;

    virtual Sequence<T>* Concatenate(Sequence<T>& sequence) = 0;




};


#endif
