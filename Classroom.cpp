#include "Classroom.h"

Classroom::Classroom(const std::vector<Student> &students_)
    : students(students_) {}

Classroom::Classroom() {}

std::vector<Student> Classroom::get_student_list() const
{
  return students;
}

void Classroom::add_student(const Student &s_)
{
  students.push_back(s_);
}

std::vector<size_t> Classroom::matching_names(const std::string &name_to_match) const
{
  std::vector<size_t> pos_of_matches;

  for (size_t i = 0; i < students.size(); i++)
  {
    if (students[i].get_full_name() == name_to_match)
    {
      pos_of_matches.push_back(i);
    }
  }

  return pos_of_matches;
}

void Classroom::remove_student(const size_t &pos_)
{
  students.erase(students.begin() + pos_);
}

Student Classroom::top_student() const
{
  Student hi_score;

  for (Student s : students)
    hi_score = s.grade_average() > hi_score.grade_average() ? s : hi_score;

  return hi_score;
}

std::vector<Student> Classroom::failing_students() const
{
  std::vector<Student> failing_students_v;
  for (Student s : students)
  {
    if (s.is_failing())
      failing_students_v.push_back(s);
  }
  return failing_students_v;
}
