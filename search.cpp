#include "include/search.h"

#include <algorithm>
#include <cctype>
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
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
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
  ifstream infile(filename);
  if (!infile.is_open()) return 0;

  int pages = 0;
  string url, text;

  while (getline(infile, url) && getline(infile, text)) {
    if (!url.empty() && url.back() == '\r') {
      url.pop_back();
    }
    if (!text.empty() && text.back() == '\r') {
      text.pop_back();
    }

    pages++;
    set<string> tokens = gatherTokens(text);

    for (const string& token : tokens) {
      index[token].insert(url);
    }
  }

  return pages;
}

set<string> findQueryMatches(const map<string, set<string>>& index,
                             const string& sentence) {
  stringstream ss(sentence);
  string term;

  ss >> term;
  string cleaned = cleanToken(term);

  set<string> result;
  auto it = index.find(cleaned);
  if (it != index.end()) {
    result = it->second;
  }

  while (ss >> term) {
    char modifier = 0;
    if (term[0] == '+' || term[0] == '-') {
      modifier = term[0];
      term = term.substr(1);
    }

    string cleanedTerm = cleanToken(term);

    set<string> matches;
    auto it2 = index.find(cleanedTerm);
    if (it2 != index.end()) {
      matches = it2->second;
    }

    set<string> temp;
    if (modifier == '+') {
      set_intersection(result.begin(), result.end(), matches.begin(),
                       matches.end(), inserter(temp, temp.begin()));
    } else if (modifier == '-') {
      set_difference(result.begin(), result.end(), matches.begin(),
                     matches.end(), inserter(temp, temp.begin()));
    } else {
      set_union(result.begin(), result.end(), matches.begin(), matches.end(),
                inserter(temp, temp.begin()));
    }

    result = temp;
  }

  return result;
}

void searchEngine(const string& filename) {
  map<string, set<string>> index;

  int pages = buildIndex(filename, index);

  if (pages == 0) {
    cout << "Error: Unable to open file" << endl;
    return;
  }

  cout << "Indexed " << pages << " pages containing " << index.size()
       << " unique terms" << endl;

  while (true) {
    cout << "Enter query sentence (press enter to quit):" << endl;

    string query;
    getline(cin, query);

    if (query == "") {
      break;
    }

    set<string> matches = findQueryMatches(index, query);

    cout << "Found " << matches.size() << " matching pages" << endl;
    for (const string& url : matches) {
      cout << url << endl;
    }
  }

  cout << "Thank you for searching!" << endl;
}
