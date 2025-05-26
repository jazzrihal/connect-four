//
//  ConnectFour.cpp
//  ConnectFour
//
//  Created by Jazz Rihal on 22/01/2021.
//

#include "ConnectFour.hpp"

using namespace std;

ConnectFour::ConnectFour() {
    cout << "Welcome to Connect Four!" << endl;

    // Define board size
    cout << "Enter board size: " << endl;
    cin >> height;
    width = height;
    cout << endl;
    
    // Allocate memory
    board = new SlotState*[height];
    for (int i = 0; i < height; i++)
        board[i] = new SlotState[width];
    
    Reset();
}

ConnectFour::~ConnectFour() {
    // Deallocate memory
    for (int i = 0; i < height; i++)
        delete [] board[i];
    
    delete [] board;
}

// Main game loop
void ConnectFour::Play() {
    cout << "0 QUIT | 1-" << height << " DROP TOKEN" << endl << endl;

    while (user_in) {
        Draw();
        Input();
    }
}

void ConnectFour::Quit() {
    user_in = 0;
}

// Blank all slots and prepare for first player
void ConnectFour::Reset() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = BLANK;
    
    current_player = PLAYER_1;
    user_in = 1;
}

void ConnectFour::Draw() {
    // Print column header
    for (int j = 0; j < width; j++)
        cout << j + 1 << " ";
    
    cout << endl;
    
    // Print board in its current state
    for (int i = 0; i < height; i++) {
        
        for (int j = 0; j < width; j++) {
            
            SlotState slot = board[i][j];
            
            switch (slot)
            {
                case    PLAYER_1:   cout << "+ ";   break;
                case    PLAYER_2:   cout << "x ";   break;
                default:            cout << "_ ";   break;
            }
        }
        cout << endl;
    }
    cout << endl;
    
    DetectWin();
}

// Prompt current player to place token in column
void ConnectFour::Input() {
    if (user_in == 0)
        return;
    
    cout << "Player " << current_player << "'s turn!" << endl;
    cin >> user_in;
    cout << endl;
    
    if (user_in >= 0 && user_in <= width) {
        PlaceToken(user_in);
        
    } else {
        cout << "Enter number between 1 and " << width << endl;
    }
}

// Find first blank slot in chosen column to place token
void ConnectFour::PlaceToken(int column) {
    --column;
    
    for (int i = height - 1; i >= 0; i--) {
        
        SlotState slot = board[i][column];
        
        if (slot == BLANK) {
            
            if (current_player == PLAYER_1) {
                board[i][column] = PLAYER_1;
                break;
                
            } else {
                board[i][column] = PLAYER_2;
                break;
            }
        }
    }
    SwitchPlayer();
}

void ConnectFour::SwitchPlayer() {
    if (current_player == PLAYER_1) {
        current_player = PLAYER_2;
        
    } else {
        current_player = PLAYER_1;
    }
}

// Detect connect-four in any direction
void ConnectFour::DetectWin() {
    // Horizontal algorithm
    for (int i = 0; i < height; i++) {
        
        string rowOfTokens;

        for (int j = 0; j < width; j++) {
            
            SlotState slot = board[i][j];
            AppendTokenToString(slot, rowOfTokens);
        }
        VerifyConnectFour(rowOfTokens);
    }
    
    // Vertical algorithm
    for (int j = 0; j < width; j++) {
        
        string columnOfTokens;
        
        for (int i = 0; i < height; i++) {
            
            SlotState slot = board[i][j];
            AppendTokenToString(slot, columnOfTokens);
        }
        VerifyConnectFour(columnOfTokens);
    }
    
    // Upwards diagonal algorithm
    // 1 - Start at first slot of each row
    for (int i = 3; i < height; i++) {
        
        string lineOfTokens;
        
        for (int j = 0; j <= i; j++) {
            
//                cout << "[" << i - j << "][" << j << "]" << endl;
            SlotState slot = board[i - j][j];
            AppendTokenToString(slot, lineOfTokens);
        }
        VerifyConnectFour(lineOfTokens);
    }
    
    // 2 - Start at last slot of each column
    for (int j = 1; j < width - 3; j++) {
        
        string lineOfTokens;
        
        for (int i = 0; i < width - j; i++) {
            
//                cout << "[" << height - 1 - i << "][" << j + i << "]" << endl;
            SlotState slot = board[height - 1 - i][j + i];
            AppendTokenToString(slot, lineOfTokens);
        }
        VerifyConnectFour(lineOfTokens);
    }
    
    // Downwards diagonal algorithm
    // 1 - Start at first slot of each row
    for (int i = 0; i < height - 3; i++) {
        
        string lineOfTokens;
        
        for (int j = 0; j < width - i; j++) {
            
            SlotState slot = board[i + j][j];
            AppendTokenToString(slot, lineOfTokens);
        }
        VerifyConnectFour(lineOfTokens);
    }
    
    // 2 - Start at first slot of each column
    for (int j = 1; j < width - 3; j++) {
        
        string lineOfTokens;
        
        for (int i = 0; i < height - j; i++) {
            
            SlotState slot = board[i][j + i];
            AppendTokenToString(slot, lineOfTokens);
        }
        VerifyConnectFour(lineOfTokens);
    }
}

// Convert token and append to given string
void ConnectFour::AppendTokenToString(const SlotState token, string &lineOfTokens) {
    if (token == PLAYER_1)
        lineOfTokens.append("+");
    
    else if (token == PLAYER_2)
        lineOfTokens.append("x");
    
    else
        lineOfTokens.append("_");
}

// Find Connect Four in given line of tokens
void ConnectFour::VerifyConnectFour(const string &tokens) {
    // Win keys for players
    const string verifyPlayer1 = "++++";
    const string verifyPlayer2 = "xxxx";
    
    if (tokens.find(verifyPlayer1) != string::npos) {
        cout << "Player 1 wins!\n";
        Quit();
        
    } else if (tokens.find(verifyPlayer2) != string::npos) {
        cout << "Player 2 wins!\n";
        Quit();
    }
}
