/*


此題叫你實作一個堆疊
首先我們需要一個main以及一個可以印出堆疊內容的含式，以驗證我們的程式是不是正確的
堆疊實作方法:
    使用陣列
    並且使用指標指向top
問題1.要怎麼知道一個位子有沒有儲存東西?
    A:不需要 只要他還在top指標下就代表是儲存進來的

實作重點:
    1.如何取的目前堆疊最小的值? 並且時間複雜度只能O(1)
    這意味著要從一開始就維護一個值去儲存目前最小的值
    問題1.:如果只儲存一個值，但此值如果POP掉了怎麼辦?
        A:因此要用一個陣列儲存，其大小要跟top-pointer的大小一樣
        例如堆疊依序push 5個值 1,2,3,4,5
        則此陣列要儲存 [1,1,1,1,1] 每個值都是top-pointer停在該索引時，堆疊內最小的值

        因此在判斷目前堆疊內最小值的時候會需要
        1.比對跟上一個最小值，新push的值是不是最小的
        2.是的話才紀錄目前最小值是新push得值
        3.不是的話將上一個最小值紀錄為目前堆疊內的最小值

*/

#include <iostream>
#include <stdexcept>
using namespace std;

typedef struct {
    int data[100];
    int top_pointer;
    int min_value[100];
} MinStack;

void printStack(MinStack* s)
{
    for (int i = 0; i <= s->top_pointer; i++)
    {
        cout << s->data[i] << endl;
    }

}


MinStack* minStackCreate() {
    MinStack* s = new MinStack;
    s->top_pointer = -1;
    return s;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->top_pointer >= 99)
    {
        throw invalid_argument("Push時出錯了");
    }

    obj->data[++(obj->top_pointer)] = val;


    if (obj->top_pointer == 0 || obj->min_value[obj->top_pointer - 1] > val)
    {
        obj->min_value[obj->top_pointer] = val;
    }
    else {
        obj->min_value[obj->top_pointer] = obj->min_value[obj->top_pointer - 1];
    }

}

int minStackPop(MinStack* obj) {
    if (obj->top_pointer >= 99 || obj->top_pointer < 0)
    {


        throw invalid_argument("Pop時出錯了");
    }

    return obj->data[(obj->top_pointer)--];
}

int minStackTop(MinStack* obj) {
    if (obj->top_pointer >= 99 || obj->top_pointer < 0)
    {
        throw invalid_argument("Top時出錯了");
    }
    return obj->data[(obj->top_pointer)];
}


int minStackGetMin(MinStack* obj) {
    if (obj->top_pointer >= 99 || obj->top_pointer < 0)
    {
        throw invalid_argument("GetMin時出錯了");
    }

    return obj->min_value[obj->top_pointer];
}

void minStackFree(MinStack* obj) {
    delete obj;
}


int main()
{
    try
    {
        MinStack* obj = minStackCreate();
        std::cout << "Hello World!\n";
        minStackPush(obj, 20);
        printStack(obj);
        cout << "getmin_value " << minStackGetMin(obj) << endl;
        cout << minStackPop(obj) << endl;
        cout << "目前top_pointer是" << obj->top_pointer << endl;
        cout << "getmin_value " << minStackGetMin(obj) << endl;
        minStackPush(obj, -2);
        cout << "getmin_value " << minStackGetMin(obj) << endl;
    }
    catch (invalid_argument& e) {
        cout << "報錯了 值是 " << e.what() << endl;
    }

    return 0;

}

