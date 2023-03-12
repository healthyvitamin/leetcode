
/*
題目:給一個字串，括號全部都要成對且順序也要對才能為true，字串中會有星號* 可以表示左右括號以及空白

直覺作法: 找成對的
從第一個字開始找 如果一開始是右括號就return 因為順序不對接下來一定都錯
如果一開始是左括號才繼續，再剩下的長度中尋找是否有右括號可以匹配
但是會有一個問題，例如 ((((()()))))  明顯第一個右括號n不會是第一個左括號m的，k才是匹配的
                     m    n     k
那麼如何找到匹配的 "怎麼判斷?"
根據觀察可以發現 如果k是匹配的，則 s[m+1]~s[k-1] 都必須是已經匹配的了
因此右括號n同理， 如果他左右兩邊都是已經匹配的了
左邊(m+1~n-1) 右邊(n+1~strlen-1)
，那麼n就是跟當前m匹配的右括號了
故明顯可以看出是"遞迴"
bool checkValidSubstring(char *s, int i, int j)
{
    if(s[i] == ')')
    {
        return false;
    } else if (s[i] == '('){
        for(int k = 0; k <= j; k++)
        {
            if(s[k] == ')'){
                if(checkValidSubstring(s, i+1, k-1)&& checkValidSubstring(s, k+1, j)){
                    return true;
                }
            }
        }
    } else { // 星號*的時候

    }
}

bool checkValidString(char * s){

    return checkValidSubstring(s, 0, strlen(s)-1);

}

-------------------------但是有星號*------------------
}
*/

/*
bool checkValidSubstring(char *s, int i, int j)
{
    if(i > j) return true; //如果跑到最後面全空，全空相當於匹配故返回true
    if(s[i] == ')')
    {
        return false;
    } else if (s[i] == '*'){ //將星號當空格使用 那麼就問接下來的是不是都匹配即可
    問題: 那如果題目是**))怎麼辦? 如果當空格則右邊兩個右括號明顯無法匹配
    不用擔心 因為這邊是合法才return，如果不合法會繼續做下面的事，"將星號當作左括號看待"
        if(checkValidSubstring(s, i+1, j))
        {
            return true;
        }
    }
    //如果不是右括號，*號也不能當作空格看待，代表一定是左括號或代表左括號的*號
    for(int k = i+1; k <= j; k++){
        if(s[k] == ')' || s[k] == '*'){
            if(checkValidSubstring(s, i+1, k-1)&& checkValidSubstring(s, k+1, j)){
                return true;
                }
            }
        }
    //如果不是左右括號，也不是*號，
    return false;
}

bool checkValidString(char * s){

    return checkValidSubstring(s, 0, strlen(s)-1);

}
*/
//但是會TLE-----------------------------
/*
觀察明顯可以知道 是因為遞迴可能會重複運算
故要設計一個陣列，儲存結果
checkValidSubstring 是你給他一個範圍 i 到 j 回應是不是合法的(全都匹配)
那我們就用一個陣列[i][j]儲存
值為0 : 還沒算過， 1 : 算過且是true， -1 : 算過且是false

*/
bool checkValidSubstring(char* s, int i, int j, int** cache)
{
    if (i > j) return true; //如果跑到最後面全空，全空相當於匹配故返回true

    if (cache[i][j] != 0)
    {
        if (cache[i][j] == 1)
        {
            return true;
        }
        if (cache[i][j] == -1)
        {
            return false;
        }
    }


    if (s[i] == ')')
    {
        cache[i][j] = -1;
        return false;
    }
    else if (s[i] == '*') { //將星號當空格使用 那麼就問接下來的是不是都匹配即可
 /*
 問題: 那如果題目是**))怎麼辦? 如果當空格則右邊兩個右括號明顯無法匹配
 不用擔心 因為這邊是合法才return，如果不合法會繼續做下面的事，"將星號當作左括號看待"
 */
        if (checkValidSubstring(s, i + 1, j, cache))
        {
            cache[i][j] = 1;
            return true;
        }
    }
    //如果不是右括號，*號也不能當作空格看待，代表一定是左括號或代表左括號的*號
    for (int k = i + 1; k <= j; k++) {
        if (s[k] == ')' || s[k] == '*') {
            if (checkValidSubstring(s, i + 1, k - 1, cache) && checkValidSubstring(s, k + 1, j, cache)) {
                cache[i][j] = 1;
                return true;
            }
        }
    }

    //如果不是左右括號，也不是*號，
    cache[i][j] = -1;
    return false;
}

bool checkValidString(char* s) {
    int len = strlen(s);
    //先建立一個用來指向陣列指標的指標  用指標創建是因為這個陣列是需要在遞迴中傳遞的
    int** cache = malloc(sizeof(int*) * len);
    //接著為每一個陣列指標，所要儲存的陣列做malloc，同時我們想要預設為0，故用calloc
    //如此才創立好一個[len][len]的陣列
    for (int i = 0; i < len; i++)
    {
        cache[i] = calloc(len, sizeof(int));
    }
    return checkValidSubstring(s, 0, strlen(s) - 1, cache);

}

/*另法，用堆疊，可以見資料結構，對於運算子優先順序怎麼用堆疊實作的章節

師解:可以更精簡，直接計算左右括號的個數，只要注意")("的情況即可，也就是一開始計數會變成"負數" 就代表不匹配了
如果是星號，那麼他可以當左括號或右括號，故會產生兩種可能
因此這邊我們用minCount與maxCount做一個範圍的表示
只要在這個範圍內那麼

*/
/*
bool checkValidString(char * s){
    int minCount = 0; //最少有幾個'('
    int maxCount = 0; //最多有幾個'('
    for(int i = 0'; i < strlen(s); i++)
    {
        if(s[i] == '('){
            minCount++;
            maxCounr++
        } else if (s[i] == ')'){
            minCount--;
            maxCount--;
        }else if (s[i] == '*') //
        {
            minCount--;
            maxCount++;
        }
        if( maxCount < 0 ){ //如果minCount跟maxCount都<0，則代表右括號比較多 故return false 不匹配
            return false;
        }
        if (minCount < 0 ){
            只有當右括號太多 或 *號當右括號太多時才會進入負數， 原本右括號太多已經在上面篩選掉了
            故這邊是把*號當右括號的部分做歸0的動作，因為*號當右括號如果是-1
            就相當於第一個值就是右括號，那當然沒有意義。 故歸0
            minCount = 0;
        }
        //只有當mincount為0時代表左右括號剛好匹配
        return mincount == 0;
    }
}
*/