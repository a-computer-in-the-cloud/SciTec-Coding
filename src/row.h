#ifndef ROW_HH
#define ROW_HH

#include <vector>
#include <string>
#include <ostream>
#include <iomanip>

#include "LLAPoint.h"

class Row {
  public:
    Row  ();
    ~Row ();

    void clear ();
    bool empty ();
    size_t size ();
    void append (const std::string&);
    std::string operator [](size_t idx);
    size_t getIndex (std::string name);
    
    friend std::ostream& operator <<(std::ostream& out, const Row& row) {
      out << "Row {";
      for (auto& v : row.columns) {
        out << std::setw(6) << std::fixed << v <<", ";
      };
      out <<"}\n";
      return out;
    };
  
  std::vector<std::string> columns;
};

#endif