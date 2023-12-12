#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream fin("data/day1.in");

  int ans = 0;

  for (std::string str; std::getline(fin, str);) {
    int first = -1;
    int second = 0;

    for (auto ch : str) {
      if (ch >= '0' && ch <= '9') {
        if (first == -1) {
          first = ch;
        }

        second = ch;
      }
    }

    first -= '0';
    second -= '0';

    const int val = first * 10 + second;

    ans += val;
  }

  std::cout << "Answer: " << ans << '\n';

  return 0;
}
