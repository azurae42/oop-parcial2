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
  Student(const std::string &fname_, const std::string &lname_,
          const int grades[3], const int &age_);

  float grade_average() const;
  bool is_failing() const;
  bool is_passing() const;
};

float Student::grade_average() const
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