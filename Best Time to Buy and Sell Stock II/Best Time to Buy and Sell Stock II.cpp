/*
直覺可以想到:是否可以把所有買賣的組合找出來?
由於可以買賣多次，也可以不買不賣 直覺上光是兩個for迴圈是不行的，太多組合數

故可以思考怎麼分割，把問題縮小
答案:最後一天要不要進行賣的動作?
如此便可逐漸縮小範圍

假設決定不賣
max{ [7,1,5,3,6,4] = > [7,1,5,3,6]  直接將size-1 當作它不存在

假設決定要賣，則決定要在哪一天買入
    max{
    [7,1,5,3,6] + (6,4)  代表前面(不管怎樣買賣)的錢 + 在6塊的時候買，4塊的時候賣的錢 (要算賺多少所以是4-6)
                        maxProfit([7,1,5,3,6,4], 5) + (4-6)
    [7,1,5,3] + (3,4)   maxProfit([7,1,5,3,6,4], 4) + (4-3)
    [7,1,5] + (5,4)     maxProfit([7,1,5,3,6,4], 3) + (4-5)
    [7,1] + (1,4)       maxProfit([7,1,5,3,6,4], 2) + (4-1)
    [7] + (7,4)
    }
}
求最大值

prices[4] 意思是在第一天買


*/

/* C語言版本，由於C++參數是給vector，且leetcode無法更改參數列，故在resize部分會相當複雜
故改用C語言

class Solution {
public:
    int maxProfit(int* prices, int pricesSize) {

        //遞迴停止點
        if(prices.size <= 1 ) return 0;

        int profit = 0;
        int max = 0;

        //假設決定不賣
        profit = maxProfit(prices, pricesSize-1);
        if(profit > max) {
            max = profit;
        }

        //假設決定最後一天要賣，注意從1開始，故跟上面原理一樣 只是倒過來了而已
        //先從maxProfit([7,1,5,3,6,4], 1) + (4-7) 開始
        for(int i = 1; i< pricesSize - 1; i++)
        {

            profit = maxProfit(prices , i) + (prices[pricesSize - 1] - prices[i-1]) ;


            if(profit > max) {
                max = profit;
            }

        }
     return max;
    }
};

*/
/*
但是上述方法會TLE，因遞迴重複呼叫函數
可以想到一個改善的地方，因為決定不賣跟決定要賣，有可能算到同一個狀況
故可以改用一個陣列直接儲存答案，如此也不用呼叫函數才能取得答案了

動態規劃: 從1開始推價格，一天可以賺多少(這個一開始就知道=0)，有兩天時又可以賺多少

例如有3天時，
1.首先假設不賣，那就肯定是前面已經算過的只有2天時的答案，所以不用特別計算
profit = profits[k-1];

2.假設要賣的話，就要決定哪一天買了，可以開啟一個for迴圈，從第1天開始算到第2天 (第3天不用 因為同一天買同一天賣沒意義)
跟前面一樣
假如第2天買，那就是 第2天的利益 + 第3天的價格 - 第2天的價格
假如第1天買，那就是 第1天的利益 + 第3天的價格 - 第1天的價格

跟前面的原理一樣
看哪一個高
以此類推，推到最後就知道了總共最大的利益違和了。


class Solution {
public:
    int maxProfit(int* prices, int pricesSize) {

        //遞迴停止點
        if(prices.size <= 1 ) return 0;

        int profits[pricesSize + 1];
        profits[1] = 0;

        //設定最後一天為第k天，因為k-1 最後一天為第一天時沒有意義 故從2開始
        for(int k = 2; k <= pricesSize; k++)
        {
            int profit;
            int max = 0;

            //1.假設決定不賣
            profit = profits[k-1]; //此處-1是因為見上面推導
            if(profit > max){
                max = profit
            }

            //2.假設決定最後一天要賣:
            for(int i = 1; i <= k-1; i++)
            {
                profit = profits[i] + prices[k-1] - prices[i-1];  //此處-1是因為索引，k=3=第3天 第三個值在陣列中的索引位置是2
                if(profit > max){
                    max = profit;
                }

            }
            profits[k] = max

        }

     return profits[pricesSize] = max ;
    }

};


但此效率依然不夠高，因為有兩層for迴圈
*/

/*

只看相鄰的兩天，如果昨天比較便宜，今天比較貴，那就進行買賣
為何這樣可以? 師未解


class Solution {
public:
    int maxProfit(int* prices, int pricesSize) {

        int total = 0;
        for(int i = 0; i < pricesSize - 1; i++)
        {
            if(prices[i] < prices[i+1]){
                total += prices[i+1] - prices[i];
            }

        }

    }

};

*/



