#include "cmdline.hpp"

#include "docopt.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>

#include "debug.hpp"
#include "keys.hpp"

namespace cmdline {
  static const char USAGE_KEYGEN[] =
  R"(Generate randomly a new secret and public key.

  Usage: ecc keygen [-h] [-d] [--output=<file>]

    Options:
      -d --debug                 show debug informations
      -h --help                  show this screen.
      -o <file> --output=<file>  store key pair at this location [default: /tmp/id_m511]
  )";

  void cmdline_keygen(std::vector<std::string> args){
    std::map<std::string, docopt::value> subargs
          = docopt::docopt(USAGE_KEYGEN,
                          args, //generate argument array automatically
                          true, // show help if requested
                          ""); //version string

  std::string filename = subargs["--output"].asString();

  std::string pk;
  std::string sk;

  Private_Key k;
  k.generate();
  sk = k.tostring();
  pk = k.get_pub().tostring();
  Debug::Write("Saving Private Key..");
  //TODO Format keys in a usefull way.
  std::ofstream f_privatekey(filename);
  f_privatekey << sk;
  f_privatekey.close();
  Debug::Write("Saving Public Key..");
  std::ofstream f_publickey(filename+".pub");
  f_publickey << pk;
  f_publickey.close();
  }
}
