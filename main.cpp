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
map<int,int> get_row_index;
map<int,int> get_col_index;

//////////// Functions prototypes ////////////
void init_game();
void start_game();
void clear_console();
void display_scores();
void build_grid();
void render_grid();
void get_move(int &row, int &col);
void validate_input(int &row, int &col);
void fill_grid(int row, int col, int turn);
bool get_status();
void display_results();
void play_again();
void lowercase_word(string word);
void refresh();

int main() {
    init_game();
//    start_game();
}

void init_game() {
    build_grid();
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















