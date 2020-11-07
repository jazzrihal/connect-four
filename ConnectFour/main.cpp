//
//  main.cpp
//  ConnectFour
//
//  Created by Jazz Rihal on 07/11/2020.
//

#include <iostream>
using namespace std;

enum SlotState {
    BLANK,
    PLAYER_1,
    PLAYER_2
};

void SetupBoard();
void DrawBoard();
int GetInput();

int main () {
    cout << "Welcome to Connect Four!" << endl;
    
    // Setup board
    int height = 4;
    int width = 4;
    
    SlotState **board;
    board = new SlotState*[height];
    for (int i = 0; i < height; i++)
        board[i] = new SlotState[width];
    
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = BLANK;
    
    // Display board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SlotState state = board[i][j];
            switch (state)
            {
            case BLANK:     cout << "_ ";   break;
            case PLAYER_1:  cout << "+ ";   break;
            case PLAYER_2:  cout << "x ";   break;
            default:        cout << "E";    break;
            }
        }
        cout << endl;
    }
    
    // Deallocate memory
    for (int i = 0; i < height; i++)
        delete board[i];
    delete board;
    
    return 0;
}
