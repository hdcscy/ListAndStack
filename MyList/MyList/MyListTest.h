#pragma once

#include <new>
#include <iostream>

template<class T>
class MyListTest {
protected:
    //����ṹ��
    struct tag_myList {
        tag_myList(T nTempData) {
            m_nData = nTempData;
            m_pNext = nullptr;
            m_pPrevious = nullptr;
        }
        //��һ�����
        tag_myList* m_pNext;
        //��һ�����
        tag_myList* m_pPrevious;
        //����
        T m_nData;
    };

public:
    MyListTest();
    ~MyListTest();

    //ѹ��Ԫ�أ����
    void push_back(const T& val) throw(std::bad_alloc);

    //ѹ��Ԫ�أ���ǰ��
    void push_front(const T& val) throw(std::bad_alloc);

    //����Ԫ�أ����
    void pop_back();

    //����Ԫ�أ���ǰ��
    void pop_front();

    //��ӡ
    void printValue();

    //�ж��Ƿ�Ϊ��
    bool empty();

    //����������
    int length();

    //��������
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

    //����
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

    //����
    //��д

protected:
    //ͷ���
    tag_myList* m_pHead;
    //������
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

//ѹ��Ԫ�أ���ǰ��
template<class T>
void MyListTest<T>::push_front(const T& val) {
    tag_myList* tagTest = new tag_myList(val);
    //����ͷ������һ����ַָ��
    tag_myList* p_tagHeadTemp = m_pHead->m_pNext;

    //�����ʼ���ѷ����쳣�����׳��쳣
    if (tagTest == nullptr) {
        throw std::bad_alloc();
    }
    //ͷ������һ����ַָ��ָ���²���Ľ��
    m_pHead->m_pNext = tagTest;

    //�²��������һ����ַָ��ָ��ͷ���
    tagTest->m_pPrevious = m_pHead;

    //�ٰ�ͷ������һ����ַָ�븳ֵ���²���ָ�����һ������ַ
    tagTest->m_pNext = p_tagHeadTemp;

    if (p_tagHeadTemp != nullptr) {
        p_tagHeadTemp->m_pPrevious = tagTest;
    }

    m_nLength = m_nLength + 1;
    return;
}

//ѹ��Ԫ�أ����
template<class T>
void MyListTest<T>::push_back(const T& val) {
    tag_myList* p_tagTest = new tag_myList(val);
    //����ͷ�������
    tag_myList* p_tagHeadTemp = m_pHead;

    //�����ʼ���ѷ����쳣�����׳��쳣
    if (p_tagTest == nullptr) {
        throw std::bad_alloc();
    }

    //�����������ڶ������Ϊֹ
    while (p_tagHeadTemp->m_pNext != nullptr) {
        p_tagHeadTemp = p_tagHeadTemp->m_pNext;
    }

    //���²�����ĵ�ַ��ֵ����һ��������һ������ַ
    p_tagHeadTemp->m_pNext = p_tagTest;

    //����һ�����ĵ�ַ��ֵ���²��������һ������ַ
    p_tagTest->m_pPrevious = p_tagHeadTemp;

    m_nLength = m_nLength + 1;
    return;
}

//����Ԫ�أ���ǰ��
template<class T>
void MyListTest<T>::pop_front() {
    if (m_pHead->m_pNext == nullptr) {
        throw std::bad_alloc();
    }

    //�����������������
    tag_myList* p_tagHeadTemp = m_pHead->m_pNext->m_pNext;
    //����ڶ����������
    tag_myList* p_tagTemp = m_pHead->m_pNext;

    //��ͷ������һ������ַ��Ϊ����������ַ
    m_pHead->m_pNext = p_tagHeadTemp;

    //��������������һ������ַ��Ϊͷ���
    m_pHead->m_pNext->m_pPrevious = m_pHead;

    //�ͷŵڶ������
    delete p_tagTemp;

    m_nLength = m_nLength - 1;
    return;
}

//����Ԫ�أ����
template<class T>
void MyListTest<T>::pop_back() {
    if (m_pHead->m_pNext == nullptr) {
        throw std::bad_alloc();
    }

    tag_myList* p_tagHeadTemp = m_pHead;

    //���������һ��
    while (p_tagHeadTemp->m_pNext != nullptr) {
        p_tagHeadTemp = p_tagHeadTemp->m_pNext;
    }

    //���һ������ǰһ������nextָ���ÿ�
    p_tagHeadTemp->m_pPrevious->m_pNext = nullptr;

    //ɾ�����һ�����
    delete p_tagHeadTemp;

    m_nLength = m_nLength - 1;
    return;
}

//��ӡ
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

//���ش�С
template<class T>
int MyListTest<T>::length() {
    return m_nLength;
}

//�ж�ջ�Ƿ�Ϊ��
template<class T>
bool MyListTest<T>::empty() {
    if (m_pHead->m_pNext == nullptr) {
        return true;
    }
    return false;
}