#include "Menu.h"

Menu::Menu()
{
  // Display menu and handle user choices
  bool exit_menu = false;

  while (!exit_menu)
  {
    std::cout << "\n=== SISTEMA DE REVISIÓN DE CALIFICACIONES ===\n";
    std::cout << "1. Leer archivo de texto de entrada\n";
    std::cout << "2. Imprimir calificaciones\n";
    std::cout << "3. Información general\n";
    std::cout << "4. Mostrar alumnos reprobados\n";
    std::cout << "5. Insertar nuevo alumno\n";
    std::cout << "6. Eliminar alumno\n";
    std::cout << "7. Salir\n";
    std::cout << "Ingrese su opción: ";

    if (!(std::cin >> user_choice))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Opción inválida. Por favor ingrese un número.\n";
      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (user_choice)
    {
    case 1:
      load_file();
      break;
    case 2:
      print_grades();
      break;
    case 3:
      general_info();
      break;
    case 4:
      show_failing_students();
      break;
    case 5:
      add_new_student();
      break;
    case 6:
      remove_student();
      break;
    case 7:
      exit_menu = true;
      break;
    default:
      std::cout << "Opción inválida. Por favor intente de nuevo.\n";
    }
  }
}

void Menu::load_file()
{
  std::string filename;
  std::cout << "Ingrese el nombre del archivo (incluya la ruta si es necesario): ";
  std::getline(std::cin, filename);

  if (csv_handler.open_file_to_read(filename))
  {
    return;
  }

  // Read students from file and add them to classroom
  classroom = Classroom(csv_handler.read_students_from_file());
  students_are_loaded = true;

  std::cout << "Se han cargado los estudiantes del archivo.\n";
}

void Menu::print_grades()
{
  if (!students_are_loaded)
  {
    std::cerr << "Error: Primero debe cargar un archivo de estudiantes (opción 1).\n";
    return;
  }

  std::string output_filename;
  std::cout << "Ingrese el nombre del archivo de salida: ";
  std::getline(std::cin, output_filename);

  // Open output file
  if (csv_handler.open_file_to_overwrite(output_filename))
  {
    return;
  }

  // Write header to output file
  csv_handler.write_header_to_file();

  // Display grades and write to output file
  std::cout << "\n=== CALIFICACIONES DE ESTUDIANTES ===\n";
  std::cout << "Nombre Apellido, Parcial 1, Parcial 2, Parcial 3, Edad.\n";

  for (Student s : classroom.get_student_list())
  {
    std::cout << s.to_pretty_string() + "\n";
    csv_handler.write_student_to_file(s);
  }

  std::cout << "Calificaciones guardadas en el archivo: " << csv_handler.get_opened_file_write() << "\n";
  csv_handler.end_file_write();
}

void Menu::general_info()
{
  if (!students_are_loaded)
  {
    std::cout << "Error: Primero debe cargar un archivo de estudiantes (opción 1).\n";
    return;
  }

  // Count underage students
  int underage_count = 0;
  for (Student s : classroom.get_student_list())
  {
    if (s.is_underage())
    {
      underage_count++;
    }
  }

  // Display information
  std::cout << "\n=== INFORMACIÓN GENERAL ===\n";

  std::cout << "Estudiante con el promedio más alto: " + classroom.top_student().get_full_name()
            << ", calif: " << classroom.top_student().grade_average() << "\n";

  std::cout << "Cantidad de estudiantes reprobados: " << classroom.failing_students().size() << "\n";
  std::cout << "Cantidad de estudiantes menores de edad: " << underage_count << "\n";
}

void Menu::show_failing_students()
{
  if (!students_are_loaded)
  {
    std::cout << "Error: Primero debe cargar un archivo de estudiantes (opción 1).\n";
    return;
  }

  // Display failing students
  std::cout << "\n=== ALUMNOS REPROBADOS ===\n";

  if (classroom.failing_students().empty())
  {
    std::cout << "No hay alumnos reprobados.\n";
    return;
  }

  for (Student s : classroom.failing_students())
  {
    std::cout << s.get_full_name() << ", Promedio: " << s.grade_average() << "\n";
  }
}

