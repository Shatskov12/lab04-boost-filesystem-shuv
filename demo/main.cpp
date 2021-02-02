#include <ParsAcc.hpp>

int main (int argc, char *argv[]) {
  std::string path;

  if (argc == 1) {
    path = ".";

  } else {
    path = argv[1];
  }




  //path = "/Users/yury/Desktop/lab-04-boost-filesystem/misc/ftp";

  ParserDir parser(path);
  parser.assembleFilesForAcc();
  std::cout<<parser.printFormatted();


}