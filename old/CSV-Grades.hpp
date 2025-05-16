#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Student.hpp"

class CSV_Grades
// Format: FirstName,LastName,Midterm1,Midterm2,Midterm3,Age
{
private:
  std::ifstream in;
  std::ofstream out;

  std::string open_r_file;
  std::string open_w_file;

  int my_stoi(const std::string &s_) const;
  Student parse_line(const std::string &line_) const;

public:
  CSV_Grades();

  void open_file_to_read(const std::string &filename_r_);
  void open_file_to_write(const std::string &filename_w_);

  std::vector<Student> read_students_from_file();
  void write_student_to_file(const Student &s_);
};

int CSV_Grades::my_stoi(const std::string &s_) const
{
  // value to return
  int integer = 0;
  for (int i = s_.size() - 1, pwr = 1; i >= 0; i--, pwr *= 10)
  {
    if (i != 0 && !isdigit(s_[i]))
    {
      return 0;
    }
    else if (i == 0 && s_[i] == '-')
    {
      return integer * -1;
    }

    integer += (s_[i] - '0') * pwr;
  }

  return integer;
}

Student CSV_Grades::parse_line(const std::string &line_) const
{
  static const int NO_OF_COMMAS = 5;
  static const int NO_OF_VALUES = NO_OF_COMMAS + 1;

  size_t comma_positions[NO_OF_COMMAS] = {};

  // the six substrings before converting to appropiate type
  // Format:        FirstName,LastName,Midterm1,Midterm2,Midterm3,Age
  // Value Types:   string,   string, int,      int,     int,     int
  std::string values[NO_OF_VALUES];

  for (size_t i = 0, prev_pos = 0; i < NO_OF_COMMAS; prev_pos = comma_positions[i], i++)
  {
    comma_positions[i] = line_.find(',', prev_pos) + 1;
  }

  for (size_t i = 0, prev_pos = 0; i < NO_OF_VALUES; i++, prev_pos = comma_positions[i - 1])
  {
    values[i] = line_.substr(prev_pos, comma_positions[i] - (prev_pos + 1));
  }

  return {values[0], values[1], {my_stoi(values[2]), my_stoi(values[3]), my_stoi(values[4])}, my_stoi(values[5])};
}

void CSV_Grades::open_file_to_read(const std::string &filename_r_)
{
  in.open(filename_r_);

  if (!in.good())
  {
    std::cerr << "file could not be opened.\n";
    in.close();
  }
}

void CSV_Grades::open_file_to_write(const std::string &filename_w_)
{
  out.open(filename_w_, std::ios::app);

  if (!out.good())
  {
    std::cerr << "file could not be opened.\n";
    out.close();
  }
}
