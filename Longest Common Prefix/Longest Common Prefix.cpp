/*
題目:給一個字串陣列，找出每個字串之間最大的相同子字串

直覺法: 由於這個公共字串，是所有字串都要有的
也就是說其實只要把第一個字串去比對其他字串就好了 最大的相同子字串就在第一個字串裡頭，

比對部分可以使用while，如此一來就不需要去數陣列的長度了


*/




char* longestCommonPrefix(char** strs, int strsSize) {

    if (strsSize <= 0)
    {
        return "";
    }
    //我們稱呼temp為比對字串
    char* temp;
    temp = strs[0];

    //開始比對新的字串
    for (int i = 1; i < strsSize; i++)
    {
        int j = 0;

        //如果目前字元存在、且被比對字串的目前字元也存在、且兩者相同
        while (temp[j] && strs[i][j] && temp[j] == strs[i][j])
        {
            j++;
        }
        //最後用\0結尾，每個字元陣列都要有
        temp[j] = '\0';
    }


    return temp;
}