void Menu::add_new_student()
{
  if (!students_are_loaded)
  {
    std::cout << "Error: Primero debe cargar un archivo de estudiantes (opción 1).\n";
    return;
  }

  std::string first_name, last_name;
  int midterm_grades[Student::NO_OF_MIDTERMS];
  int age;

  std::cout << "\n=== AGREGAR NUEVO ESTUDIANTE ===\n";

  std::cout << "Ingrese el nombre: ";
  std::getline(std::cin, first_name);

  std::cout << "Ingrese el apellido: ";
  std::getline(std::cin, last_name);

  for (int i = 0; i < Student::NO_OF_MIDTERMS; i++)
  {
    std::cout << "Ingrese la calificación del parcial " << (i + 1) << ": ";
    std::cin >> midterm_grades[i];
    if (midterm_grades[i] > 100 || midterm_grades[i] < 0)
    {
      std::cout << "Calificación inválida. Se asignará valor de 0.\n";
      midterm_grades[i] = 0;
    }
  }

  std::cout << "Ingrese la edad: ";
  std::cin >> age;
  if (age < 0)
  {
    std::cout << "Edad inválida. Se asignará valor de 0.\n";
    age = 0;
  }

  // Create new student
  Student new_student(first_name, last_name, midterm_grades, age);

  // Add student to classroom
  classroom.add_student(new_student);

  // Append student to original file
  csv_handler.open_file_to_write(original_filename);
  csv_handler.write_student_to_file(new_student);

  std::cout << "Estudiante agregado correctamente.\n";
}

void Menu::remove_student()
{
  if (!students_are_loaded)
  {
    std::cout << "Error: Primero debe cargar un archivo de estudiantes (opción 1).\n";
    return;
  }

  std::string first_name, last_name, full_name;

  std::cout << "\n=== ELIMINAR ESTUDIANTE ===\n";

  std::cout << "Ingrese el nombre: ";
  std::getline(std::cin, first_name);

  std::cout << "Ingrese el apellido: ";
  std::getline(std::cin, last_name);

  full_name = first_name + " " + last_name;

  // Find student positions
  std::vector<size_t> matches = classroom.matching_names(full_name);

  if (matches.empty())
  {
    std::cout << "No se encontró ningún estudiante con ese nombre.\n";
    return;
  }

  // If multiple matches, show them
  if (matches.size() > 1)
  {
    std::cout << "Se encontraron múltiples estudiantes con ese nombre:\n";
    std::vector<Student> students = classroom.get_student_list();

    for (size_t i = 0; i < matches.size(); i++)
    {
      std::cout << (i + 1) << ". " << students[matches[i]].get_full_name()
                << " (Promedio: " << students[matches[i]].grade_average() << ")\n";
    }

    size_t choice;
    std::cout << "Ingrese el número del estudiante que desea eliminar (0 para cancelar): ";
    std::cin >> choice;

    if (choice > matches.size())
    {
      std::cout << "Selección inválida. Operación cancelada.\n";
      return;
    }
    else if (choice == 0)
    {
      std::cout << "Operación cancelada.\n";
      return;
    }

    char confirm;
    std::cout << "¿Está seguro de que desea eliminar a este estudiante? (s/n): ";
    std::cin >> confirm;

    if (tolower(confirm) != 's')
    {
      std::cout << "Operación cancelada.\n";
      return;
    }

    // Remove student
    classroom.remove_student(matches[choice - 1]);

    // Update the original file with all remaining students
    csv_handler.update_file(classroom.get_student_list());

    std::cout << "Estudiante eliminado correctamente.\n";
  }
  else
  {
    // Only one match
    char confirm;
    std::cout << "¿Está seguro de que desea eliminar a este estudiante? (S/N): ";
    std::cin >> confirm;

    if (tolower(confirm) != 's')
    {
      std::cout << "Operación cancelada.\n";
      return;
    }

    // Remove student
    classroom.remove_student(matches[0]);

    // Update the original file with all remaining students
    csv_handler.update_file(classroom.get_student_list());

    std::cout << "Estudiante eliminado correctamente.\n";
  }
}