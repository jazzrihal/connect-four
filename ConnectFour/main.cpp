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
    int height = 6;
    int width = 7;
    
    SlotState **board;
    board = new SlotState*[height];
    for (int i = 0; i < height; i++)
        board[i] = new SlotState[width];
    
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = BLANK;
        
    // Display board
    for (int j = 0; j < width; j++)
        cout << j + 1 << " ";
    cout << endl;
    
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
    cout << endl;
    
    // Player input
    SlotState current_player = PLAYER_1;
    bool state_changed = false;
    
    int column;
    cin >> column;
    
    for (int i = height - 1; i >= 0; i--) {
        while (!state_changed) {
            SlotState state = board[i][column];
            switch (state)
            {
            case BLANK:
                    if (current_player == PLAYER_1) {
                        board[i][column] = PLAYER_1;
                        state_changed = true;
                        current_player = PLAYER_2;
                    }
                    else {
                        board[i][column] = PLAYER_2;
                        state_changed = true;
                        current_player = PLAYER_1;
                    }
                    break;
            case PLAYER_1:  break;
            case PLAYER_2:  break;
            default:        break;
            }
        }
    }
    
    // Deallocate memory
    for (int i = 0; i < height; i++)
        delete board[i];
    delete board;
    
    return 0;
}
