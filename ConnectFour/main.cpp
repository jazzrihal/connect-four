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
    virtual string GetName() = 0;
    virtual void Play() = 0;
};

class ConnectFour : public Game {
    const string name = "Connect Four";

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
        cout << endl;
        
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
    
    string GetName() override {
        return name;
    }
    
    void Play() override {
        cout << "0 Quit | 1-" << height << " Drop Token" << endl;

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
        for (int j = 0; j < width; j++)
            cout << j + 1 << " ";
        
        cout << endl;
        
        // Print board in its current state
        for (int i = 0; i < height; i++) {
            
            for (int j = 0; j < width; j++) {
                
                SlotState state = board[i][j];
                
                switch (state)
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
        
        // Find first BLANK slot in column to place current player's token
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
            
            string rowOfTokens;

            for (int j = 0; j < width; j++) {
                
                SlotState slot = board[i][j];
                AppendTokenToString(slot, rowOfTokens);
            }
            VerifyConnectFour(rowOfTokens);
        }
        
        // Check for win vertically
        for (int j = 0; j < width; j++) {
            
            string columnOfTokens;
            
            for (int i = 0; i < height; i++) {
                
                SlotState slot = board[i][j];
                AppendTokenToString(slot, columnOfTokens);
            }
            VerifyConnectFour(columnOfTokens);
        }
        
        // Check for win diagonally upwards (left to right)
        // Start at first slot of each row
        for (int i = 3; i < height; i++) {
            
            string lineOfTokens;
            
            for (int j = 0; j <= i; j++) {
                
//                cout << "[" << i - j << "][" << j << "]" << endl;
                SlotState slot = board[i - j][j];
                AppendTokenToString(slot, lineOfTokens);
            }
            VerifyConnectFour(lineOfTokens);
        }
        
        // Start at last slot of each column
        for (int j = 1; j < width - 3; j++) {
            
            string lineOfTokens;
            
            for (int i = 0; i < width - j; i++) {
                
//                cout << "[" << height - 1 - i << "][" << j + i << "]" << endl;
                SlotState slot = board[height - 1 - i][j + i];
                AppendTokenToString(slot, lineOfTokens);
            }
            VerifyConnectFour(lineOfTokens);
        }
        
        // Check for win diagonally downwards (left to right)
        // Start at first slot of each row
        for (int i = 0; i < height - 3; i++) {
            
            string lineOfTokens;
            
            for (int j = 0; j < width - i; j++) {
                
                SlotState slot = board[i + j][j];
                AppendTokenToString(slot, lineOfTokens);
            }
            VerifyConnectFour(lineOfTokens);
        }
        
        // Start at last slot of each column
        for (int j = 1; j < width - 3; j++) {
            
            string lineOfTokens;
            
            for (int i = 0; i < height - j; i++) {
                
                SlotState slot = board[i][j + i];
                AppendTokenToString(slot, lineOfTokens);
            }
            VerifyConnectFour(lineOfTokens);
        }
    }
    
    void VerifyConnectFour(const string &tokens) {
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
    
    void AppendTokenToString(const SlotState token, string &lineOfTokens) {
        if (token == PLAYER_1)
            lineOfTokens.append("+");
        
        else if (token == PLAYER_2)
            lineOfTokens.append("x");
        
        else
            lineOfTokens.append("_");
    }
};

int main() {
    Game *game = new ConnectFour();
    cout << "Welcome to " << game->GetName() << "!" << endl;

    game->Play();
    
    delete game;
    return 0;
}
