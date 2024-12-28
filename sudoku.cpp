#include <iostream>
#include <windows.h>
#include <cstdlib>//可使用rand 
#include <ctime>//可使用rand 

using namespace std;

int boards[2][9][9] = {
    {
        {0, 5, 0, 0, 0, 1, 4, 0, 0},
        {2, 0, 3, 0, 0, 0, 7, 0, 0},
        {0, 7, 0, 3, 0, 0, 1, 8, 2},
        {0, 0, 4, 0, 5, 0, 0, 0, 7},
        {0, 0, 0, 1, 0, 3, 0, 0, 0},
        {8, 0, 0, 0, 2, 0, 6, 0, 0},
        {1, 8, 5, 0, 0, 6, 0, 9, 0},
        {0, 0, 2, 0, 0, 0, 8, 0, 3},
        {0, 0, 6, 4, 0, 0, 0, 7, 0},//第一組可能的棋盤 
    },
    {
        {0, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},//第二組可能的棋盤
    }
};
int answers[2][9][9] = {
    {
        {6, 5, 8, 2, 7, 1, 4, 3, 9},
        {2, 1, 3, 8, 9, 4, 7, 5, 6},
        {4, 7, 9, 3, 6, 5, 1, 8, 2},
        {9, 2, 4, 6, 5, 8, 3, 1, 7},
        {5, 6, 7, 1, 4, 3, 9, 2, 8},
        {8, 3, 1, 9, 2, 7, 6, 4, 5},
        {1, 8, 5, 7, 3, 6, 2, 9, 4},
        {7, 4, 2, 5, 1, 9, 8, 6, 3},
        {3, 9, 6, 4, 8, 2, 5, 7, 1},//第一組棋盤的答案 
    },
    {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9},//第二組棋盤的答案 
    }
};
int board[9][9]; //棋盤為9*9大小 
int answer[9][9];
bool editable[9][9];//可供編輯的位置 

int cur_r = 0, cur_c = 0;//當前光標所在位置 

void fill_number(char c)
{
    /* TODO: Fill a number in to the cell the cursor is now pointing to.
            After fill in the number, check the horizontal line, the
            vertical line and the block the cell is in.
     */
	// fill in the number
	
		if(c=='0') board[cur_r][cur_c]=0;
  		else if(c=='1') board[cur_r][cur_c]=1;
    	else if(c=='2') board[cur_r][cur_c]=2;
    	else if(c=='3') board[cur_r][cur_c]=3;
    	else if(c=='4') board[cur_r][cur_c]=4;
    	else if(c=='5') board[cur_r][cur_c]=5;
    	else if(c=='6') board[cur_r][cur_c]=6;
		else if(c=='7') board[cur_r][cur_c]=7;
    	else if(c=='8') board[cur_r][cur_c]=8;
    	else if(c=='9') board[cur_r][cur_c]=9;
}

void move_cursor(char c)
{
    /* TODO: Move the cursor up, down, to the left or to the right.
             Remember to check if the cursor is moving out of bound.
    */
    //光標移動+檢查是否超過邊界+跳過不可更動的位置
	 
    int next_r=cur_r,next_c=cur_c;  
    while(true){ //若不可更動且未超過邊界則繼續執行 
    	if(c=='W' || c=='w'){//若傳入值是w or W，則向上移動一格 
    		if(next_r>0) next_r--;//假設當前位置不是在某列的第一行(next_r==0)，則由當前位置往上一格 
    		else break; //反之不移動，否則超過邊界 
		}
		else if(c=='S' || c=='s'){//若傳入值是s or S，則向下移動一格 
    		if(next_r<8) next_r++;//假設當前位置不是在某列的第九行(next_r==8)，則由當前位置往下一格
    		else break;
		}
		else if(c=='A' || c=='a'){//若傳入值是a or A，則向左移動一格 
    		if(next_c>0) next_c--;//假設當前位置不是在某行的第一列(next_C==0)，則由當前位置往左一格
    		else break;
		}
		else{  //若傳入值是d or D，則向右移動一格 
    		if(next_c<8) next_c++;
    		else break;//假設當前位置不是在某行的第九列(next_C==8)，則由當前位置往右一格
		}
		if(editable[next_r][next_c]){ //確認新位置是否可更動 
			cur_r=next_r;//則光標移動到目前位置 
			cur_c=next_c;
			break; //while editable
		}//如果剛好移動到不可編輯處，則再執行while迴圈，跳到指定方向的下一格 
	}
	
}

bool is_invalid(int i, int j)
{
    /* TODO: Check if board[i][j] is in a line that has conflict numbers. */
    // check horizontal
    for (int c1=0; c1<9; ++c1){
        for (int c2=c1+1; c2<9; ++c2){
            if (board[i][c1]  && board[i][c1] == board[i][c2])//如果現在檢查到的位置非0且等於該位置右邊的某數 
                return true; //有重複
        }
    }

    // check vertical 
    for (int r1=0; r1<9; ++r1){
        for (int r2=r1+1; r2<9; ++r2){
            if (board[r1][j]  && board[r1][j] == board[r2][j])//如果現在檢查到的位置非0且等於該位置下面列的某數 
                return true; //有重複
        }
    }

    // check block
    int row = (i / 3) * 3; // 區塊起始行:0,3,6 
    int col = (j / 3) * 3; // 區塊起始列:0,3,6
    //用board[r1][c1]和board[r2][c2] 比 
    for (int r1=row; r1<row+3; ++r1){//row+3==區塊行邊界 的下一個 
        for (int c1=col; c1<col+3; ++c1){//col+3==區塊列邊界 的下一個 
            for (int r2=row; r2<row+3; ++r2){
                for (int c2=col; c2<col+3; ++c2){
                    if ((r1 != r2 || c1 != c2) && board[r1][c1] && board[r1][c1] == board[r2][c2])
                    //如果board[r1][c1],board[r2][c2]不是同個位置且非零， 又值相同 
                        return true; //有重複
                }
            }
        }
    }

    return false; // no conflict

}

