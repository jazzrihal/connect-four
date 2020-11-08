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

void SetupBoard(int &height, int &width, SlotState **&board);
void DrawBoard(int &height, int &width, SlotState **&board);
void PlaceToken(int &height, int &width, SlotState **&board, SlotState &current_player);
void SwitchPlayer(SlotState &current_player);
void QuitGame(int & height, SlotState **&board);

int main () {
    cout << "Welcome to Connect Four!" << endl;
    
    // Setup game
    int height = 6;
    int width = 7;
    SlotState **board;
    SetupBoard(height, width, board);
    SlotState current_player = PLAYER_1;
    
    // Game loop
    DrawBoard(height, width, board);
    PlaceToken(height, width, board, current_player);
    
    QuitGame(height, board);
    return 0;
}

void SetupBoard(int &height, int &width, SlotState **&board) {
    board = new SlotState*[height];
    for (int i = 0; i < height; i++)
        board[i] = new SlotState[width];
    
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = BLANK;
    
}

void DrawBoard(int &height, int &width, SlotState **&board) {
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
}

void PlaceToken(int &height, int &width, SlotState **&board, SlotState &current_player) {
    int column;
    cin >> column;
    bool state_changed = false;
    
    for (int i = height - 1; i >= 0; i--) {
        while (!state_changed) {
            SlotState state = board[i][column - 1];
            switch (state)
            {
            case BLANK:
                    if (current_player == PLAYER_1) {
                        board[i][column] = PLAYER_1;
                        state_changed = true;
                        SwitchPlayer(current_player);
                    }
                    else {
                        board[i][column] = PLAYER_2;
                        state_changed = true;
                        SwitchPlayer(current_player);
                    }
                    break;
            case PLAYER_1:  break;
            case PLAYER_2:  break;
            default:        break;
            }
        }
    }
}

void SwitchPlayer(SlotState &current_player) {
    if (current_player == PLAYER_1) {
        current_player = PLAYER_2;
    } else {
        current_player = PLAYER_1;
    }
}

void QuitGame(int &height, SlotState **&board) {
    // Deallocate memory
    for (int i = 0; i < height; i++)
        delete board[i];
    delete board;
}
