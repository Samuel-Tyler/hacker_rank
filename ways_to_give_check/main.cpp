#include <bits/stdc++.h>

using namespace std;

enum SquareType
{
  Empty,
  King,
  NonKing,
  Invalid
};

SquareType CheckSquare(const vector<vector<char>> &board, int row, int col)
{
  if (row >= 0 && row < 8 && col >= 0 && col < 8)
  {
    char piece = board[row][col];
    if (piece == 'k')
    {
      return King;
    }
    else if (piece == '#')
    {
      return Empty;
    }
    else
    {
      return NonKing;
    }
  }
  else
  {
    return Invalid;
  }
}

bool checkAndModify(const vector<vector<char>> &board, int row, int col,
                    void (*modify)(int &, int &))
{
  SquareType squareType = Empty;
  while (squareType == Empty)
  {
    modify(row, col);
    squareType = CheckSquare(board, row, col);
    if (squareType == King)
    {
      return true;
    }
  }
  return false;
}

bool straightCheck(const vector<vector<char>> &board, int row, int col)
{
  if (checkAndModify(board, row, col, [](int &nrow, int &) { nrow++; }))
  {
    return true;
  }
  if (checkAndModify(board, row, col, [](int &nrow, int &) { nrow--; }))
  {
    return true;
  }
  if (checkAndModify(board, row, col, [](int &, int &ncol) { ncol--; }))
  {
    return true;
  }
  if (checkAndModify(board, row, col, [](int &, int &ncol) { ncol++; }))
  {
    return true;
  }
  return false;
}

bool diagonalCheck(const vector<vector<char>> &board, int row, int col)
{
  if (checkAndModify(board, row, col, [](int &nrow, int &ncol) {
        nrow++;
        ncol++;
      }))
  {
    return true;
  }
  if (checkAndModify(board, row, col, [](int &nrow, int &ncol) {
        nrow--;
        ncol++;
      }))
  {
    return true;
  }
  if (checkAndModify(board, row, col, [](int &nrow, int &ncol) {
        nrow++;
        ncol--;
      }))
  {
    return true;
  }
  if (checkAndModify(board, row, col, [](int &nrow, int &ncol) {
        nrow--;
        ncol--;
      }))
  {
    return true;
  }
  return false;
}

bool knightCheck(const vector<vector<char>> &board, int row, int col)
{
  if (CheckSquare(board, row - 1, col - 2) == King)
  {
    return true;
  }
  if (CheckSquare(board, row - 1, col + 2) == King)
  {
    return true;
  }
  if (CheckSquare(board, row + 1, col - 2) == King)
  {
    return true;
  }
  if (CheckSquare(board, row + 1, col + 2) == King)
  {
    return true;
  }
  if (CheckSquare(board, row - 2, col - 1) == King)
  {
    return true;
  }
  if (CheckSquare(board, row - 2, col + 1) == King)
  {
    return true;
  }
  if (CheckSquare(board, row + 2, col - 1) == King)
  {
    return true;
  }
  if (CheckSquare(board, row + 2, col + 1) == King)
  {
    return true;
  }
  return false;
}

bool checkDiscoveredChecks(vector<vector<char>> board, int row, int col)
{
  board[row][col] = '#';

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[i][j] == 'Q')
      {
        if (diagonalCheck(board, i, j) || straightCheck(board, i, j))
        {
          return true;
        }
      }
      if (board[i][j] == 'R')
      {
        if (straightCheck(board, i, j))
        {
          return true;
        }
      }
      if (board[i][j] == 'B')
      {
        if (diagonalCheck(board, i, j))
        {
          return true;
        }
      }
    }
  }
  return false;
}

int waysToGiveACheck(vector<vector<char>> board)
{
  const int _7th_row_index = 1;
  const int _8th_row_index = 0;
  int n = 0;
  for (int i = 0; i < 8; i++)
  {
    if ('P' == board[_7th_row_index][i] && board[_8th_row_index][i] == '#')
    {
      if (checkDiscoveredChecks(board, _7th_row_index, i))
      {
        n+=4;
      }
      else
      {
        if (knightCheck(board, _8th_row_index, i))
        {
          n++;
        }

        bool diagCheck = diagonalCheck(board, _8th_row_index, i);
        bool strCheck = straightCheck(board, _8th_row_index, i);

        if (diagCheck)
        {
          n++;
        }
        if (strCheck)
        {
          n++;
        }
        if (diagCheck || strCheck)
        {
          n++;
        }
      }
    }
  }
  return n;
}

int main()
{
  int t;
  cin >> t;
  for (int a0 = 0; a0 < t; a0++)
  {
    vector<vector<char>> board(8, vector<char>(8));
    for (int board_i = 0; board_i < 8; board_i++)
    {
      for (int board_j = 0; board_j < 8; board_j++)
      {
        cin >> board[board_i][board_j];
      }
    }
    int result = waysToGiveACheck(board);
    cout << result << endl;
  }
  return 0;
}
