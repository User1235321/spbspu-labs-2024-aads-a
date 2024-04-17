#ifndef INPUT_EXPRESSIONS_HPP
#define INPUT_EXPRESSIONS_HPP

#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
#include "data_types.hpp"

namespace namestnikov
{
  void inputExpressions(std::istream & in, Stack< Queue< namestnikov::Key > > & expressionsStack);
  void inputExpression(std::string s, Queue< namestnikov::Key > & expression);
}

#endif
