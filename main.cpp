#include <iostream>
#include <map>
using namespace std;

//////////// Variables ////////////
const int grid_rows = 7;
const int grid_cols = 13;
char grid[grid_rows][grid_cols];
bool end_game {false};
int turns {0};
int player_O_score {0};
int player_X_score {0};
int winner;
map<int,int> row_i, col_i;

//////////// Functions prototypes ////////////
void init_game();
void start_game();
void clear_console();
void display_scores();
void build_grid();
void render_grid();
void get_move(int &row, int &col);
char get_player();
void validate_input(int &row, int &col);
bool check_cell(int row, int col);
bool check_number(int row, int col);
void mark_cell(int row, int col);
bool check_winning();
void display_winner();
void restart_game();
void refresh();

//////////////////////////////////////////
int main() {
    init_game();
    start_game();
}

void init_game() {
    clear_console();
    build_grid();

    // Build maps from user input to grid index
    row_i[1]=1, row_i[2]=3, row_i[3]=5;
    col_i[1]=2, col_i[2]=6, col_i[3]=10;

    refresh();
}
/*
-------------
|   |   |   |
-------------
|   |   |   |
-------------
|   |   |   |
-------------
 */
void build_grid() {
    // Inserting all dashes lines --> -------------
    for(int i{}; i<grid_rows; i+=2)
        for(int j{}; j<grid_cols; j++)
            grid[i][j] = '-';

    // Inserting all rows --> |   |   |   |
    for(int i{1}; i<grid_rows; i+=2)
        for(int j{}; j<grid_cols; j++) {
            if(j%4) grid[i][j] = ' ';
            else    grid[i][j] = '|';
        }
}

void refresh() {
    clear_console();
    display_scores();
    render_grid();
}

void clear_console() {
    system("cls");
}

void display_scores() {
    cout << "Player O Score: " << player_O_score << endl;
    cout << "Player X Score: " << player_X_score << endl;
}

void render_grid() {
    for(int i{}; i<grid_rows; i++) {
        for(int j{}; j<grid_cols; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

void start_game() {
    while(!end_game) {
        int row, col;
        get_move(row,col);
        mark_cell(row, col);

        end_game = check_winning();
        if(end_game) {
            display_winner();
            restart_game();
        }
    }
}

void get_move(int &row, int &col) {
    turns++;
    cout << "Player " << get_player() << " turn" << endl;

    cout << "Enter the row number: ";
    cin >> row;
    cout << "Enter the column number: ";
    cin >> col;
    validate_input(row, col);
}

void validate_input(int &row, int &col) {
    while(!check_number(row, col) || !check_cell(row, col)) {
        refresh();

        cout << "Player " << get_player() << " turn" << endl;
        if(!check_number(row, col))
            cout << "Error! Please enter valid numbers (1, 2, 3).\n";
        else if(!check_cell(row, col))
            cout << "Error! Cell is not empty, try another cell.\n";


        cout << "Enter the row number: ";
        cin >> row;
        cout << "Enter the column number: ";
        cin >> col;
    }
}

char get_player() {
    if(turns%2) return 'X';
    else        return 'O';
}

bool check_number(int row, int col) {
    if(row<1 || row>3 || col<1 || col>3)
        return false;
    else return true;
}

bool check_cell(int row, int col) {
    row = row_i[row];
    col = col_i[col];

    if(grid[row][col] == ' ')
        return true;
    else return false;
}

void mark_cell(int row, int col) {
    row = row_i[row];
    col = col_i[col];
    grid[row][col] = get_player();
    refresh();
}

bool check_winning() {
    char player = get_player();

    // Check horizontally
    for(int i{1}; i<=3; i++) {
        bool winning {true};
        for(int j{1}; j<=3; j++)
            if(grid[row_i[i]][col_i[j]] != player)
                winning = false;

        if(winning) {
            winner = turns%2;
            return true;
        }
    }
    // Check vertically
    for(int j{1}; j<=3; j++) {
        bool winning {true};
        for(int i{1}; i<=3; i++)
            if(grid[row_i[i]][col_i[j]] != player)
                winning = false;

        if(winning) {
            winner = turns%2;
            return true;
        }
    }
    // Check left diagonal
    if(grid[row_i[1]][col_i[1]] == player &&
       grid[row_i[2]][col_i[2]] == player &&
       grid[row_i[3]][col_i[3]] == player) {
        winner = turns%2;
        return true;
    }
    // Check right diagonal
    if(grid[row_i[1]][col_i[3]] == player &&
       grid[row_i[2]][col_i[2]] == player &&
       grid[row_i[3]][col_i[1]] == player) {
        winner = turns%2;
        return true;
    }

    // Check if game is not finished (check if there's empty cell)
    for(int i{1}; i<=3; i++)
        for(int j{1}; j<=3; j++)
            if(grid[row_i[i]][col_i[j]] == ' ')
                return false;

    // DRAW
    winner = -1;
    return true;
}

void display_winner() {
    cout << "======================================================\n";
    if(winner == 0) {
        cout << "============= The winner is player O :-) =============\n";
        player_O_score++;
    }
    else if(winner == 1) {
        cout << "============= The winner is player X ^_^ =============\n";
        player_X_score++;
    }
    else cout << "====================== DRAW :'( ======================\n";
    cout << "======================================================\n";
}

void restart_game() {
    cout << "Play again?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";
    cout << "Enter 1 to continue, or 2 to exit: ";

    int answer;
    cin >> answer;
    while(answer != 1 && answer != 2) {
        cout << "Error! Invalid choice, try again\n";
        cout << "Enter 1 to continue, or 2 to exit: ";
        cin >> answer;
    }
    // End game if answer is 2 (NO)
    if(answer == 2) return;


    // Remove O & X
    for(int i{}; i<grid_rows; i++)
        for(int j{}; j<grid_cols; j++)
            if(grid[i][j] == 'O' || grid[i][j] == 'X')
                grid[i][j] = ' ';
    end_game = false;
    refresh();
}






