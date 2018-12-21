// MyList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include "MyListTest.h"
#include "MyStackTest.h"
#include <iostream>

//单向链表测试用结构体
typedef struct tag_myList {
    int m_data;
    tag_myList* m_pNext;
};

//栈模拟数学运算
//需两个栈
//num_stack为存放数字的栈
//char_stack为存放运算符的栈
MyStackTest<float> num_stack;
MyStackTest<char> char_stack;

//计算式
char szCalc[64] = "3*2-1+2-3+4/2+1";
//存放结果
float nResult = 0;

//判断是否为数字
bool funcJudgeNum(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

//枚举运算符
enum e_judgeOp{
    SUB = 1,    // -
    ADD = 2,    // +
    DIV = 3,    // /
    MUL = 4     // *
};

//判断运算符优先级
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

//计算结果
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
    //如果运算符栈不为空
    if (!char_stack.empty_stack()) {
        if (funcJudgeOperator(szCalc[val]) == MUL || funcJudgeOperator(szCalc[val]) == DIV) {
            //若即将进入的符号优先级高，则入栈
            funcTest(val);
        } else {
            while (funcJudgeOperator(szCalc[val]) == ADD || funcJudgeOperator(szCalc[val]) == SUB) {
                float nTempA = 0.0f;
                float nTempB = 0.0f;

                if (char_stack.empty_stack()) {
                    break;
                }

                //先保存数字栈的栈顶数字
                if (!num_stack.empty_stack()) {
                    nTempA = num_stack.top_stack();
                    //弹出栈顶数字
                    num_stack.pop_stack();
                }

                //再保存数字栈的栈顶数字
                if (!num_stack.empty_stack()) {
                    nTempB = num_stack.top_stack();
                    //弹出栈顶数字
                    num_stack.pop_stack();
                }
                //得出计算结果并保存
                nResult = funcCalcResult(nTempA, nTempB, funcJudgeOperator(char_stack.top_stack()));
                //结果压入数字栈
                num_stack.push_stack(nResult);
                //弹出运算符栈的栈顶运算符
                char_stack.pop_stack();
            }
            funcTest(val);
        }
    } else { //如果运算符栈为空，则直接压入运算符
        funcTest(val);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    //单向链表测试（和实验无关）
    tag_myList* pHead = new tag_myList;
    pHead->m_pNext = nullptr;

    for (int i = 0; i < 5; i++) {
        tag_myList* tagTemp = new tag_myList;
        tagTemp->m_data = i;
        tagTemp->m_pNext = pHead->m_pNext;
        pHead->m_pNext = tagTemp;
    }

    pHead = pHead->m_pNext;

    printf("单向链表测试\r\n");
    while (pHead != nullptr) {
        printf("%d ", pHead->m_data);
        pHead = pHead->m_pNext;
    }
    printf("\r\n\r\n");

    delete[] pHead;

    //实验部分
    MyListTest<int> CTest;
    printf("首部添加\r\n");
    CTest.push_front(4);
    CTest.push_front(5);
    CTest.push_front(6);
    CTest.printValue();
    printf("\r\n\r\n");

    printf("尾部添加\r\n");
    CTest.push_back(1);
    CTest.push_back(2);
    CTest.push_back(3);
    CTest.printValue();
    printf("\r\n\r\n");

    printf("首部删除\r\n");
    CTest.pop_front();
    CTest.pop_front();
    CTest.printValue();
    printf("\r\n\r\n");

    printf("尾部删除\r\n");
    CTest.pop_back();
    CTest.pop_back();
    CTest.printValue();
    printf("\r\n\r\n");

    printf("迭代器begin\r\n");
    printf("%p", CTest.begin());
    printf("\r\n\r\n");
    printf("迭代器end\r\n");
    printf("%p", CTest.end());
    printf("\r\n\r\n");

    MyListTest<int>::Iterator it = CTest.begin();

    printf("迭代器Insert\r\n");
    CTest.insert(it, 88);
    CTest.printValue();
    printf("\r\n\r\n");

    //===============================
    //=============分割线=============
    //===============================

    char szTemp[3] = "+0";
    strcat(szCalc, szTemp);

    //计算计算式的长度
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