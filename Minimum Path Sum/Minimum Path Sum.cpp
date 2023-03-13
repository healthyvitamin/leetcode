/*
給一個二維陣列，找到左上角走到右下最短的路徑(即走的路的值的合最小) 每次只能往右跟往下走
    gird[0][0] => ,,, => grid[2][2] 中間有兩個選擇 gird[row+1][col] 或是 grid[row][col+1]
明顯我們可以用遞迴的方式找到所有可能的值
那麼就要創立一個function minPartialPathSum(int ** grid, int row, int col)
表示到達這個gire[row0][col]所花的最小值
那麼遞迴怎麼跑?
我們可以用 目前的值 + 從左上角到達上一格/左一格所花的最小值
來找到所有可能的值，因此起始會是在最右下角，樹會一直擴展到最左上角grid[0][0]時return

int minPartialPathSum(int ** grid, int row, int col){
    if(row == 0 && col == 0)
        return grid[0][0];

    int min = INT_MAX;


    if(row -1 > = 0){ //如果目前gird[row][col]在第一排 因為沒有上一排故不可能從上來，故要判斷
        int upMin = minPartialPathSum(grid, row-1, col);
        if(upMin < min){
            min = upMin;
        }
    }

    if(col -1 > = 0){ //如果目前gird[row][col]在最左邊 因為沒有左邊故不可能從左來，故要判斷
        int leftMin = minPartialPathSum(grid, row, col-1);
        if(leftMin < min){
            min = leftMin;
        }
    }
    return min + gird[row][col];
}
*/
/*
但是上面會TLE，因為老問題，遞迴會重複運算到可能的情況
故創建一個cache二維陣列 去儲存運算過的值
同Valid Parenthesis String那題，要初始化並創建陣列
需要使用calloc

接著在在遞迴function前面先檢查目前這個值是否有計算過了

int minPartialPathSum(int ** grid, int row, int col){
    if(row == 0 && col == 0)
        return grid[0][0];

    if(cache[row][col] != 0 ){
        return cache[row][col];
    }

    int min = INT_MAX;


    if(row -1 > = 0){ //如果目前gird[row][col]在第一排 因為沒有上一排故不可能從上來，故要判斷
        int upMin = minPartialPathSum(grid, row-1, col);
        if(upMin < min){
            min = upMin;
        }
    }

    if(col -1 > = 0){ //如果目前gird[row][col]在最左邊 因為沒有左邊故不可能從左來，故要判斷
        int leftMin = minPartialPathSum(grid, row, col-1);
        if(leftMin < min){
            min = leftMin;
        }
    }
    cache[row][col] = min + grid[row][col];
    return cache[row][col];

}
int minPathSum(int** grid, int gridSize, int* gridColSize){
    int M = gridSize;
    int N = gridColSize[0];

    int ** cache = malloc(sizeof(int *) *M);
    for(int i = 0 ; i <M; i++)
    {
        cache[i] = calloc(N, sizeof(int));
    }
    int result = minPartialPathSum(gird, M-1, N-1, cache);
    for(int i = 0; i< M; i++){
        free(cache[i]);
    }
    free(cache);

    return result;
}
*/
int minPartialPathSum(int** grid, int row, int col, int** cache) {
    if (row == 0 && col == 0)
        return grid[0][0];

    if (cache[row][col] != 0) {
        return cache[row][col];
    }

    int min = INT_MAX;


    if (row - 1 >= 0) { //如果目前gird[row][col]在第一排 因為沒有上一排故不可能從上來，故要判斷
        int upMin = minPartialPathSum(grid, row - 1, col, cache);
        if (upMin < min) {
            min = upMin;
        }
    }

    if (col - 1 >= 0) { //如果目前gird[row][col]在最左邊 因為沒有左邊故不可能從左來，故要判斷
        int leftMin = minPartialPathSum(grid, row, col - 1, cache);
        if (leftMin < min) {
            min = leftMin;
        }
    }
    cache[row][col] = min + grid[row][col];
    return cache[row][col];

}
int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int M = gridSize;
    int N = gridColSize[0];

    int** cache = malloc(sizeof(int*) * M);
    for (int i = 0; i < M; i++)
    {
        cache[i] = calloc(N, sizeof(int));
    }
    int result = minPartialPathSum(grid, M - 1, N - 1, cache);
    for (int i = 0; i < M; i++) {
        free(cache[i]);
    }
    free(cache);

    return result;
}

/*師解 用兩層迴圈去遍歷
因為從上面遞迴方式可以知道 想知道grid[row][col]的值 只要知道上面的值跟左邊的值就可以了
那麼從左到右依序往下計算，便可以得到答案

*/