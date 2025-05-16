#include <iostream>
#include <string>

#include "Student.hpp"
#include "Classroom.hpp"
#include "CSV-Grades.hpp"

struct student_t
{
  std::string fname;
  std::string lname;
  int midterms[3];
  int age;
};

int my_stoi(const std::string &s_)
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

student_t parse_line(const std::string &line_)
{
  static const int NO_OF_COMMAS = 5;
  static const int NO_OF_VALUES = NO_OF_COMMAS + 1;

  // comma positions.
  size_t comma_pos[NO_OF_COMMAS] = {};

  // the six substrings before converting to appropiate type
  // Format:        FirstName,LastName,Midterm1,Midterm2,Midterm3,Age
  // Value Types:   string,   string, int,      int,     int,     int
  std::string values[NO_OF_VALUES];

  for (size_t i = 0, prev_pos = 0; i < NO_OF_COMMAS; prev_pos = comma_pos[i], i++)
  {
    comma_pos[i] = line_.find(',', prev_pos) + 1;
  }

  for (size_t i = 0, prev_pos = 0; i < NO_OF_VALUES; i++, prev_pos = comma_pos[i - 1])
  {
    values[i] = line_.substr(prev_pos, comma_pos[i] - (prev_pos + 1));
  }

  return {values[0], values[1], {my_stoi(values[2]), my_stoi(values[3]), my_stoi(values[4])}, my_stoi(values[5])};
}

void print_student(const student_t &s_)
{
  std::cout << "student:\nfirst name: " + s_.fname + "\nlast name: " + s_.lname + "\nmidterm grades: " << s_.midterms[0] << ", " << s_.midterms[1] << ", " << s_.midterms[2] << "\nage: " << s_.age << std::endl;
}

int main()
{
  // std::cout << my_stoi("128");

  // student_t s = parse_line("FirstName,LastName,12,98,54,19");

  Classroom classroom_(
      {{"a", "a", {10, 10, 10}, 18},
       {"maria jose", "castilla", {11, 11, 11}, 17},
       {"c", "c", {9, 9, 9}, 17}});

  std::cout << classroom_.top_student().to_csv_line();

  return 0;
}