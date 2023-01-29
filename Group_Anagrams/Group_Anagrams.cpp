/*
1.陣列是不能單純用assign複製的 意即你不能宣告另一個陣列然後直接使用=指定複製陣列
且只能用指標互傳 都是傳址呼叫
2.input的型態是:char** 意味著此陣列的每個元素也是一個char陣列
3. 回傳結果是char*** 因為可見output 我們要將元素分類
4. 要注意的是 因為回傳的是陣列 但是陣列只存活於此函數中 (也就是以下我們的程式) 而我們回傳的是此陣列的指標 如果回傳給系統 系統是拿不到的 因為早已因為此函數結束生命周期而陣列也跟著結束
必須借用動態指標 malloc來建立陣列 如此便可保證在系統的主程式結束前 陣列可以存活。


解題思想:
使用排序以確認是否一樣

1.首先使用自製的Pair結構，儲存原本的字元陣列為(original)，與該字元陣列排序後的樣子(sorted)
例如
    original, sorted
    "eat" , "aet"
    "tea" , "aet"
    "tan" , "ant"

2.此時再對pair中的sorted進行排序，便可以將所有sorted，例如是"aet"的都排序在一起
最後可見輸出為
bat: abt //cast 1
eat: aet //case 1
tea: aet //case 2
ate: aet //case 2
tan: ant //case 1
nat: ant //case 2

會使用到qsort以及兩個自製的比較函式

3.建立回傳的陣列，將群組從pairs抓出

首先一開始先塞bat，其為abt的群組  故為abt使用malloc增長"一個"空間

returnResult = malloc(sizeof(char**)*1);
returnResult[0] = malloc(sizeof(char*)*1);
returnResult[0][0] = pairs[0].original;

    *returnSize = 1;
    *returnColumnSizes = malloc(sizeof(int)*1);
    (*returnColumnSizes)[1] = 1;

再來eat 由於aet是不同的群組 所以要"增長一個空間"，可以使用realloc進行增長
returnResult = realloc(returnResult, sizeof(char**)*2);
於是有了returnResult[1]
故
returnResult[1] = malloc(sizeof(char*)*1);
returnResult[1][0] = pairs[1].original;

別忘了這些也要增長
    *returnSize = 2;
    *returnColumnSizes = realloc(sizeof(int)*2);  變成2是因為他是一個陣列，儲存每個群組的有多少個元素
    (*returnColumnSizes)[1] = 1;

再來tea 他是aet群組 故只要
returnResult[1] = realloc(returnResult[1], sizeof(char*)*2 );
returnResult[1][1] = pairs[2].original;
(*returnColumnSizes)[1] = 2;

以上可知，會有三種狀況
1.一開始用malloc增長
2.遇到不同群組，新增另一個群組
3.遇到已有群組，加入已有群組

但其實前兩個可以合併，
故為兩種case
case 1.一開始、遇到未見過的就新增群組
     2.新增到一個已有的群組，故要增長一個群組

前兩個怎麼合併呢?
可以使用一個旗標:lastGroupIndex 代表最後一個group的index
並且將returnResult一開始指向空旗標，如此realloc也可以替代malloc了

合併後:
lastGroupIndex = *returnSize;
returnResult = realloc(returnResult, sizeof(char**)*(*returnSize+1));
returnResult[lastGroupIndex] = malloc(sizeof(char*)*1);
returnResult[lastGroupIndex][0] = pairs[i].original;

(*returnSize)++; // 1
*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize));
(*returnColumnSizes)[i] = 1;

(*returnSize)++; // 2
*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize));
(*returnColumnSizes)[i] = 1;


而case2詳見下方

*/


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

 //#include <cstring>

typedef struct {
    char* original;
    char* sorted;
}Pair;


//為何是用const? 可見qsort所要求的比較函式的寫法
int cmpChar(const void* a, const void* b)
{
    return *(const char*)a - *(const char*)b;
}

int cmpPair(const void* a, const void* b)
{
    const Pair* pa = (const Pair*)a;
    const Pair* pb = (const Pair*)b;

    return strcmp(pa->sorted, pb->sorted);
}


