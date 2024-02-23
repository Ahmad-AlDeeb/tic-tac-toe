#include <iostream>
#include <map>
#include <limits>
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
void fill_grid(int row, int col);
bool get_status();
void display_results();
void play_again();
void lowercase_word(string word);
void refresh();


int main() {
    init_game();
    start_game();
}

void init_game() {
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
        for(int j{}; j<grid_cols; j+=2) {
            if(j%4) grid[i][j] = ' ';
            else    grid[i][j] = '|';
        }
}

void refresh() {
//    clear_console();
    display_scores();
    render_grid();
}

void clear_console() {}

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
//        fill_grid(row, col);

//        end_game = get_status();
//        if(end_game)
//            display_results();
    }
}

void get_move(int &row, int &col) {
    char player = get_player();
    cout << "Player " << player << " turn" << endl;

    cout << "Enter the row number: ";
    cin >> row;
    cout << "Enter the column number: ";
    cin >> col;
    validate_input(row, col);

    turns++;
}

void validate_input(int &row, int &col) {
    while(!check_number(row, col) || !check_cell(row, col)) {
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












