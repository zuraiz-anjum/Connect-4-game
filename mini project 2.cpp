
//Zuraiz Anjum BDS-1C 
//23l-2547

//Fardeen Mirza BDS-1C
//23L-2576




#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MaxRows = 14;
const int MaxCols = 14;
const int MaxPlayers = 2;
const char DefaultFill = '.';

// Arrays to store data
char Board[MaxRows][MaxCols];

//Array to keep track of next row in each column
//This will save us from searching for the next
// empty slot in each column
int Next_Move[MaxCols] = { 0 };

string PlayerNames[MaxPlayers];
char PlayerMarks[MaxPlayers] = { 'o', 'x' };

//Turning player represent the player making the move
int TurningPlayer = 0;

//Game End State represent the result of the game
// with -1 means game is not over
// 0 means the first player has won it
// and 1 means the second player is the winner
int GameEndState = 0;

// Number of rows to be used in this game
// Maximum value is MaxRows
int Rows = 6;

// Number of columns to be used in this game
// Maximum value is MaxCols
int Columns = 7;

// How many consecutive positions to win
int ConnectLimit = 4;

bool GameisOn() {
    return GameEndState == 0;
}

void ShowGame() {
    for (int c = 0; c < Columns; c++)
        cout << "_________";
    cout << endl;
    for (int c = 0; c < Columns; c++)
        cout << "\t" << c;
    cout << endl;
    for (int c = 0; c < Columns; c++)
        cout << "_________";

    cout << endl;

    for (int r = Rows - 1; r >= 0; r--) {
        cout << "| " << r << " |\t";
        for (int c = 0; c < Columns; c++)
            cout << Board[r][c] << "\t";
        cout << endl << "|   |" << endl;
    }

    for (int c = 0; c < Columns; c++)
        cout << "_________";
    cout << endl;

    if (GameisOn())
        cout << endl << "\tPlayer:" << PlayerNames[TurningPlayer]
        << "("
        << PlayerMarks[TurningPlayer] << ")"
        << " Moving " << endl;
}

bool CheckForWinner(int c) {
    for (int i = 0; i < Columns; i++) {

        for (int j = 0; j < Rows; j++) {

            if (Board[i][j] == 'x') {
                //up
                if (j + c < Columns) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i][j + k] == 'x')
                            w++;
                    if (w == c) {
                        return true;
                    }
                    w = 0;
                }
                //down
                if (j - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i][j - k] == 'x')
                            w++;
                    if (w == c) {
                        return true;
                    }
                    w = 0;

                }
                //right side
                if (i + c < Rows) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i + k][j] == 'x')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //left side
                if (i - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i - k][j] == 'x')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diagnal top right
                if (i + c < Rows && j + c < Columns) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i + k][j + k] == 'x')
                            w++;
                    if (w == c) {

                        return true;
                    }

                    w = 0;
                }
                //diagnal top left
                if (i - c >= 0 && j + c < Columns) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i - k][j + k] == 'x')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diagnal bottom right
                if (i + c < Rows && j - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i + k][j - k] == 'x')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diaganl bottom left
                if (i - c >= 0 && j - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i - k][j - k] == 'x')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
            }
            else if (Board[i][j] == 'o') {
                //up
                if (j + c < Columns) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i][j + k] == 'o')
                            w++;
                    if (w == c) {

                        return true;

                    }
                    w = 0;

                }
                //down
                if (j - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i][j - k] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //right side
                if (i + c < Rows) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i + k][j] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //left side
                if (i - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i - k][j] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diagnal top right
                if (i + c < Rows && j + c < Columns) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i + k][j + k] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diagnal top left
                if (i - c >= 0 && j + c < Columns) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i - k][j + k] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diagnal bottom right
                if (i + c < Rows && j - c <= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i + k][j - k] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
                //diaganl bottom left
                if (i - c >= 0 && j - c >= 0) {
                    int w = 1;
                    for (int k = 1; k <= c; k++)
                        if (Board[i - k][i - j] == 'o')
                            w++;
                    if (w == c) {

                        return true;
                    }
                    w = 0;
                }
            }
        }
    }
    return false;
}



