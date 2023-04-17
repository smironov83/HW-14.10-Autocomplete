#pragma once
#include <string>
#include <vector>

const size_t ALPHABET_SIZE = 33;

// Структура узела дерева 
class AutocompleteDictionary
{
  AutocompleteDictionary* child_[ALPHABET_SIZE] = {};
  bool endOfWord_ = false;

public:
  std::vector<std::string> prefixes_;
  int prefCount = 0;

  AutocompleteDictionary();
  ~AutocompleteDictionary();

  void Insert(AutocompleteDictionary* root, std::string word);
  auto Search(AutocompleteDictionary* root, std::string word) -> bool;
  void FindAllPrefixes(AutocompleteDictionary* root, char* wordConstructor, int index, std::string const word);
};

