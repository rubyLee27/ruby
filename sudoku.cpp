#include <iostream>
#include <windows.h>
#include <cstdlib>//�i�ϥ�rand 
#include <ctime>//�i�ϥ�rand 

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
        {0, 0, 6, 4, 0, 0, 0, 7, 0},//�Ĥ@�եi�઺�ѽL 
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
        {0, 0, 0, 0, 8, 0, 0, 7, 9},//�ĤG�եi�઺�ѽL
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
        {3, 9, 6, 4, 8, 2, 5, 7, 1},//�Ĥ@�մѽL������ 
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
        {3, 4, 5, 2, 8, 6, 1, 7, 9},//�ĤG�մѽL������ 
    }
};
int board[9][9]; //�ѽL��9*9�j�p 
int answer[9][9];
bool editable[9][9];//�i�ѽs�誺��m 

int cur_r = 0, cur_c = 0;//��e���ЩҦb��m 

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
    //���в���+�ˬd�O�_�W�L���+���L���i��ʪ���m
	 
    int next_r=cur_r,next_c=cur_c;  
    while(true){ //�Y���i��ʥB���W�L��ɫh�~����� 
    	if(c=='W' || c=='w'){//�Y�ǤJ�ȬOw or W�A�h�V�W���ʤ@�� 
    		if(next_r>0) next_r--;//���]��e��m���O�b�Y�C���Ĥ@��(next_r==0)�A�h�ѷ�e��m���W�@�� 
    		else break; //�Ϥ������ʡA�_�h�W�L��� 
		}
		else if(c=='S' || c=='s'){//�Y�ǤJ�ȬOs or S�A�h�V�U���ʤ@�� 
    		if(next_r<8) next_r++;//���]��e��m���O�b�Y�C���ĤE��(next_r==8)�A�h�ѷ�e��m���U�@��
    		else break;
		}
		else if(c=='A' || c=='a'){//�Y�ǤJ�ȬOa or A�A�h�V�����ʤ@�� 
    		if(next_c>0) next_c--;//���]��e��m���O�b�Y�檺�Ĥ@�C(next_C==0)�A�h�ѷ�e��m�����@��
    		else break;
		}
		else{  //�Y�ǤJ�ȬOd or D�A�h�V�k���ʤ@�� 
    		if(next_c<8) next_c++;
    		else break;//���]��e��m���O�b�Y�檺�ĤE�C(next_C==8)�A�h�ѷ�e��m���k�@��
		}
		if(editable[next_r][next_c]){ //�T�{�s��m�O�_�i��� 
			cur_r=next_r;//�h���в��ʨ�ثe��m 
			cur_c=next_c;
			break; //while editable
		}//�p�G��n���ʨ줣�i�s��B�A�h�A����while�j��A������w��V���U�@�� 
	}
	
}

