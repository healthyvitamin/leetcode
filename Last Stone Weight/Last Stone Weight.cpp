/*
將最重的兩顆石頭砸在一起，互消重量，只留下差值重量的石頭，例如7與8，則留下一顆重量為1的石頭
一直重複直到只剩下一顆石頭，或沒有石頭(全消掉)後回傳
方法:
    第一種
        用while迴圈，直到陣列元素只剩下一個或0個之前，每次都找最重跟次重的進行合併
    第二種
        先排序好，故可以從陣列尾端一直處理到前端
    第三種:
        觀察題目，stones陣列的元素最大的值是1000

        故使用一個counter[1001] 其索引代表了1~1001
        接著conter[stones[56]] = 1 就代表值56在stones陣列中出現了一次 以此類推
        故如果將所有輸入都這樣轉換進conter
        接下來只要在用一個for迴圈 從1000往回數就可以快速取得最大與次大的值了
*/

//第一種
int extractMax(int* stones, int stonesSize)
{
    int max = stones[0];
    //找出最大值
    for (int i = 0; i < stonesSize; i++)
    {
        if (stones[i] > max)
        {
            max = stones[i];
        }
    }
    //將該最大值設為0，不在上面就做是因為上面的方法是掃完才能確定誰是最大值
    for (int i = 0; i < stonesSize; i++)
    {
        if (stones[i] == max)
        {
            stones[i] = 0;
            break;
        }
    }
    return max;
}

void insert(int* stones, int stonesSize, int value)
{
    for (int i = 0; i < stonesSize; i++)
    {
        if (stones[i] == 0)
        {
            stones[i] = value;
            return;
        }

    }
}

int lastStoneWeight(int* stones, int stonesSize) {

    while (true)
    {
        //取出最大與次大的值
        int y = extractMax(stones, stonesSize);
        int x = extractMax(stones, stonesSize);

        /*
        會有三種狀況
        1. 只剩下一個值，也就是y!=0 x==0
        2. 沒有值，也就是陣列全部=0了 則此時y==0 x==0
        */
        if (x == 0) {
            return y;
        }
        //3. 還有兩個以上的值，要繼續做，因此要把這次石頭碰撞後的值 y-x 儲存回陣列當中
        if (x != y)
        {
            insert(stones, stonesSize, y - x);
        }
    }

    return 0;
}