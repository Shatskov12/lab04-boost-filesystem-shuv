// Copyright 2020 Shatskov12 <qweser2016@mail.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <set>
#include <regex>
#include <iostream>
#include <sstream>

using std::string;
using std::vector;

class Account {
 private:
  string Brocker;
  string AccountNumber;
  vector<boost::filesystem::path> Files;
  int FilesSum = 0;
  int LastDate;

 public:
  void AddFile(boost::filesystem::path);
  void IncFilesSum();
  void SetLastDate(int);
  void SetBrocker(string);
  void SetAccountNumber(string);
  string GetBrocker();
  string GetAccountNum();
  int GetFileSum();
  int GetLastDate();
};


class ParserDir{
 private:
  vector<boost::filesystem::path> files;
  std::set<std::string> accountsStrings;
  vector<Account> accounts;
 public:
  explicit ParserDir(string pathForParse);
  void assembleFilesForAcc();
  string printFormatted();

};



#endif // INCLUDE_HEADER_HPP_
