// MyList.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <cstdlib>
#include "MyListTest.h"
#include "MyStackTest.h"
#include <iostream>

//������������ýṹ��
typedef struct tag_myList {
    int m_data;
    tag_myList* m_pNext;
};

//ջģ����ѧ����
//������ջ
//num_stackΪ������ֵ�ջ
//char_stackΪ����������ջ
MyStackTest<float> num_stack;
MyStackTest<char> char_stack;

//����ʽ
char szCalc[64] = "3*2-1+2-3+4/2+1";
//��Ž��
float nResult = 0;

//�ж��Ƿ�Ϊ����
bool funcJudgeNum(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

//ö�������
enum e_judgeOp{
    SUB = 1,    // -
    ADD = 2,    // +
    DIV = 3,    // /
    MUL = 4     // *
};

//�ж���������ȼ�
int funcJudgeOperator(char ch) {
    switch (ch) {
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '+':
        return ADD;
    case '-':
        return SUB;
    }
}

//������
float funcCalcResult(float nNumA, float nNumB, int nFlag) {
    switch (nFlag) {
    case 4:
        nResult = nNumB * nNumA;
        return nResult;
    case 3:
        nResult = nNumB / nNumA;
        return nResult;
    case 2:
        nResult = nNumB + nNumA;
        return nResult;
    case 1:
        nResult = nNumB - nNumA;
        return nResult;
    }
}

void funcTest(int val) {
    char_stack.push_stack(szCalc[val]);
}

void funcCalcProcess(int val) {
    //��������ջ��Ϊ��
    if (!char_stack.empty_stack()) {
        if (funcJudgeOperator(szCalc[val]) == MUL || funcJudgeOperator(szCalc[val]) == DIV) {
            //����������ķ������ȼ��ߣ�����ջ
            funcTest(val);
        } else {
            while (funcJudgeOperator(szCalc[val]) == ADD || funcJudgeOperator(szCalc[val]) == SUB) {
                float nTempA = 0.0f;
                float nTempB = 0.0f;

                if (char_stack.empty_stack()) {
                    break;
                }

                //�ȱ�������ջ��ջ������
                if (!num_stack.empty_stack()) {
                    nTempA = num_stack.top_stack();
                    //����ջ������
                    num_stack.pop_stack();
                }

                //�ٱ�������ջ��ջ������
                if (!num_stack.empty_stack()) {
                    nTempB = num_stack.top_stack();
                    //����ջ������
                    num_stack.pop_stack();
                }
                //�ó�������������
                nResult = funcCalcResult(nTempA, nTempB, funcJudgeOperator(char_stack.top_stack()));
                //���ѹ������ջ
                num_stack.push_stack(nResult);
                //���������ջ��ջ�������
                char_stack.pop_stack();
            }
            funcTest(val);
        }
    } else { //��������ջΪ�գ���ֱ��ѹ�������
        funcTest(val);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    //����������ԣ���ʵ���޹أ�
    tag_myList* pHead = new tag_myList;
    pHead->m_pNext = nullptr;

    for (int i = 0; i < 5; i++) {
        tag_myList* tagTemp = new tag_myList;
        tagTemp->m_data = i;
        tagTemp->m_pNext = pHead->m_pNext;
        pHead->m_pNext = tagTemp;
    }

    pHead = pHead->m_pNext;

    printf("�����������\r\n");
    while (pHead != nullptr) {
        printf("%d ", pHead->m_data);
        pHead = pHead->m_pNext;
    }
    printf("\r\n\r\n");

    delete[] pHead;

    //ʵ�鲿��
    MyListTest<int> CTest;
    printf("�ײ����\r\n");
    CTest.push_front(4);
    CTest.push_front(5);
    CTest.push_front(6);
    CTest.printValue();
    printf("\r\n\r\n");

    printf("β�����\r\n");
    CTest.push_back(1);
    CTest.push_back(2);
    CTest.push_back(3);
    CTest.printValue();
    printf("\r\n\r\n");

    printf("�ײ�ɾ��\r\n");
    CTest.pop_front();
    CTest.pop_front();
    CTest.printValue();
    printf("\r\n\r\n");

    printf("β��ɾ��\r\n");
    CTest.pop_back();
    CTest.pop_back();
    CTest.printValue();
    printf("\r\n\r\n");

    printf("������begin\r\n");
    printf("%p", CTest.begin());
    printf("\r\n\r\n");
    printf("������end\r\n");
    printf("%p", CTest.end());
    printf("\r\n\r\n");

    MyListTest<int>::Iterator it = CTest.begin();

    printf("������Insert\r\n");
    CTest.insert(it, 88);
    CTest.printValue();
    printf("\r\n\r\n");

    //===============================
    //=============�ָ���=============
    //===============================

    char szTemp[3] = "+0";
    strcat(szCalc, szTemp);

    //�������ʽ�ĳ���
    int calcLen = strlen(szCalc);
    
    for (int i = 0; i < calcLen; i++) {
        if (funcJudgeNum(szCalc[i])) {
            num_stack.push_stack(szCalc[i] - '0');
        } else {
            funcCalcProcess(i);
        }
    }

    std::cout << "Result: " << nResult << std::endl;
    std::cout << std::endl;

    system("pause");
	return 0;
}