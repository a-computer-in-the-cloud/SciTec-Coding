#ifndef PARSER_HH
#define PARSER_HH

#include <vector>
#include <string>
#include "LLAPoint.h"
#include "status.h"
#include "row.h"

class Parser {
  public:
    Parser  ();
    ~Parser ();

    Status parse (const std::string filename, bool has_header = false);
    LLAPoint getRow (size_t idx);
    void head (size_t limit = 5);
    size_t size ();
    bool empty ();

    std::vector<LLAPoint>::iterator begin () { return this->table.begin(); };
    std::vector<LLAPoint>::iterator end   () { return this->table.end(); };

  Row header;
  std::vector<LLAPoint> table;
};


#endif