#include <string>
#include <iostream>
#include "config.h"
#include "game.h"

int main(int argc, char *argv[])
{
  std::cout << "Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

  Game().Run();
}
