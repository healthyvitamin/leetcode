/*
解題思路有幾個方法:
1.先學會檢查，試著局部修正，重複做到檢查不出問題為止
    => 沒有信心這樣會對
2.每次完成一部分
    => 每次真的都完成了一部分，慢慢做總會對
3.直接生出答案
    => 有些時候需要額外的空間
    => 觀察寫入跟讀取的位置，如果寫入後的東西不會再被讀就可以不需要額外的空間

4.把所有有可能的排列組合找出來
    => 即暴力法，優點在於什麼場合都可以使用此方法，但速度極慢

以下介紹三種方式


第一個:用for迴圈從頭掃到尾，當發現一個非0數值時，就在開啟一個for迴圈搜尋他前面是否有0可以進行交換
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int k = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            bool is_zero_aval = false;

            if (nums[i] != 0) //當碰到一個非0數值時
            {
                //搜尋他前面是否有0的位置可做交換  

                /*在這邊時就會有局部修正造成的問題
                假如沒有想到可以用搜尋的
                而是僅僅去檢查k
                    if(nums[k] == 0)
                則假如題目給你[1,0,1]，當你檢查到第三個值1，但因為有交換時才進行k++，故K依然停留在初始值
                              ^   ^
                              k   i
                此時是無法搬動的，造成錯誤，接著你開始反覆的修正
                過程中你無法知道這次的修正對不對，只有一次修到好跟修不好，跟第二個方法有著天壤之別。
                */
                for (int j = k; j < i; j++)
                {
                    if (nums[j] == 0)
                    {
                        k = j;
                        is_zero_aval = true;
                        break;
                    }
                }

                //有的話才做交換
                if (is_zero_aval)
                {
                    nums[k] = nums[i];
                    nums[i] = 0;
                }



            }
            //  cout << "k=" << k << endl;


        }

    }
};

/*

第二個:使用while不斷進行"檢查"相鄰的兩個數值，如果是左方為0，右方非0，則代表可以進行交換
交換完break進行下一次掃描 (即每次掃描只糾正一個錯誤)
使用一個旗標check，檢查此次迴圈是否沒有做任何交換 (代表全部已交換完畢，可return了)
或者用一個count變數計算此次迴圈是否也進行交換也可。

不過此方法會TLE

可以想像是因為每交換一次就break
因此不break即可通過

但是明顯花的時間會比第一個方法多很多，這是因為我們只交換一次，每次掃描完一次一定會有一個0移動到最後面
有點像是泡沫排序，一次至少解決一個，時間花費O(n平方)

*/

/*

class Solution {
public:
    void moveZeroes(vector<int>& nums) {

        bool check = true;

        while(check){

            check = false;

            for(int i = 0 ; i+1 < nums.size(); i++)
            {

                //左方為0 右方非0 代表還沒有完成
                if(nums[i] == 0 && nums[i+1] != 0)
                {
                    check =true;

                    int t = nums[i];
                    nums[i] = nums[i+1];
                    nums[i+1] = t;
                 //   break;
                }
            }

        }

    }
};

*/


/*
第三個方法:直接寫答案
掃描一次，把第一個非0的直接存到第一個位子，第二個非0的直接存到第二個位子
以此類推，

注意此方法是建立在j <= i ，即j永遠不會超過i，否則有可能j超過i 以至於覆寫到以前寫過的值
故保險一點的作法是可以建立一個新的陣列。

而此題不需要故叫做in-place(原地處理)，因為j一定<= i，
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {


        int j = 0;


        //先放不是0的
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0)
            {
                nums[j] = nums[i];
                j++;
            }

        }

        //再放是0的
        while (j < nums.size()) {
            nums[j] = 0;
            j++;
        }

    }
};
