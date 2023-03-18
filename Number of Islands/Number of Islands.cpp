/*
給一個二維陣列，1代表土地、0代表水，島會被水包圍，可以假設邊緣都是水，輸出島的個數
gridColSize 代表有幾行，gridSize代表有幾列

直覺:怎麼找島嶼? 一次找一座 找完將他們刪除變回0
可以用兩層for迴圈，每當碰到一個1，那麼就用X取代他，接著再進入一個兩層迴圈
開始掃描屬於這個1的島嶼，從他開始掃描上下左右，如果也是1那麼一樣將他們用X取代
從左上掃描到右下即可，
最後清除可用別的符號或是0都可以


問題: 怎麼偵測第二座島? 第二座島明顯不能在屬於第一座島魚的迴圈中做處理
解:觀察可知，不需特別做處理，因為我們是從一個x展開的，只有當一個值是1，然後他上下左右有X時才會也變成X
而第二、三座島的周圍都被0包圍了 故不會有X存在，即便掃描到1也不會變成X





*/

char NEW = 'X';
char WATER = '0';
char LAND = '1';
char USED = 'O';

void floodFill(char** grid, int number_of_rows, int number_of_cols, int i, int j) {
    //只要超出邊界，以及偵測到水便結束遞迴
    if (i < 0 || j < 0 || i >= number_of_rows || j >= number_of_cols || grid[i][j] != LAND)
    {
        return;
    }
    grid[i][j] = NEW;
    floodFill(grid, number_of_rows, number_of_cols, i + 1, j);
    floodFill(grid, number_of_rows, number_of_cols, i - 1, j);
    floodFill(grid, number_of_rows, number_of_cols, i, j + 1);
    floodFill(grid, number_of_rows, number_of_cols, i, j - 1);
}
int numIslands(char** grid, int gridSize, int* gridColSize) {

    if (gridSize == 0) return 0;

    int number_of_rows = gridSize;
    int number_of_cols = gridColSize[0];

    int numberOfIslands = 0;
    for (int i = 0; i < number_of_rows; i++)
    {
        for (int j = 0; j < number_of_cols; j++)
        {
            if (grid[i][j] == LAND)
            {
                floodFill(grid, number_of_rows, number_of_cols, i, j);
                for (int y = 0; y < number_of_rows; y++)
                {
                    for (int x = 0; x < number_of_cols; x++)
                    {
                        if (grid[y][x] == NEW)
                        {
                            grid[y][x] = USED;
                        }
                    }
                }
                numberOfIslands++;
            }
        }
    }
    return numberOfIslands;
}