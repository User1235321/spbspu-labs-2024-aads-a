#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

#include "myTree.hpp"
#include "functions.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Bad input data!\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  using dictTree = rebdev::AVLTree< long long int, std::string >;
  rebdev::AVLTree< std::string, dictTree > dictionaryTree;
  while (!file.eof())
  {
    std::string line;
    std::getline(file, line);
    if (line.empty())
    {
      continue;
    }
    std::stringstream inLine(line);
    inLine >> line;
    dictTree newDictionary;
    while (!inLine.eof())
    {
      int key;
      std::string value;
      inLine >> key;
      inLine >> value;
      newDictionary[key] = value;
    }
    dictionaryTree[line] = newDictionary;
  }
  using func = std::function< void(dictTree &, const dictTree &, const dictTree &) >;
  rebdev::AVLTree< std::string, func > commandTree;
  commandTree["complement"] = rebdev::complement;
  commandTree["intersect"] = rebdev::intersect;
  commandTree["union"] = rebdev::treeUnion;
  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    try
    {
      if (command == "print")
      {
        std::cin >> command;
        auto it = dictionaryTree.find(command);
        if (!((*it).second.empty()))
        {
          std::cout << command;
          rebdev::print(std::cout, (*it).second);
        }
        else
        {
          std::cout << "<EMPTY>\n";
        }
      }
      else
      {
        auto it = commandTree.find(command);
        std::string firstTree, secondTree;
        std::cin >> command >> firstTree >> secondTree;
        auto tree1 = dictionaryTree.find(firstTree);
        auto tree2 = dictionaryTree.find(secondTree);
        if ((command == firstTree) || (command == secondTree))
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        else
        {
          (*it).second(dictionaryTree[command], (*tree1).second, (*tree2).second);
        }
      }
    }
    catch (const std::exception & e)
    {
      if (!std::cin.eof())
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  return 0;
}