char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {


    //1.使用自製的Pair結構，儲存原本的字元陣列，與該字元陣列排序後的樣子

    Pair* pairs = malloc(sizeof(Pair) * strsSize);

    //排序每個字元陣列 一個就是["eat"] 以儲存進Pairs裡面
    for (int i = 0; i < strsSize; i++)
    {
        char* sorted_str = malloc(sizeof(char) * (strlen(strs[i]) + 1));
        strcpy(sorted_str, strs[i]);
        //要排序的陣列，長度(有幾個字元)，每個字元有多大，以及排序使用的函數
         //排序的函式必須回傳一個整數
        qsort(sorted_str, strlen(strs[i]), sizeof(char), cmpChar);

        pairs[i].original = strs[i];
        pairs[i].sorted = sorted_str;
    }

    //2.再排序一次
    qsort(pairs, strsSize, sizeof(Pair), cmpPair);

    //輸出
    for (int i = 0; i < strsSize; i++)
    {
        printf("%s: %s\n", pairs[i].original, pairs[i].sorted);
    }

    /*可知輸出為 bat: abt
                eat: aet
                tea: aet
                ate: aet
                tan: ant
                nat: ant
    */

    //3.建立回傳的陣列，將群組從pairs抓出

    //初始值
    char*** returnResult = NULL; //0(空指標)
    *returnSize = 0; //要回傳的群組個數
    *returnColumnSizes = NULL; //要回傳的每個群組的元素個數，陣列設為空指標 以方便一開始就可以使用realloc 而不用使用malloc
    int lastGroupIndex = -1;

    for (int i = 0; i < strsSize; i++) {
        

        //由於已經排序好了 故當sorted跟前一個不一樣時，便是代表要新增一個新的群組，否則便可以新增到已有群組 i==0是因為一開始並沒有前一個 故strcmp會出問題
        if (i == 0 || strcmp(pairs[i].sorted, pairs[i = 1].sorted))
            //Case 1 : 新增一個新的群組(group)
        {
            int lastGroupIndex = *returnSize;
            returnResult = realloc(returnResult, sizeof(char**) * (*returnSize + 1)); //根據returnSize確認目前有多少群組，+1增長
            returnResult[lastGroupIndex] = malloc(sizeof(char*) * 1);
            returnResult[lastGroupIndex][0] = pairs[i].original;

            (*returnSize)++;
            *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int) * (*returnSize)); //根據returnSize確認要增長"至"多少
            (*returnColumnSizes)[lastGroupIndex] = 1;


        }
        else
            //Case 2: 新增到已有的最後一個群組(group)
            //因為已經排序好了 所以肯定是直接新增到最後一個群組 故用lastGroupIndex
        {
            int lastGroupIndex = *returnSize - 1; //-1是因為 例如有5個陣列，但是最後一個陣列的旗標其實是[4] 故-1，上面case1不用-1是因為他本來就是要新增的

            int lastGroupSize = (*returnColumnSizes)[lastGroupIndex]; //拿取該陣列的大小

            //根據此陣列的大小將該陣列增長一個空間
            returnResult[lastGroupIndex] = realloc(returnResult[lastGroupIndex], sizeof(char*) * (lastGroupSize + 1));
            //接著放入即可
            returnResult[lastGroupIndex][lastGroupSize] = pairs[i].original;
            //記得更新在ColumSizes紀錄的該陣列的元素個數，不需要更新returnSize，因為並沒有動到群組個數
            (*returnColumnSizes)[lastGroupIndex] = lastGroupSize + 1;
        }

    }

    return returnResult;


    /*
        // 目前的情況: returnResult: [], *returnSize: 0;

        //當pairs遇到第一對 bat, abt時 以下狀態要變化成
        // returnResult : [["bat"]] , *returnSize: 1 (大小), *returnColumnSizes: [1] (每個群組有多少個)

        //故接下來可以先建立二層、一層，建造原理可見最下方展示的程式
        returnResult = malloc(sizeof(char**)*1);
        returnResult[0] = malloc(sizeof(char*)*1);
        returnResult[0][0] = pairs[0].original; //"bat"

        *returnSize = 1;

        //此陣列也要建立
        *returnColumnSizes = malloc(sizeof(int)*1);
        (*returnColumnSizes)[0] = 1;


    */

    /* 這是一個展示如何回傳的程式
        //如同第4點所說 用malloc來建立要回傳的char***陣列
        char *** returnResult = malloc(sizeof(char**)*3);
        //注意上面只建立了3個可以放置char**指標的空間，故還要再為char*指標分配空間
        returnResult[0] = malloc(sizeof(char*)*3); //例如[0]要可放置3個char*指標
        returnResult[1] = malloc(sizeof(char*)*2);
        returnResult[2] = malloc(sizeof(char*)*1);

         //建立字元的儲存空間 +1是因為字元陣列要以\0結尾
        returnResult[0][0] = malloc(sizeof(char)*(strlen("ate") + 1 ));

        strcpy(returnResult[0][0], "ate");

        returnResult[0][1] = malloc(sizeof(char)*(strlen("ate") + 1 ));
        strcpy(returnResult[0][1], "eat");

        returnResult[0][2] = malloc(sizeof(char)*(strlen("ate") + 1 ));
        strcpy(returnResult[0][2], "tea");

        returnResult[1][0] = malloc(sizeof(char)*(strlen("ate") + 1 ));
        strcpy(returnResult[1][0], "nat");

        returnResult[1][1] = malloc(sizeof(char)*(strlen("ate") + 1 ));
        strcpy(returnResult[1][1], "tan");

        returnResult[2][0] = malloc(sizeof(char)*(strlen("ate") + 1 ));
        strcpy(returnResult[2][0], "bat");


        //由於題目上面有說 除了returnResult要回傳之外 還有以傳址呼叫傳進來的returnSize 以及 returnColumnSize也要回傳 故在此做更動即可

        //1.returnSize只是位址 故要用*才是值
        *returnSize = 3;
        //2.告知系統列大小  同上 returnColumnSizes只是位址 故藥用*才是值
        *returnColumnSizes = malloc(sizeof(int)*3);
        (*returnColumnSizes)[0] = 3 ;
        (*returnColumnSizes)[1] = 2 ;
        (*returnColumnSizes)[2] = 1 ;

        return returnResult;
    */
}