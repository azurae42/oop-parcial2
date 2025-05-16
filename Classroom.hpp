#pragma once

#include <string>
#include <vector>

#include "Student.hpp"

class Classroom
{
private:
  std::vector<Student> students;

public:
  Classroom();
  Classroom(const std::vector<Student> &students_);
  void add_student(const Student &s_);
  void remove_student(const size_t &pos_);
};

Classroom::Classroom(const std::vector<Student> &students_) : students(students_) {}

void Classroom::add_student(const Student &s_)
{
  students.push_back(s_);
}

void Classroom::remove_student(const size_t &pos_)
{
  try
  {
    students.erase(students.begin() + pos_ - 1);
  }
  catch (...)
  {
    return;
  }
}
