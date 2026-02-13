#include "include/search.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string cleanToken(const string& token) {
  string s = token;
  for (char& c : s) {
    c = static_cast<char>(tolower(static_cast<unsigned>(c)));
  }

  bool hasLetter = false;
  for (char c : s) {
    if (isalpha(static_cast<unsigned char>(c))) {
      hasLetter = true;
      break;
    }
  }
  if (!hasLetter) return "";

  size_t start = 0;
  while (start < s.size() && ispunct(static_cast<unsigned char>(s[start]))) {
    start++;
  }

  size_t end = s.size();
  while (end > start && ispunct(static_cast<unsigned char>(s[end - 1]))) {
    end--;
  }

  return s.substr(start, end - start);
}

set<string> gatherTokens(const string& text) {
  set<string> tokens;
  stringstream ss(text);

  string raw;
  while (ss >> raw) {
    string cleaned = cleanToken(raw);
    if (!cleaned.empty()) {
      tokens.insert(cleaned);
    }
  }
  return tokens;
}

int buildIndex(const string& filename, map<string, set<string>>& index) {
  // TODO student
  return 0;
}

set<string> findQueryMatches(const map<string, set<string>>& index,
                             const string& sentence) {
  // TODO student
  return {};
}

void searchEngine(const string& filename) {
  // TODO student
}
