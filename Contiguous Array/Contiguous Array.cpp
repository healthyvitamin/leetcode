/*
題目給一個元素為二位元的陣列，希望找子串列，這個子串列有一樣數量的0跟1，找最多的。
例如 [0,0,1,1,0,1,0,0,1,0,1] 則後面十個元素就是最長的子串列，因為可以包含5個0跟5個1
直覺方法:
    用i跟j分別找出 num[i]~num[j]有幾個0與幾個1
    故很明顯這樣就會有
    for (int i)
    {
        for (int j)
        {
            for (int k=i; k <= j)
                取得num[i]~num[j]有多少個0
            for (int k=i; k <= j)
                取得num[i]~num[j]有多少個1
            當兩個相同代表是一個子串列
                紀錄是否是目前最長的

        }
    }
    三層的迴圈，這樣在時間複雜度是"次方時間" 肯定會TLE

    故怎麼改善?
    通常有幾種做法 1.減少變數 2.減少迴圈層數
    1.減少變數
師解:
有十個數      0 1 2 3 4 5 6 7 8 9 10
            [0,0,1,1,0,1,0,0,1,0,1]
count0(0,10): 1 2 2 2 3 3 4 5 5 6 6   有6個0

count(2,10) : - - 0 0 1 1 2 3 3 4 4   有4個0

可以發現，count(2,10) 就是 count(0,10) - count(0,1)
            4               6               2

故可以將原本第三層的兩個for迴圈變成
    count0(0,j) - count0(0, i-1) 以及 count1(0,j) - count1(0,i-1)
    就可以得知num[i]~num[j] 有幾個0跟1了

故目前程式碼是
    if(count0(0,j) - count0(0,i-1) == count1(0,j) - count1(0,i-1)
再來進行數學上的調換，將用到j變數跟i變數分別換到一邊
    if(count0(0,j) - count1(0,j) == count0(0,i-1) - count1(0,i-1)
改成函式
    if(countDiff(j) == countDiff(i-1))


接下來回顧一下總程式碼
所以目前是
for (int i)
    {
        for (int j)
        {
            if(countDiff(j) == countDiff(i-1)){
                紀錄是否是目前最長的
            }
        }
    }
再來可以觀察，希望可以簡化j迴圈，因此要先把i迴圈的東西拿出來 把i變數去除，因此可以把coundiff(i-1)拿出來
再把紀錄目前是否是最長的值得部分 改成先找最大的j
for (int i)
    {
        int target = countDiff(i-1)
        int maxj = -1;

        --------------變成了找一個值的存在，可以寫成函式findmaxj---------------
        for (int j)
        {
            if(countDiff(j) == target){
                maxj = j;
            }
        }
        ----------------------------------------------

        //紀錄是否是目前最長的
        int lenght = maxj - i + 1;
        if(length > maxLength){
            maxLength = length;
        }
    }
故目前可以知道 j迴圈 徹底變成了單純找一個值的存在 ，將他寫成函式 findMaxj

以上皆為精簡程式碼，並沒有優化
---------------------------------------------------------------------------
接下來才是真正的優化
希望可以把for迴圈的countDiff變成一開始就已經找好答案了，接下來取用只需要countDiff[索引]
希望target = countDiff[i-1]; 這樣子去取用

回顧一下countdiff的定義: 給一個索引，找出 [0~索引中] 0跟1出現的次數差了幾次
(另外findMaxJ的定義: 給0跟1出現的次數差了幾次，找出差這麼多次的索引是誰
所以其實findMaxJ跟countdiff是相反的函式 )

1.如何直接先算好countDiff的答案? 只要把原函式的程式拉出來實作就可以了
並且計算方法從累加變成countDiff[k] = countDiff[k-1] +1;

2.此方法會有索引的問題 因為countDiff[0]必須由countDiff[-1] +- 1得來，-1會導致陣列報錯
因此額外做個函式 int cindex(int j)

3.int countDiff[?] 陣列要設多大?
   我們多設計了一個"索引-1"當作初始值: -1~ numsSize-1
   然而陣列只能從0開始存
   換句話說真正在取用的時候  countDiff[0] 才是 countDiff[-1]
   因此需要: (numsSize-1) - (-1) + 1 個空間

故目前從三層迴圈變成兩層迴圈了
----------------------------------------------------------------------
對findMaxJ做同樣的事，化成陣列
1.這邊可以偷吃步，因為上面知道了findMaxJ跟countdiff其實是相反的函式
例如j= 3 countDiff[cindex(3)] = 10 ，代表nums[0]~nums[3]，0跟1的次數差了10次
那麼我們可以記錄 findMaxJ[10] = 3 ，代表0跟1的次數差了10次 在索引3的時候出現
   問題: 如果0跟1的次數差了10次 在索引5的時候也出現了呢? 會衝突
        沒有關係，因為是要找MaxJ 故可以給他覆蓋掉

2.陣列初始化的大小要多大?
    也就是說 countDiff[cindex(3)] == target 會多大?
    A: 最小值:全部都是1，0跟1差了numsSize個，最大值:全部都是0,0跟1差了numsSize個，
    故 -numsSize ~ numsize
    故最大值-最小值+1 = 所需空間 需要 2 * numsSize + 1 個

3.因此跟countDiff的cindex一樣，findMaxJ用到了負索引
因此真正在調用時需要一個函式轉換索引
findex()
-----------------------------------------------------------------------

總結:
解題精神:減少變數，用空間換取時間，得到精簡函式
for迴圈轉換成陣列儲存
*/

