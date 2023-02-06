/*
此題為實作堆疊 每個函式需要時間複雜度為O(1)
1.使用data陣列實作堆疊
2.使用top_pointer當作頂端的旗標
3..使用min_value陣列儲存堆疊中當top_pointer的指向該索引時，堆疊內最小的值
    舉例來說 依序push    [4.3,2,2,5]
    則min_value陣列會儲存[4,3,2,2,2]
4. 因為陣列要增長 因此使用C語言的malloc、realloc 因此data、min_value都是用指標來存的
*/
typedef struct {
    int* data;
    int* min_value;
    int top_pointer;
} MinStack;


MinStack* minStackCreate() {
    MinStack* s = malloc(sizeof(MinStack));
    s->data = NULL;
    s->min_value = NULL;
    s->top_pointer = -1;

    return s;
}

void minStackPush(MinStack* obj, int val) {

    obj->top_pointer++;

    obj->data = realloc(obj->data, sizeof(int) * (obj->top_pointer + 1));
    obj->data[obj->top_pointer] = val;

    obj->min_value = realloc(obj->min_value, sizeof(int) * (obj->top_pointer + 1));

    if (obj->top_pointer == 0 || obj->min_value[obj->top_pointer - 1] > val)
    {
        obj->min_value[obj->top_pointer] = val;
    }
    else {
        obj->min_value[obj->top_pointer] = obj->min_value[obj->top_pointer - 1];
    }
}

int minStackPop(MinStack* obj) {
    return obj->data[(obj->top_pointer)--];
}

int minStackTop(MinStack* obj) {
    return obj->data[(obj->top_pointer)];
}

int minStackGetMin(MinStack* obj) {
    return obj->min_value[obj->top_pointer];
}

void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj->min_value);
    free(obj);
}



/**

 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/