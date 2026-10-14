// Задача: создаем аналог майнкрафта (поле 2*2*2) с возможностью передать поле в
// дальнейшую обработку, например, движком.
// int*** нужен, потому что поле трехмерное и мы выделяем в памяти конкретные
// ячейки.
// void* нужен, потому что мы хотим отдать поле на дальнейшую обработку,
// но мы не знаем, какой тип данных нужен дальше. А void типа не имеет и ошибки
// не будет.

// 0 - воздух, 1 - блок

#include <iostream>

int main() {
  int*** cube = new int**[2];
  for (int i = 0; i < 2; ++i) {
    cube[i] = new int*[2];
    for (int j = 0; j < 2; ++j) {
      cube[i][j] = new int[2]();
    }
  }

  cube[0][1][1] = 1;  // заполнение
  cube[1][0][0] = 1;

  void* generic_arg = static_cast<void*>(cube);  // упаковка

  int*** received_cube = static_cast<int***>(generic_arg);  // распаковка

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      delete[] received_cube[i][j];
    }
    delete[] received_cube[i];
  }
  delete[] received_cube;

  return 0;
}