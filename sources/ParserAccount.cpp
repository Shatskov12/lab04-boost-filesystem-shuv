// Copyright 2020 Shatskov12 <qweser2016@mail.ru>

#include <ParsAcc.hpp>


//#include "iomanip"


ParserDir::ParserDir(string PathForParse) {
  const std::regex regularExp(
      "^(balance_)\\d\\d\\d\\d\\d\\d\\d\\d_\\d\\d\\d\\d\\d\\d\\d\\d");


  const boost::filesystem::path PathObj{PathForParse};
  if (boost::filesystem::exists(PathObj)) {
    for (auto ItEntry =
        boost::filesystem::recursive_directory_iterator(PathObj);
         ItEntry != boost::filesystem::recursive_directory_iterator();
         ++ItEntry) {
      if (boost::filesystem::is_regular_file(ItEntry->path())) {
        if ((ItEntry->path().stem().extension() == "")) {
          if (ItEntry->path().extension() == ".txt") {
            if (std::regex_search(ItEntry->path().stem().string(),
                                  regularExp)) {
              files.push_back(ItEntry->path());
              accountsStrings.insert(
                  ItEntry->path().stem().string().substr(8, 8));
            }
          }
        }
      }

      if (boost::filesystem::is_symlink(ItEntry->path())) {
        for (auto itEntrySymLink =
            boost::filesystem::recursive_directory_iterator(
                ItEntry->path());
             itEntrySymLink !=
             boost::filesystem::recursive_directory_iterator();
             ++itEntrySymLink) {
          if (boost::filesystem::is_regular_file(ItEntry->path())) {
            if ((ItEntry->path().stem().extension() == "")) {
              if (ItEntry->path().extension() == ".txt") {
                if (std::regex_search(ItEntry->path().stem().string(),
                                      regularExp)) {
                  files.push_back(ItEntry->path());
                  accountsStrings.insert(
                      ItEntry->path().stem().string().substr(8, 8));
                }
              }
            }
          }
        }
      }
    }
  }
}




string ParserDir::printFormatted() {
  std::stringstream ss;
  for (const auto& file : files) {
    ss << file.parent_path().filename().string() << " "
       << file.filename().string() << std::endl;
  }
  for (auto& acc : accounts){
    ss<<"broker:"<<acc.GetBrocker()<<" "<<"account:"<<
      acc.GetAccountNum()<<" "<<"files:"<<acc.GetFileSum()<<
      " "<<"lastdate:"<<acc.GetLastDate()<<std::endl;
  }
  return ss.str();
}


void ParserDir::assembleFilesForAcc() {
  for (const auto& acc : accountsStrings) {
    Account tempAcc;
    tempAcc.SetAccountNumber(acc);
    int lastDate = 0;
    for (const auto& file : files) {
      if (file.filename().string().substr(8, 8) == acc) {

        tempAcc.IncFilesSum();
        tempAcc.AddFile(file);
        tempAcc.SetBrocker(file.parent_path().filename().string());
        if (std::stoi(file.filename().stem().string().substr(17, 8)) > lastDate) {
          lastDate = std::stoi(file.filename().stem().string().substr(17, 8));
        }
      }
    }
    tempAcc.SetLastDate(lastDate);
    accounts.push_back(tempAcc);

  }

}

void Account::AddFile(boost::filesystem::path path) { Files.push_back(path); }

void Account::IncFilesSum() { ++FilesSum; }
void Account::SetLastDate(int date) { LastDate = date; }
void Account::SetBrocker(string brockerArg) { Brocker = brockerArg; }
void Account::SetAccountNumber(string accNum) { AccountNumber = accNum; }
string Account::GetBrocker() { return Brocker; }
string Account::GetAccountNum() { return AccountNumber; }
int Account::GetFileSum() { return FilesSum; }
int Account::GetLastDate() { return LastDate; }