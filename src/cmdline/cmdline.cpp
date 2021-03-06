#include <iostream>
#include <string>
#include "docopt.h"

#include "debug.hpp"

#include "cmdline.hpp"

namespace cmdline{
  static const char USAGE[] =
  R"(Eliptic curve cryptography with M-511 proposed by D.F. Aranha et al.
  WARNING UNSECURE! DO NOT USE IN THE REAL WORLD, FOR EDUCATIONAL PURPOSES ONLY!

    Usage: ecc [--version] [--help] [--debug] <command> [<args>...]

    Options:
      -d --debug    show debug informations
      -h --help     show this screen.
      --version     show version.

    Available ecc commands are:
      keygen        generate a new key pair.
      box           encrypt and authenticate a message
      box-open      decrypt and authenticate a message
      encrypt       encrypt a message to a known public key.
      decrypt       decrypt a message with a secret key.
      sign          sign a message with a secret key.
      verify        verify a signature of a message to a given public key.
      test          run test.

    See 'ecc <commands> --help' for more information of the specific command.
  )";

  void cmdline(int argc, char const *argv[]){
    std::map<std::string, docopt::value> args
        = docopt::docopt(USAGE,
                        { argv + 1, argv + argc }, //generate argument array automatically
                        true, // show help if requested
                        //TODO(Yoann): use Version from appinfo.hpp
                        "Eliptic Curve Cryptogryphy ", // version string
                        true); //options_first

    if (args["--debug"].asBool() == true)
      Debug::SetLevel(true);
    else
      Debug::SetLevel(false);

    Debug::Write("Debug on");

    // for(auto const& arg : args) {
    //     std::cout << arg.first <<  arg.second << std::endl;
    // }

    std::string command = args["<command>"].asString();
    std::vector<std::string> subargs = args["<args>"].asStringList();
    //std::vector<std::string> subargs;
    subargs.insert(subargs.begin(), command);

    if (command == "keygen")
      cmdline_keygen(subargs);
    else if (command == "box")
      cmdline_box(subargs);
    else if (command == "box-open")
      cmdline_box_open(subargs);
    else if (command == "encrypt")
      cmdline_encrypt(subargs);
    else if (command == "decrypt")
      cmdline_decrypt(subargs);
    else if (command == "sign")
      cmdline_sign(subargs);
    else if (command == "verify")
      cmdline_verify(subargs);
    else if (command == "test")
      cmdline_test(subargs);
    else
      std::cout << args["<commands>"] << "is not a valid command. See 'ecc --help'." << std::endl;
  }
}
