#pragma once

#include <new>
#include <iostream>

template<class T>
class MyListTest {
protected:
    //链表结构体
    struct tag_myList {
        tag_myList(T nTempData) {
            m_nData = nTempData;
            m_pNext = nullptr;
            m_pPrevious = nullptr;
        }
        //下一个结点
        tag_myList* m_pNext;
        //上一个结点
        tag_myList* m_pPrevious;
        //数据
        T m_nData;
    };

public:
    MyListTest();
    ~MyListTest();

    //压入元素（最后）
    void push_back(const T& val) throw(std::bad_alloc);

    //压入元素（最前）
    void push_front(const T& val) throw(std::bad_alloc);

    //弹出元素（最后）
    void pop_back();

    //弹出元素（最前）
    void pop_front();

    //打印
    void printValue();

    //判断是否为空
    bool empty();

    //返回链表长度
    int length();

    //迭代器类
    class Iterator {
    public:
        Iterator(tag_myList* p_nTemp) {
            m_nPtr = p_nTemp;
        }

    private:
        friend class MyListTest;
        tag_myList* m_nPtr;
    };

    Iterator begin() {
        if (m_pHead->m_pNext == nullptr) {
            throw std::bad_alloc();
        }

        return m_pHead->m_pNext;
    }

    Iterator end() {
        if (m_pHead->m_pNext == nullptr) {
            throw std::bad_alloc();
        }

        tag_myList* p_tagTemp = m_pHead;

        while (p_tagTemp != nullptr) {
            p_tagTemp = p_tagTemp->m_pNext;
        }

        return p_tagTemp;
    }

    //插入
    Iterator insert(Iterator& position, const int& val) {
        tag_myList* p_tagInsert = new tag_myList(val);
        tag_myList* p_tagTemp = position.m_nPtr->m_pPrevious;

        p_tagTemp->m_pNext = p_tagInsert;
        position.m_nPtr->m_pPrevious = p_tagInsert;

        p_tagInsert->m_pNext = position.m_nPtr;
        p_tagInsert->m_pPrevious = p_tagTemp;

        m_nLength = m_nLength + 1;
        return p_tagInsert;
    }

    //擦除
    //待写

protected:
    //头结点
    tag_myList* m_pHead;
    //链表长度
    int m_nLength;
};

template<class T>
MyListTest<T>::MyListTest() {
    m_pHead = new tag_myList(0);
    m_nLength = 0;
}

template<class T>
MyListTest<T>::~MyListTest() {
}

//压入元素（最前）
template<class T>
void MyListTest<T>::push_front(const T& val) {
    tag_myList* tagTest = new tag_myList(val);
    //保存头结点的下一个地址指针
    tag_myList* p_tagHeadTemp = m_pHead->m_pNext;

    //如果初始化堆发生异常，则抛出异常
    if (tagTest == nullptr) {
        throw std::bad_alloc();
    }
    //头结点的下一个地址指针指向新插入的结点
    m_pHead->m_pNext = tagTest;

    //新插入结点的上一个地址指针指向头结点
    tagTest->m_pPrevious = m_pHead;

    //再把头结点的下一个地址指针赋值给新插入指针的下一个结点地址
    tagTest->m_pNext = p_tagHeadTemp;

    if (p_tagHeadTemp != nullptr) {
        p_tagHeadTemp->m_pPrevious = tagTest;
    }

    m_nLength = m_nLength + 1;
    return;
}

//压入元素（最后）
template<class T>
void MyListTest<T>::push_back(const T& val) {
    tag_myList* p_tagTest = new tag_myList(val);
    //保存头结点内容
    tag_myList* p_tagHeadTemp = m_pHead;

    //如果初始化堆发生异常，则抛出异常
    if (p_tagTest == nullptr) {
        throw std::bad_alloc();
    }

    //遍历到倒数第二个结点为止
    while (p_tagHeadTemp->m_pNext != nullptr) {
        p_tagHeadTemp = p_tagHeadTemp->m_pNext;
    }

    //将新插入结点的地址赋值给上一个结点的下一个结点地址
    p_tagHeadTemp->m_pNext = p_tagTest;

    //将上一个结点的地址赋值给新插入结点的上一个结点地址
    p_tagTest->m_pPrevious = p_tagHeadTemp;

    m_nLength = m_nLength + 1;
    return;
}

//弹出元素（最前）
template<class T>
void MyListTest<T>::pop_front() {
    if (m_pHead->m_pNext == nullptr) {
        throw std::bad_alloc();
    }

    //保存第三个结点的内容
    tag_myList* p_tagHeadTemp = m_pHead->m_pNext->m_pNext;
    //保存第二个结点内容
    tag_myList* p_tagTemp = m_pHead->m_pNext;

    //将头结点的下一个结点地址改为第三个结点地址
    m_pHead->m_pNext = p_tagHeadTemp;

    //将第三个结点的上一个结点地址改为头结点
    m_pHead->m_pNext->m_pPrevious = m_pHead;

    //释放第二个结点
    delete p_tagTemp;

    m_nLength = m_nLength - 1;
    return;
}

//弹出元素（最后）
template<class T>
void MyListTest<T>::pop_back() {
    if (m_pHead->m_pNext == nullptr) {
        throw std::bad_alloc();
    }

    tag_myList* p_tagHeadTemp = m_pHead;

    //遍历至最后一项
    while (p_tagHeadTemp->m_pNext != nullptr) {
        p_tagHeadTemp = p_tagHeadTemp->m_pNext;
    }

    //最后一个结点的前一个结点的next指针置空
    p_tagHeadTemp->m_pPrevious->m_pNext = nullptr;

    //删除最后一个结点
    delete p_tagHeadTemp;

    m_nLength = m_nLength - 1;
    return;
}

//打印
template<class T>
void MyListTest<T>::printValue() {
    tag_myList* p_tagTest = m_pHead;

    p_tagTest = p_tagTest->m_pNext;

    while (p_tagTest != nullptr) {
        std::cout << p_tagTest->m_nData << " ";
        p_tagTest = p_tagTest->m_pNext;
    }

    delete p_tagTest;
    return;
}

//返回大小
template<class T>
int MyListTest<T>::length() {
    return m_nLength;
}

//判断栈是否为空
template<class T>
bool MyListTest<T>::empty() {
    if (m_pHead->m_pNext == nullptr) {
        return true;
    }
    return false;
}