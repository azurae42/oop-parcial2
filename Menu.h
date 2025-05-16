#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Student.h"
#include "Classroom.h"
#include "CSV-Grades.h"

class Menu
{
private:
  int user_choice = 0;
  bool students_are_loaded = false;
  std::string original_filename;

  CSV_Grades csv_handler;
  Classroom classroom;

  void load_file();
  void print_grades();
  void general_info();
  void show_failing_students();
  void add_new_student();
  void remove_student();
  void update_original_file();

public:
  Menu();
};