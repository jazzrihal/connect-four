//
//  main.cpp
//  ConnectFour
//
//  Created by Jazz Rihal on 07/11/2020.
//

#include <iostream>
using namespace std;

class Game {
public:
    Game() {};
    virtual ~Game() {};
    virtual void Play() = 0;
};

class ConnectFour : public Game {
    enum SlotState {
        BLANK,
        PLAYER_1,
        PLAYER_2
    };
    
    int height, width;
    SlotState **board;
    SlotState current_player;
    int user_in;
    
public:
    ConnectFour() {
        cout << "Enter board height then width: " << endl;
        cin >> height;
        cin >> width;
        
        // Allocate memory
        board = new SlotState*[height];
        for (int i = 0; i < height; i++)
            board[i] = new SlotState[width];
        
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                board[i][j] = BLANK;
        
        // Prepare for first player
        current_player = PLAYER_1;
        user_in = 1;
    }
    
    ~ConnectFour() {
        // Deallocate memory
        for (int i = 0; i < height; i++)
            delete [] board[i];
        delete [] board;
    }
    
    void Play() override {
        while (user_in) {
            Draw();
            Input();
        }
    }
    
private:
    void Quit() {
        user_in = 0;
    }
    
    void Draw() {
        // Print column header
        cout << "0 Quit | 1-" << height << " Drop Token" << endl;
        
        for (int j = 0; j < width; j++)
            cout << j + 1 << " ";
        cout << endl;
        
        // Print board in its current state
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                SlotState state = board[i][j];
                switch (state)
                {
                    case    BLANK:      cout << "_ ";   break;
                    case    PLAYER_1:   cout << "+ ";   break;
                    case    PLAYER_2:   cout << "x ";   break;
                    default:            cout << "E";    break;
                }
            }
            cout << endl;
        }
        cout << endl;
        
        DetectWin();
    }

    void Input() {
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
    
    void PlaceToken(int column) {
        column--; // Offset input by 1 to align with desired column
        
        // Find first BLANK slot in column to place current player token
        for (int i = height - 1; i >= 0; i--) {
            SlotState current_state = board[i][column];
            if (current_state == BLANK) {
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
    
    void SwitchPlayer() {
        if (current_player == PLAYER_1) {
            current_player = PLAYER_2;
        } else {
            current_player = PLAYER_1;
        }
    }
    
    void DetectWin() {
        // Check for win horizontally
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width - 3; j++) {
                // Build string from snapshot of 4 consecutive tokens
                string fourTokens;
                
                for (int k = 0; k < 4; k++) {
                    SlotState slot = board[i][j + k];
                    
                    if (slot == PLAYER_1)
                        fourTokens.append("+");
                    else if (slot == PLAYER_2)
                        fourTokens.append("x");
                }
                
                VerifyConnectFour(fourTokens); // Compare snapshot with verification strings
            }
        }
        
        // Check for win vertically
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height - 3; j++) {
                // Build string from snapshot of 4 consecutive tokens
                string fourTokens;

                for (int k = 0; k < 4; k++) {
                    SlotState slot = board[j + k][i];

                    if (slot == PLAYER_1)
                        fourTokens.append("+");
                    else if (slot == PLAYER_2)
                        fourTokens.append("x");
                }

                VerifyConnectFour(fourTokens);
            }
        }
    }
    
    void VerifyConnectFour(string tokens) {
        // Win keys for players
        const string verifyPlayer1 = "++++";
        const string verifyPlayer2 = "xxxx";
        
        if (tokens == verifyPlayer1) {
            cout << "Player 1 wins!\n";
            Quit();
        } else if (tokens == verifyPlayer2) {
            cout << "Player 2 wins!\n";
            Quit();
        }
    }
};

int main() {
    cout << "Welcome to Connect Four!" << endl;
    Game *Game = new ConnectFour();
    Game->Play();
    delete Game;
    
    return 0;
}
