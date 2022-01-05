#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <stdlib.h>
#include <cstdlib>

bool isValid(char str[])
{
  int arg = atoi(str);
  if (arg <= 0)
    return false;
  return true;
}

int main(int argc, char** argv) {
  int codeCount;

  if (argc == 2)
  {
    if (isValid(argv[1]))
    {
      codeCount = atoi(argv[1]);
    }
    else
    {
      std::cout << "Invalid argument; defaulting to single codename." << std::endl;
      codeCount = 1;
    }
  }
  else 
  {
    codeCount = 1;
  }

  std::string line;
  std::vector<std::string> nouns;
  std::vector<std::string> adjectives;
  
  std::string const HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";  
  std::ifstream nounFile(HOME + "/bin/codenames/nouns.csv");
  if (nounFile.is_open())
  {
    while (std::getline(nounFile, line))
    {
      nouns.push_back(line);
    }
    nounFile.close();
  }

  std::ifstream adjFile(HOME + "/bin/codenames/adjectives.csv");
  if (adjFile.is_open())
    {
      while (std::getline(adjFile, line))
      {
        adjectives.push_back(line);
      }
      adjFile.close();
    }

  std::random_device dev;
  std::mt19937::result_type seed = dev() ^ (
      (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count() + 
      (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch()).count());
  std::mt19937 gen(seed);
  std::uniform_int_distribution<std::mt19937::result_type> distNouns(0, static_cast<int>(nouns.size()));
  std::uniform_int_distribution<std::mt19937::result_type> distAdjs(0, static_cast<int>(adjectives.size()));
  
  for (int i=0; i<codeCount; i++)
  {
    int adjIdx = distAdjs(gen);
    int nounIdx = distNouns(gen);
    std::cout << adjectives[adjIdx] << " " << nouns[nounIdx] << std::endl;
  }

  return 0;
}
