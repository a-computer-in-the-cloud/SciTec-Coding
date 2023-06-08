#include "parser.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Parser::Parser () {};
Parser::~Parser () {};

enum tag {
  COMMA = ',',
  TAB   = '\t'
};

static std::string rtrim (std::string& token) {
  if (token.empty()) return token;
  size_t idx = token.size();
  size_t last_space = idx;
  while (--idx > 0) {
    if (isspace(token[idx])) {
      last_space = idx;
      continue;
    };
    return token.substr(0, last_space);
  };
  return token;
};

static size_t parse_line (std::ifstream& file, Row& row, size_t cols) {
  std::string line;
  getline (file, line);
  if (line.empty()) return 0;
  // std::cout<<" line.:"<<line<<"\n";

  char c;
  std::string token;
  for (size_t idx = 0; idx < line.size(); idx++) {
    c = line.at(idx);
    // std::cout<<c<<",";
    
    // If this line has more columns than the header
    // Then exit early
    if ((row.size() >= cols) && (cols > 0))
      break;

    if (c == tag::COMMA) {
      // end of token //
      // std::cout<<"token => "<<token<<", ";
      row.append (rtrim(token));
      token.clear();
      continue;
    };

    // Ignore leading spaces //
    if (isspace(c) && token.empty()) {
      continue;
    };

    token += c;
  };

  if (!token.empty()) {
    row.append (rtrim(token));
  };

  // less columns on this row? //
  // make up the difference to fill width //
  if (row.size() < cols) {
    size_t diff = cols - row.size();
    for (size_t item = 0; item < diff; item++) row.append("");
  };

  // std::cout<<" - "<<row.size()<<" \n";
  line.clear ();
  return row.size();
};

static size_t parse_header (std::ifstream& file, Row& row) {
  return parse_line (file, row, 0);
};

Status Parser::parse (const std::string filename, bool has_header) {
  std::ifstream file (filename, std::ios::in);
  if (!file.is_open()) {
    std::cerr<<"Failed to open CSV file {"<<filename<<"}\n";
    return STATUS_ERR;
  };
  
  Row row;
  // read header if specified
  size_t cols = 0;
  if (has_header)
    cols = parse_header (file, this->header);

  while (!file.eof()) {
    row.clear ();
    cols = parse_line (file, row, cols);
    if (cols > 0) {
      size_t len;
      auto time= std::stod(row[0], &len);
      auto lat = std::stod(row[1], &len);
      auto lng = std::stod(row[2], &len);
      auto alt = std::stod(row[3], &len);
      LLAPoint lla {time, lat, lng, alt};
      this->table.push_back (lla);
      // std::cout<<"lla==> "<<lla;
    };
    // getchar ();
  };

  if (file.is_open())
    file.close();

  return STATUS_OK;
};

void Parser::head (size_t limit) {
  size_t width = 32;
  std::cout << this->header;
  size_t counter = 0;
  for (auto& row : this->table) {
    if (counter++ >= limit) break;
    std::cout << row;
  };
};

LLAPoint Parser::getRow (size_t idx) {
  return this->table[idx];
};

size_t Parser::size () {
  return this->table.size ();
};

bool Parser::empty () {
  return this->table.empty ();
};