int Menu() {
    int Choice;
    do {
        cout << "1. Play" << endl
            << "2. Save Game" << endl
            << "3. Load Game" << endl
            << "4. Exit" << endl
            << "Enter Your Choice (1 - 4): ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return Choice;
}

void initNewGame() {
    cout << "How Many Rows? ";
    cin >> Rows;
    cout << "How Many Cols? ";
    cin >> Columns;
    cout << "Connectivity Limit? ";
    cin >> ConnectLimit;
    cout << "First Player Name? ";
    cin >> PlayerNames[0];
    cout << "Second Player Name? ";
    cin >> PlayerNames[1];

    for (int r = 0; r < MaxRows; r++)
        for (int c = 0; c < MaxCols; c++)
            Board[r][c] = DefaultFill;
}

bool MakeMove(int Col) {
    int R = Next_Move[Col];

    // Array Bounds Check
    if (R >= Rows || Col >= Columns) {
        cout << "Invalid move. Try again." << endl;
        return false;
    }

    // Check for win first before switching players
    if (CheckForWinner(ConnectLimit)) {
        cout << "Congratulations " << PlayerNames[(TurningPlayer - 1 + MaxPlayers) % MaxPlayers]
            << " has won the game!!!" << std::endl;
        GameEndState = 1;
    }
    else {
        // Switch players
        TurningPlayer = (TurningPlayer + 1) % MaxPlayers;
    }

    // Make the move
    Board[R][Col] = PlayerMarks[TurningPlayer];
    Next_Move[Col]++;

    return true;
}



bool SaveGame(const string& FileName) {
    ofstream outputFile(FileName);
    if (!outputFile.is_open()) {
        cout << "Error opening file for saving!" << endl;
        return false;
    }

    // Save game parameters
    outputFile << Rows << " " << Columns << " " << ConnectLimit << endl;
    outputFile << PlayerNames[0] << " " << PlayerNames[1] << endl;

    // Save board state
    for (int r = 0; r < Rows; ++r) {
        for (int c = 0; c < Columns; ++c) {
            outputFile << Board[r][c] << " ";
        }
        outputFile << endl;
    }

    // Save next move array
    for (int c = 0; c < Columns; ++c) {
        outputFile << Next_Move[c] << " ";
    }

    outputFile.close();
    cout << "Game saved successfully!" << endl;
    return true;
}

bool LoadSavedGame(const string& FileName) {
    ifstream inputFile(FileName);
    if (!inputFile.is_open()) {
        cout << "Error opening file for loading!" << endl;
        return false;
    }

    // Load game parameters
    inputFile >> Rows >> Columns >> ConnectLimit;
    inputFile >> PlayerNames[0] >> PlayerNames[1];

    // Load board state
    for (int r = 0; r < Rows; ++r) {
        for (int c = 0; c < Columns; ++c) {
            inputFile >> Board[r][c];
        }
    }

    // Load next move array
    for (int c = 0; c < Columns; ++c) {
        inputFile >> Next_Move[c];
    }

    inputFile.close();
    cout << "Game loaded successfully!" << endl;
    return true;
}

void Play() {
    int Move;
    do {
        ShowGame();
        cout << "\tENTER NEGATIVE NUMBER FOR THE MAIN MENU" << endl;
        cout << "\tPlease Enter Your Move ? (0 - " << Columns << "): ";
        cin >> Move;
        if (Move < 0)
            break;
        if (!MakeMove(Move)) {
            cout << "Invalid move. Try again." << endl;
        }
    } while (GameisOn());
}

int main() {
    int Choice;
    bool GameNotLoaded = true;

    for (int i = 0; i < MaxCols; i++)
        Next_Move[i] = 0;


    do {
        Choice = Menu();
        switch (Choice) {
        case 1:
            if (GameNotLoaded) {
                initNewGame();
                GameNotLoaded = false;
            }
            Play();
            break;
        case 2:
        {
            string saveFileName;
            cout << "Enter the file name to save the game: ";
            cin >> saveFileName;
            SaveGame(saveFileName);
            break;
        }
        case 3:
        {
            string loadFileName;
            cout << "Enter the file name to load the game: ";
            cin >> loadFileName;
            LoadSavedGame(loadFileName);
            GameNotLoaded = false; // Set to false so that the loaded game state is used
            break;
        }
        }
    } while (Choice != 4);
    return 0;
}