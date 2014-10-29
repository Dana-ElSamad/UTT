#include <iostream>

using namespace std;

enum Piece {TTTS_BLANK, TTTS_O, TTTS_X};
enum Status {NONE, TIE, O, X};

class TicTacToeBoard
{
public:
    TicTacToeBoard();
    void initBoard();
    void displayBoard();
    int move(int x, int y, Piece _turn);
    Status update();
    Status getStatus();
    Piece _board[3][3];

private:
    Piece** getBoard();
    Status _gameStatus;
};

TicTacToeBoard::TicTacToeBoard()
{
    initBoard();
    _gameStatus = NONE;
}

void TicTacToeBoard::initBoard()
{
    for(int x = 0; x < 3; ++x)
        for(int y = 0; y < 3; ++y)
            _board[x][y] = TTTS_BLANK;
}

Piece** TicTacToeBoard::getBoard()
{
    return (Piece **) _board;
}

Status TicTacToeBoard::getStatus()
{
    return _gameStatus;
}

int TicTacToeBoard::move(int x, int y, Piece _turn)
{
    /* player grid is display from 1 
     * so 1 must be subtracted for the 
     * correct indice */
    if(_board[x-1][y-1] == TTTS_BLANK) {
        _board[x-1][y-1] = _turn;
        return 1;
    }
    return 0;  // cell already occupied
}

Status TicTacToeBoard::update()
{ 
    bool tie = true;
    /* check for a tie */
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(_board[i][j] == TTTS_BLANK)
                tie = false;

    if(tie) {
        _gameStatus = TIE;
        return TIE;
    }

    /* DIAGONALS */
    /* top-left to bottom-right */
    if(_board[0][0] != TTTS_BLANK && 
       _board[0][0] == _board[1][1] && 
       _board[1][1] == _board[2][2]) {
        _gameStatus = _board[0][0] == TTTS_X ? X : O;
        return _gameStatus; // return winner
    }        
    
    /* top-right to bottom-left */
    if(_board[0][2] != TTTS_BLANK && 
       _board[0][2] == _board[1][1] && 
       _board[1][1] == _board[2][0]) {
        _gameStatus = _board[0][2] == TTTS_X ? X : O;
        return _gameStatus; // return winner
    }        

    /* COLUMNS */
    for(int column = 0; column < 3; column++)
    {
        if(_board[0][column] == _board[1][column] \
                && _board[0][column] != TTTS_BLANK \
                && _board[1][column] == _board[2][column]) {
            _gameStatus = _board[0][column] == TTTS_X ? X : O;
            return _gameStatus; // return winner
        }
    }
    
    /* ROWS */
    for(int row = 0; row < 3; row++)
    {
        if(_board[row][0] != TTTS_BLANK
            && _board[row][0] == _board[row][1] \
            && _board[row][1] == _board[row][2]) {
            _gameStatus = _board[row][0] == TTTS_X ? X : O;
            return _gameStatus; // return winner
        }
    }
    
    return NONE; // no one has won yet
}