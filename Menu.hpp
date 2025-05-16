#pragma once

#include <iostream>
#include <string>

#include "Student.hpp"
#include "Classroom.hpp"
#include "CSV-Grades.hpp"

class Menu
{
private:
  int user_choice = 0;

  CSV_Grades csv_handler;
  Classroom classroom;

public:
  Menu();
};

Menu::Menu()
{
}