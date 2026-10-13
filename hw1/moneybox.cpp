#include <cstring>
#include <iostream>

typedef void (*ComFunc)(int&, int);

struct Commands {
  const char* name;
  ComFunc func;
};

void cmd_deposit(int& balance, int k) {
  if (k > 0) {
    balance += k;
  } else {
    std::cout << "error\n";
  }
}

void cmd_withdraw(int& balance, int k) {
  if (k > 0 && balance >= k) {
    balance -= k;
  } else {
    std::cout << "error\n";
  }
}

void cmd_balance(int& balance, int k) { std::cout << balance << "\n"; }

void cmd_reset(int& balance, int k) { balance = 0; }

void cmd_sixSeven(int& balance, int k) { balance += 67; }

int main() {
  int balance = 0;

  Commands table[] = {{"deposit", cmd_deposit},
                      {"withdraw", cmd_withdraw},
                      {"balance", cmd_balance},
                      {"sixSeven", cmd_sixSeven},
                      {"reset", cmd_reset}};
  int table_size = 5;

  char cmd[20];
  int k = 0;

  while (std::cin >> cmd) {
    if (std::strcmp(cmd, "stop") == 0) {
      break;
    }

    bool found = false;
    for (int i = 0; i < table_size; ++i) {
      if (std::strcmp(cmd, table[i].name) == 0) {
        if (std::strcmp(table[i].name, "deposit") == 0 ||
            std::strcmp(table[i].name, "withdraw") == 0) {
          std::cin >> k;
        } else {
          k = 0;
        }

        table[i].func(balance, k);
        found = true;
        break;
      }
    }

    if (!found) {
      std::cout << "error\n";
    }
  }

  return 0;
}