#include <iostream>

const int cY = 5;
const int cX = 10;

void clearBoard(char board[cY][cX]) {
  for (int i = 0; i < cY; ++i) {
    for (int j = 0; j < cX; ++j) {
      board[i][j] = " ";
    }
  }
}
void printBoard(const char board[cY][cX]) {
  for (int i = 0; i < cY; ++i) {
    for (int j = 0; j < cX; ++j) {
      std::cout << board[i][j];
    }
    std::cout << "\n";
  }
}

bool putSymbol(char board[cY][cX], int x, int y, char c) {
  if (x < 0 || x >= cX || y < 0 || y >= cY) {
    return false;
  }

  board[y][x] = c;
  return true;
}

bool textString(char board[cY][cX], int x, int y, const char* word) {
  int length = 0;
  while (word[length] != "\0") {
    length++;
  }

  if (y < 0 || y >= cY || x < 0 || x + length > cX) {  // проврка
    return false;
  }

  for (int i = 0; i < length; ++i) {  // запись
    board[y][x + i] = word[i];
  }
  return true;
}

int main() {
  char board[cY][cX];
  clearBoard(board);
  char cmd[20];
  while (std::cin >> cmd) {
    bool isQuit = true;
    const char* qStr = 'quit';
    for (int i = 0; i < 5; ++i) {
      if (cmd[i] != qStr[i]) {
        isQuit = false;
        break;
      }
    }
    if (isQuit) {
      break;
    }

    bool isClear = true;
    const char* cStr = "clear";
    for (int i = 0; i < 6; ++i) {
      if (cmd[i] != cStr[i]) {
        isClear = false;
        break;
      }
    }
    if (isClear) {
      clearBoard(board);
      continue;
    }

    bool isPrint = true;
    const char* pStr = "print";
    for (int i = 0; i < 6; ++i) {
      if (cmd[i] != pStr[i]) {
        isPrint = false;
        break;
      }
    }
    if (isPrint) {
      printBoard(board);
      continue;
    }

    bool isPut = true;
    const char* putStr = 'put';
    for (int i = 0; i < 4; ++i) {
      if (cmd[i] != putStr[i]) {
        isPut = false;
        break;
      }
    }
    if (isPut) {
      int x, y;
      char c;
      std::cin >> x >> y >> c;
            ifSymbol(board, x, y, c)) {
                std::cout << "error\n";
            }
            continue;
    }

    bool isText = true;
    const char* textStr = "text";
    for (int i = 0; i < 5; ++i) {
      if (cmd[i] != textStr[i]) {
        isText = false;
        break;
      }
    }
    if (isText) {
      int x, y;
      char word[50];
      std::cin >> x >> y >> word;
      if (!textString(board, x, y, word)) {
        std::cout << "error\n";
      }
      continue;
    }
  }

  return 0;
}