#pragma once

#include "Student.hpp"
#include <string>
#include <vector>

class Classroom
{
private:
  std::vector<Student> students;

public:
  Classroom();
  void add_student(const Student &s_);
};