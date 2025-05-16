#pragma once

#include <string>

class Student
{
  static const int NO_OF_MIDTERMS = 3;

private:
  std::string first_name;
  std::string last_name;
  int midterm_grades[NO_OF_MIDTERMS];
  int age;

public:
  Student(const std::string &fname_,
          const std::string &lname_,
          const int (&mt_grades_)[NO_OF_MIDTERMS],
          const int &age_);

  int grade_average() const;
  bool is_failing() const;
  bool is_passing() const;

  std::string to_csv_line() const;
};

Student::Student(const std::string &fname_,
                 const std::string &lname_,
                 const int (&mt_grades_)[NO_OF_MIDTERMS],
                 const int &age_)
    : first_name(fname_), last_name(lname_), age(age_)
{
  for (size_t i = 0; i < NO_OF_MIDTERMS; i++)
    midterm_grades[i] = mt_grades_[i];
}

int Student::grade_average() const
{
  float grade_sum = 0;
  for (size_t i = 0; i < NO_OF_MIDTERMS; i++)
    grade_sum += midterm_grades[i];

  return grade_sum / NO_OF_MIDTERMS;
}

bool Student::is_failing() const
{
  return grade_average() < 70;
}

bool Student::is_passing() const
{
  return grade_average() >= 70;
}

std::string Student::to_csv_line() const
{
  std::string str;

  str += first_name + "," + last_name + ",";

  for (size_t i = 0; i < NO_OF_MIDTERMS; i++)
    str += std::to_string(midterm_grades[i]) + ",";

  str += std::to_string(age);

  return str;
}