int findex(int j, int numsSize) {
    return j + numsSize;
}
int cindex(int j) {
    return j + 1;
}

/*
//countDiff: 給一個索引，找出 [0~索引中] 0跟1出現的次數差了幾次
int countDiff(int j, int* nums){
    int diff = 0;
    for(int k = 0; k<= j; k++)
    {
        if(nums[k] == 0){
            diff++; //使用累加的方式計算，碰到0就+1，碰到1就-1
        }else{
            diff--;
        }
    }
    return diff;
}

//findMaxJ: 給0跟1出現的次數差了幾次，找出差這麼多次的索引是誰
int findMaxJ(int numsSize, int target, int* countDiff){
    int maxJ = -1;
    for(int j=0; j <numsSize; j++){
        if(countDiff[cindex(j)] == target){
            maxJ = j;
        }
    }
    return maxJ;
}
*/

int findMaxLength(int* nums, int numsSize) {

    //-----------先計算好所有的countDiff-------------
    int countDiffSize = (numsSize - 1) - (-1) + 1;
    int countDiff[countDiffSize];

    countDiff[cindex(-1)] = 0; //初始值
    for (int k = 0; k < numsSize; k++)
    {
        if (nums[k] == 0)
        {
            countDiff[cindex(k)] = countDiff[cindex(k - 1)] + 1;

        }
        else {
            countDiff[cindex(k)] = countDiff[cindex(k - 1)] - 1;
        }
    }
    //-------先計算好所有的findMaxJ------------------------------

    int findMaxJSize = 2 * numsSize + 1; //同上，-numsSize ~ numsSize  
    int findMaxJ[findMaxJSize];

    //先進行初始化，全部設為-1
    //
    for (int k = -numsSize; k <= numsSize; k++) {
        findMaxJ[findex(k, numsSize)] = -1;
    }

    //計算
    for (int j = 0; j < numsSize; j++) {
        findMaxJ[findex(countDiff[cindex(j)], numsSize)] = j;
    }
    //-------------------------------------
    int maxLength = 0;
    for (int i = 0; i < numsSize; i++) {

        int target = countDiff[cindex(i - 1)];

        int length = findMaxJ[findex(target, numsSize)] - i + 1;
        if (length > maxLength) {
            maxLength = length;
        }
    }

    return maxLength;

}