bool is_done(int i, int j)
{	
    /* TODO: Check if board[i][j] is in a line that has finished. */
    bool used[10];
    for(int k=1;k<10;++k) used[k]=false; //初始化，所有數值尚未出現過 
    // check horizontal
    bool horizontal=true;
    for (int c1=0; c1<9; ++c1){  
     	if (!board[i][c1] || used[board[i][c1]]) {
		 /*如果目前該列的c1位置上是0(!board[i][c1]是true)或在該列有重複的值*/
            horizontal=false;
            break;
        }
        used[board[i][c1]]=true;//把該數值改為已出現過的狀態 
    }
    if(horizontal) return true;//該列沒有未完成填入的位置和重複的數值，該列done 
    
    for(int k=1;k<10;++k) used[k]=false; //初始化，每個值尚未出現過 
    // check vertical 
    bool vertical=true;
    for (int r1=0; r1<9; ++r1){	
    	if (!board[r1][j] || used[board[r1][j]]) {
    		 /*如果目前該行的r1位置上是0(!board[r1][j]是true)或在該行有重複的值*/
            vertical=false;
            break;
        }
        used[board[r1][j]]=true;
    }
    if(vertical) return true;
    
    for(int k=1;k<10;++k) used[k]=false; //初始化
    //check block
    bool block=true;
    int row = (i / 3) * 3; // 區塊起始行:0,3,6 
    int col = (j / 3) * 3; // 區塊起始列:0,3,6
    for (int r1=row; r1<row+3; ++r1){//列檢查3項 
    	for (int c1=col; c1<col+3; ++c1){//行檢查3項 
    		if(!board[r1][c1] || used[board[r1][c1]]){
    			/*如果目前位置上是0(!board[r1][c1]是true)或在該行有重複的值*/
    			block=false;
    			break;
			}
			used[board[r1][c1]]=true;
		}
	} 
	if(block) return true;
    
    return false; //has not finished 
}

bool check_win()
{
    /* TODO: Check if the game is set. That is, every cell is finished. */
    for(int i=0;i<9;++i){
    	for(int j=0;j<9;++j){
    		if(is_invalid(i,j))return false;//有填錯 
		}
	}
	for(int i=0;i<9;++i){
    	for(int j=0;j<9;++j){
    		if(!is_done(i,j)) return false;//還沒完成 
		}
	}
    return true;
}

bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');//若輸入指令符合上述其中一個，則回傳true 
}

bool is_filling_action(char c)
{
    return (c >= '0' && c <= '9');//若輸入字元的ASCII在0到9之間，回傳true 
}

string get_styled_text(string text, string style)
{
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";
        if (c == 'G')
            color = "32";
        if (c == 'E')
            color = "41";
        if (c == 'C')
            color = "106";
        if (c == 'B')
            font = ";1";
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}
void print_answer()
{
	for (int i = 0; i < 9; ++i)
    {
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        cout << "|";
        for (int j = 0; j < 9; ++j)
        {	
        	cout<<" "<<answer[i][j]<<" ";
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void print_board()
{
    // Flush the screen 重置 
    cout << "\x1b[2J\x1b[1;1H";

    // Print usage hint.
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << get_styled_text("      K: ", "B") << "answer" << endl;
    cout << endl;

    // Iterate through and print each cell.
    for (int i = 0; i < 9; ++i)
    {
        // Print horizontal divider.
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        // Print the first vertical divider in each line.
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            // Set text style based on the state of the cell.
            string style = "";

            // Set style for the cell the cursor pointing to.
            if (cur_r == i && cur_c == j)
                style = "C";//藍 
            // Set style for the cell in an invalid line.
            else if (is_invalid(i, j))
                style = "E";//紅 
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
                style = "G";//綠 

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";//初始棋盤上的值粗體 

            // Print the cell out in styled text.
            // If the content is 0, print a dot, else print the number.
            if (board[i][j] == 0)
                cout << get_styled_text(" · ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // Print the vertical divider for each block.
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void initialize()
{
	// 設置隨機種子
    srand(time(0));

    // 隨機選擇一個棋盤
    int selected_board = rand() % 2;

    // 複製選中的棋盤到 board
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j){
        	board[i][j] = boards[selected_board][i][j];
            answer[i][j] = answers[selected_board][i][j];
		}
    // Set up styled text for Windows.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // Mark editable cells
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            editable[i][j] = !board[i][j];//在board裡數值為0者，可供編輯 

    // Print the initial board out.
    print_board();
}

int main()
{
    char c;//輸入的值 
    bool action_ok;//輸入的指令有意義 

    initialize();
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))//確認這個指令是不是要移動光標的指令 
        {
            action_ok = true;
            move_cursor(c);//傳入:輸入的值 
        }

        if (is_filling_action(c))//確認這個指令是不是要填入數值的指令
        {
            action_ok = true;
            fill_number(c);
        }

        if (c == 'Q' || c == 'q')
            break;

        print_board();
        
        if(c=='K'|| c == 'k') {
        	action_ok = true;
        	print_answer();//輸入K or k可秀答案 
		}
		
        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }
        
        if (!action_ok)//傳入字元不符任何規定，則輸出傳入的是無效的 
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }

    return 0;
}
