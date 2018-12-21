#pragma once
#include "MyListTest.h"

template<class T>
class MyStackTest : protected MyListTest<T> {
public:
    MyStackTest();
    ~MyStackTest();

    void pop_stack() {
        pop_back();
    }

    void push_stack(const T& val) {
        push_back(val); 
    }

    int size_stack() {
        return length();
    }

    T& top_stack() {
        tag_myList* p_tagTemp = m_pHead;

        while (p_tagTemp->m_pNext != nullptr) {
            p_tagTemp = p_tagTemp->m_pNext;
        }

        T& nRefTemp = p_tagTemp->m_nData;
        return nRefTemp;
    }

    bool empty_stack() {
        return empty();
    }

    void printValue_stack() {
        printValue();
    }

private:
    char szHighPriority[3];
    char szLowPriority[3];
};

template<class T>
MyStackTest<T>::MyStackTest() {
    strcpy(szHighPriority, "*/");
    strcpy(szLowPriority, "+-");
}

template<class T>
MyStackTest<T>::~MyStackTest() {
}

