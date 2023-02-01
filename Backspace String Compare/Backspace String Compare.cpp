/*
題目:#號就是刪除鍵 刪除前一個字，如果s跟t刪除後是一樣的字串則回傳true
首先要注意C語言的字串陣列 結尾是\0
故index都是字串長度+1 因此用來儲存題目給的字串的字元陣列，宣告時的index便是此。

解題
1.首先是直覺的暴力法
    創建兩個新的字元陣列儲存題目給的字串，再來用一個旗標，控制當碰到#字號時，將前一個字刪除
    再來使用strcmp比對兩個字串即可。
另外如果把重複的程式寫成函數
要注意區域變數是不能回傳出來的
故要用new、malloc 用動態配置建立變數 並且程式結束前用free、delete釋放

2.直接在s、t上做操作也可以 不需要另外創建兩個字元陣列，這樣可以省略空間

*/
bool backspaceCompare(char* s, char* t) {

    int len_S = strlen(s);
    char result_S[len_S + 1];
    int j = 0; //旗標

    for (int i = 0; i < len_S; i++)
    {
        if (s[i] != '#')
        {
            result_S[j] = s[i];
            j++;
        }
        else {
            if (j > 0) //避免旗標倒退過頭至負數 當沒的刪除時就不用刪除了
            {
                j--;
                result_S[j] = '\0';
            }
        }
    }
    result_S[j] = '\0';

    //--------------------------------------

    int len_T = strlen(t);
    char result_T[len_T + 1];
    int k = 0; //旗標

    for (int i = 0; i < len_T; i++)
    {
        if (t[i] != '#')
        {
            result_T[k] = t[i];
            k++;
        }
        else {
            if (k > 0) //避免旗標倒退過頭至負數 當沒的刪除時就不用刪除了
            {
                k--;
                result_T[k] = '\0';
            }
        }
    }
    result_T[k] = '\0';

    printf("%s %s \n", result_S, result_T);
    return strcmp(result_S, result_T) == 0;
}