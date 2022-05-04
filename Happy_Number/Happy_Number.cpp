
/* 解題想法:
* 可拆解成兩部分
* 1.取得下一位數
* 2.查看此數是否曾出現過 出現過則代表出現循環 如此便可跳出迴圈
*   去判斷是否為1*1*1*1的循環 如果是則=Happy number 不是則不是Happy
* 
* 如何判斷history究竟要多少個? 
1.從題目給int下去做判斷 
由於Int最大的數為2147483647 代表題目最多不會超過此數值
也就是十位數，這意味著最大的數是10個9，而9*9*9*9*..... = 810 即不會超過810種

2.邊做邊長大
顯而易見的 可以用指標陣列進行儲存，但指標依然會有電腦本身記憶體大小的問題
故可用cycle-finding
即同時設定兩個數，一起開始跑，一個一次走一步，另一個一次走兩步，
當他們相撞(相等)時代表出現了循環，如此便可
*/


#include <iostream>

//1.取的下一位數，使用%、/=解決
int next_n(int n){
    int r = 0;
    while (n != 0)
    {
        int d = n % 10;
        n /= 10;
        r += d * d;
    }
    return r;
}

//2.查看此樹是否曾出現過，使用陣列
bool contains(int* history, int size, int n)
{
    for (int i = 0; 1 < size; i++)
    {
        if (history[i] == n)
        {
            return true; //出現過
        }
    }
    return false; //沒出現過
}


int main()
{
    int history[10000];
    int size = 0;

    n = next_n(n);

    while (!contains(history, size, n))
    {
        history[size] = n;
        size++;
        n = next_n(n);
    }

    return n == 1;

    /*
    int slow = n;
    int fast = n;

    do {
        slow = next_n(slow);
        fast = next_n(next_n(fast));
    } while (slow != fast);

    return fast == 1;
    */


  
    
}

