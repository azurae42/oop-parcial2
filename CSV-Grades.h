#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Student.h"

class CSV_Grades
// Format: FirstName,LastName,Midterm1,Midterm2,Midterm3,Age
{
private:
  std::ifstream in;
  std::ofstream out;

  std::string opened_file_to_read;
  std::string opened_file_to_write;

  int my_stoi(const std::string &s_) const;
  Student parse_line(const std::string &line_) const;

public:
  CSV_Grades();

  std::string get_opened_file_read() const;
  std::string get_opened_file_write() const;

  bool open_file_to_read(const std::string &filename_read_);
  bool open_file_to_write(const std::string &filename_write_);
  bool open_file_to_overwrite(const std::string &filename_overwrite_);

  std::vector<Student> read_students_from_file();
  void write_header_to_file();
  void write_student_to_file(const Student &s_);
  void update_file(const std::vector<Student> &s_list);

  void end_file_read();
  void end_file_write();
};
