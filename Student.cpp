#include "Student.h"

Student::Student()
    : first_name("dummy"),
      last_name("dummy"),
      midterm_grades{-1, -1, -1},
      age(0) {}

Student::Student(const std::string &fname_,
                 const std::string &lname_,
                 const int (&mt_grades_)[NO_OF_MIDTERMS],
                 const int &age_)
    : first_name(fname_), last_name(lname_), age(age_)
{
  for (size_t i = 0; i < NO_OF_MIDTERMS; i++)
    midterm_grades[i] = mt_grades_[i];
}

std::string Student::get_full_name() const
{
  return std::string(first_name + " " + last_name);
}

std::pair<std::string, std::string> Student::get_names() const
{
  return std::make_pair(first_name, last_name);
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

bool Student::is_underage() const
{
  return age < 18;
}

std::string Student::to_pretty_string() const
{
  std::string str;

  str += first_name + " " + last_name + ", ";

  for (size_t i = 0; i < NO_OF_MIDTERMS; i++)
    str += std::to_string(midterm_grades[i]) + ", ";

  str += std::to_string(age) + " años.";

  return str;
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