#pragma once

#include <string>

class Student
{
public:
  static const int NO_OF_MIDTERMS = 3;

private:
  std::string first_name;
  std::string last_name;
  int midterm_grades[NO_OF_MIDTERMS] = {};
  int age;

public:
  Student();
  Student(const std::string &fname_,
          const std::string &lname_,
          const int (&mt_grades_)[NO_OF_MIDTERMS],
          const int &age_);

  std::string get_full_name() const;
  std::pair<std::string, std::string> get_names() const;
  int grade_average() const;
  bool is_failing() const;
  bool is_passing() const;
  bool is_underage() const;

  std::string to_pretty_string() const;
  std::string to_csv_line() const;
};