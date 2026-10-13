#include <iomanip>
#include <iostream>

float Average(const int arr[], int n) {
  float res;
  float summ = 0;
  for (int i = 0; i < n; ++i) {
    summ += arr[i];
  }
  res = summ / n;
  return res;
}

void MinMax(const int arr[], int n, int& min, int& max) {
  min = arr[0];
  max = arr[0];
  for (int i = 1; i < n; ++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
    if (arr[i] < min) {
      min = arr[i];
    }
  }
}

int Zero(const int arr[], int n) {
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] < 0) {
      count++;
    }
  }
  return count;
}

int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  int min = arr[0];
  int max = arr[0];

  std::cout << std::fixed << std::setprecision(1) << Average(arr, n) << '\n';

  MinMax(arr, n, min, max);
  std::cout << min << ' ' << max << '\n';

  std::cout << Zero(arr, n) << '\n';

  delete[] arr;
}