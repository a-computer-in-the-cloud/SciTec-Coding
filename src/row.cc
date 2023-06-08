#include "row.h"


Row::Row () {};
Row::~Row() {};

void Row::clear () {
  columns.clear ();
};
bool Row::empty () {
  return columns.empty();
};
size_t Row::size () {
  return columns.size();
};

void Row::append (const std::string& token) {
  this->columns.push_back (token);
};

std::string Row::operator [](size_t idx) {
  if ((idx < 0) || (idx > columns.size())) return "";
  return columns[idx];
};

size_t Row::getIndex (std::string name) {
  for (size_t idx = 0; idx < this->columns.size(); idx++) {
    if (this->columns[idx].compare (name) == 0) {
      return idx;
    };
  };
  return std::string::npos;
};