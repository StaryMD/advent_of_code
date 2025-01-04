// here just for shame

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream fin("data/day4.in");

  int points = 0;

  for (std::string card; std::getline(fin, card);) {
    card += ' ';

    int i = 0;
    while (card[i] != ':') {
      ++i;
    }
    ++i;
    while (!std::isdigit(card[i])) {
      ++i;
    }
    std::vector<int> freq;
    int number = 0;

    for (; card[i] != '|';) {
      if (card[i] == ' ') {
        while (card[i] == ' ') {
          ++i;
        }
        freq.resize(number + 1);
        ++freq[number];

        number = 0;
      } else {
        number = number * 10 + (card[i] - '0');
        ++i;
      }
    }

    int matches = 0;
    number = 0;
    ++i;

    while (!std::isdigit(card[i])) {
      ++i;
    }

    for (; i < card.size();) {
      if (card[i] == ' ') {
        while (i < card.size() && card[i] == ' ') {
          ++i;
        }
        std::cout << "x" << number << "x ";
        if (freq[number] != 0) {
          ++matches;
          std::cout << "match" << number << ' ';
        }

        number = 0;
      } else {
        number = number * 10 + (card[i] - '0');
        ++i;
      }
    }

    if (matches != 0) {
      points += 1 << (matches - 1);
    }
    std::cout << '\n';
  }

  std::cout << points << '\n';

  return 0;
}
