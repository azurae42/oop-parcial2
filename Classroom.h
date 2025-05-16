#pragma once

#include <string>
#include <vector>

#include "Student.h"

class Classroom
{
private:
  std::vector<Student> students;

public:
  Classroom();
  Classroom(const std::vector<Student> &students_);

  std::vector<Student> get_student_list() const;
  void add_student(const Student &s_);
  std::vector<size_t> matching_names(const std::string &full_name_) const;
  void remove_student(const size_t &pos_);
  Student top_student() const;
  std::vector<Student> failing_students() const;
};