bool is_invalid(int i, int j)
{
    /* TODO: Check if board[i][j] is in a line that has conflict numbers. */
    // check horizontal
    for (int c1=0; c1<9; ++c1){
        for (int c2=c1+1; c2<9; ++c2){
            if (board[i][c1]  && board[i][c1] == board[i][c2])//�p�G�{�b�ˬd�쪺��m�D0�B����Ӧ�m�k�䪺�Y�� 
                return true; //������
        }
    }

    // check vertical 
    for (int r1=0; r1<9; ++r1){
        for (int r2=r1+1; r2<9; ++r2){
            if (board[r1][j]  && board[r1][j] == board[r2][j])//�p�G�{�b�ˬd�쪺��m�D0�B����Ӧ�m�U���C���Y�� 
                return true; //������
        }
    }

    // check block
    int row = (i / 3) * 3; // �϶��_�l��:0,3,6 
    int col = (j / 3) * 3; // �϶��_�l�C:0,3,6
    //��board[r1][c1]�Mboard[r2][c2] �� 
    for (int r1=row; r1<row+3; ++r1){//row+3==�϶������ ���U�@�� 
        for (int c1=col; c1<col+3; ++c1){//col+3==�϶��C��� ���U�@�� 
            for (int r2=row; r2<row+3; ++r2){
                for (int c2=col; c2<col+3; ++c2){
                    if ((r1 != r2 || c1 != c2) && board[r1][c1] && board[r1][c1] == board[r2][c2])
                    //�p�Gboard[r1][c1],board[r2][c2]���O�P�Ӧ�m�B�D�s�A �S�ȬۦP 
                        return true; //������
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
    for(int k=1;k<10;++k) used[k]=false; //��l�ơA�Ҧ��ƭȩ|���X�{�L 
    // check horizontal
    bool horizontal=true;
    for (int c1=0; c1<9; ++c1){  
     	if (!board[i][c1] || used[board[i][c1]]) {
		 /*�p�G�ثe�ӦC��c1��m�W�O0(!board[i][c1]�Otrue)�Φb�ӦC�����ƪ���*/
            horizontal=false;
            break;
        }
        used[board[i][c1]]=true;//��Ӽƭȧאּ�w�X�{�L�����A 
    }
    if(horizontal) return true;//�ӦC�S����������J����m�M���ƪ��ƭȡA�ӦCdone 
    
    for(int k=1;k<10;++k) used[k]=false; //��l�ơA�C�ӭȩ|���X�{�L 
    // check vertical 
    bool vertical=true;
    for (int r1=0; r1<9; ++r1){	
    	if (!board[r1][j] || used[board[r1][j]]) {
    		 /*�p�G�ثe�Ӧ檺r1��m�W�O0(!board[r1][j]�Otrue)�Φb�Ӧ榳���ƪ���*/
            vertical=false;
            break;
        }
        used[board[r1][j]]=true;
    }
    if(vertical) return true;
    
    for(int k=1;k<10;++k) used[k]=false; //��l��
    //check block
    bool block=true;
    int row = (i / 3) * 3; // �϶��_�l��:0,3,6 
    int col = (j / 3) * 3; // �϶��_�l�C:0,3,6
    for (int r1=row; r1<row+3; ++r1){//�C�ˬd3�� 
    	for (int c1=col; c1<col+3; ++c1){//���ˬd3�� 
    		if(!board[r1][c1] || used[board[r1][c1]]){
    			/*�p�G�ثe��m�W�O0(!board[r1][c1]�Otrue)�Φb�Ӧ榳���ƪ���*/
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
    		if(is_invalid(i,j))return false;//����� 
		}
	}
	for(int i=0;i<9;++i){
    	for(int j=0;j<9;++j){
    		if(!is_done(i,j)) return false;//�٨S���� 
		}
	}
    return true;
}

bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');//�Y��J���O�ŦX�W�z�䤤�@�ӡA�h�^��true 
}

bool is_filling_action(char c)
{
    return (c >= '0' && c <= '9');//�Y��J�r����ASCII�b0��9�����A�^��true 
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
    // Flush the screen ���m 
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
                style = "C";//�� 
            // Set style for the cell in an invalid line.
            else if (is_invalid(i, j))
                style = "E";//�� 
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
                style = "G";//�� 

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";//��l�ѽL�W���Ȳ��� 

            // Print the cell out in styled text.
            // If the content is 0, print a dot, else print the number.
            if (board[i][j] == 0)
                cout << get_styled_text(" �P ", style);
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
	// �]�m�H���ؤl
    srand(time(0));

    // �H����ܤ@�ӴѽL
    int selected_board = rand() % 2;

    // �ƻs�襤���ѽL�� board
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
            editable[i][j] = !board[i][j];//�bboard�̼ƭȬ�0�̡A�i�ѽs�� 

    // Print the initial board out.
    print_board();
}

int main()
{
    char c;//��J���� 
    bool action_ok;//��J�����O���N�q 

    initialize();
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))//�T�{�o�ӫ��O�O���O�n���ʥ��Ъ����O 
        {
            action_ok = true;
            move_cursor(c);//�ǤJ:��J���� 
        }

        if (is_filling_action(c))//�T�{�o�ӫ��O�O���O�n��J�ƭȪ����O
        {
            action_ok = true;
            fill_number(c);
        }

        if (c == 'Q' || c == 'q')
            break;

        print_board();
        
        if(c=='K'|| c == 'k') {
        	action_ok = true;
        	print_answer();//��JK or k�i�q���� 
		}
		
        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }
        
        if (!action_ok)//�ǤJ�r�����ť���W�w�A�h��X�ǤJ���O�L�Ī� 
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }

    return 0;
}
