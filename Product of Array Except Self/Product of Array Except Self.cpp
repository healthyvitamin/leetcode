/**
題目:假如目前nums[0] 算第一個:結果便是把除了自己以外的數字都相乘
所以[1,2,3,4] 會變成 2*3*4=24

首先直覺:
    第一個for迴圈，從nums[0~n]
        第二個for迴圈，將其他的數字相乘

但是題目要求必須O(n) 故似乎只能有一個for迴圈 怎麼辦?
兩個方法:1.for迴圈改用陣列先儲存好結果
2.從數學上找出破口 直接減少運算量

2.故觀察題目
首先我們可以改成所有的數字都相乘，最後再除以nums[i]就好了
但發現除以0時怎麼辦?
故可以發現 當有0出現在陣列時，許多的運算都可以跳過

因此會出現三種狀況
1.陣列中有一個0時，則除了nums[i]=0的這個之外，其餘的運算結果都是0
2.有兩個0時，全部運算結果都是0
3.沒有0，照常運算

---------------------------------------------
但是題目要求不能使用除法 (但上面的方法還是能過 未解)
故改用第一個方法:
首先將其他的數字相乘 拆成兩個部分 left...num[i]....right
先看left
lefts[i] = (num[0] * nums[1] * ... * nums[i-1] )
可以發現
lefts[i] = lefts[i-1] * nums[i-1]
故可以得出程式
int lefts[numsSize];
left[0] = 1;
for(int i=1; i<numsSize; i++){
    lefts[i] = lefts[i-1] * nums[i-1];
}
注意i要從1開始 這樣才不會超出索引

rights同理
，但會有一個問題，跟lefts不同
lefts是從前面增長到後面
1 * nums[0] * .... nums[i-2] = lefts[i-2]
1 * nums[0] * .............. nums[i-1] = lefts[i-1]

但rights是後面增長到前面 或者說從前面開始缺少
right[i] = 1 * nums[i+1] * nums[i+2] *....nums[numsSize-1]
right[i+1]=1 *             nums[i+2] *....nums[numsSize-1]

故沒辦法像是lefts一樣用lefts[i] = lefts[i-1] * nums[i-1]去計算
因此要把它整個反過來，從最後一個開始算，才可以化成
rights[i] = rights[i+1] * nums[i+1];



 * Note: The returned array must be malloced, assume caller calls free().
 */

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* result = malloc(sizeof(int) * numsSize);


    int rights[numsSize];
    //起始值為1，這是因為nums[i] 當i是在numSize-1 也就是最後一個時。他的右邊rights是不會有值得
    //所以當然可以直接設為1 而不用擔心沒有計算到rights[numsSize-1]
    rights[numsSize - 1] = 1;
    //避免超出索引 所以從倒數第2個開始算 numsSize-2
    for (int i = numsSize - 2; i >= 0; i--)
    {
        rights[i] = rights[i + 1] * nums[i + 1];
    }


    int lefts[numsSize];
    for (int i = 0; i < numsSize; i++)
    {
        //將left與最後的for迴圈進行合併而已  但初始i會是0，故要多一道判斷避免超出陣列
        if (i == 0)
        {
            lefts[i] = 1;
        }
        else {
            lefts[i] = lefts[i - 1] * nums[i - 1];
        }

        result[i] = lefts[i] * rights[i];

    }
    return result;
}
/*
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    *returnSize = numsSize;

    //題目要你自己配置一個動態指標陣列去回傳
    int* result = malloc(sizeof(int)*numsSize);

    int numberOfZeros = 0;
    for(int i= 0; i<numsSize; i++)
    {
        if(nums[i] == 0)
        {
            numberOfZeros++;
        }

    }
    //1.有一個0
    if(numberOfZeros == 1)
    {
        int total = 1;
        //故只需要計算那個0時，其他的數的相乘
        for(int i = 0; i<numsSize; i++)
        {
            if(nums[i] != 0)
            {
                total *= nums[i];
            }
        }
        for(int i = 0; i< numsSize; i++)
        {
            if(nums[i] != 0)
            {
                result[i] = 0;
            }
            else
            {
                result[i] = total;
            }
        }

    }
    //有兩個0時
    else if(numberOfZeros >= 2)
    {
        for(int i = 0; i<numsSize; i++)
        {
            result[i] = 0;
        }
    }
    else
    //沒有0時，先把全部加總，再分別除以nums[i]就是result[i]了
    {
        int total = 1;
        for(int k = 0; k< numsSize; k++)
        {
            total *= nums[k];
        }
        for(int i = 0; i < numsSize; i++)
        {
            result[i] = total/nums[i];
        }
    }


    return result;
}
*/