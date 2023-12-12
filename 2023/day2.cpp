#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> Tokenizer(const std::string &str) {
  std::vector<std::string> ans;

  std::string word;

  for (const char ch : str) {
    if (ch != ':') {
      switch (ch) {
        case ' ': {
          if (not word.empty()) {
            ans.push_back(word);
            word.clear();
          }
          break;
        }
        case ';': {
          ans.push_back(word);
          word.clear();

          ans.push_back(";");
          break;
        }
        default: {
          word += ch;
        }
      }
    }
  }

  if (not word.empty()) {
    ans.push_back(word);
  }

  return ans;
}

int main() {
  std::ifstream fin("data/day2.in");

  int ans = 0;

  for (std::string str; std::getline(fin, str);) {
    const std::vector<std::string> tokens = Tokenizer(str);

    std::unordered_map<char, int> map;
    std::unordered_map<char, int> max_map;

    for (int i = 2; i < tokens.size(); i += 2) {
      if (tokens[i] == ";") {
        max_map['r'] = std::max(max_map['r'], map['r']);
        max_map['g'] = std::max(max_map['g'], map['g']);
        max_map['b'] = std::max(max_map['b'], map['b']);
        ++i;
        map.clear();
      }
      map[tokens[i + 1][0]] += std::stoi(tokens[i]);
    }
    max_map['r'] = std::max(max_map['r'], map['r']);
    max_map['g'] = std::max(max_map['g'], map['g']);
    max_map['b'] = std::max(max_map['b'], map['b']);

    const int power = max_map['r'] * max_map['g'] * max_map['b'];

    ans += power;
  }

  std::cout << "Answer: " << ans << '\n';

  return 0;
}
