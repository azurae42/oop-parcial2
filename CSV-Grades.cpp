#include "CSV-Grades.h"

CSV_Grades::CSV_Grades() {}

std::string CSV_Grades::get_opened_file_read() const
{
  return opened_file_to_read;
}

std::string CSV_Grades::get_opened_file_write() const
{
  return opened_file_to_write;
}

int CSV_Grades::my_stoi(const std::string &s_) const
{
  // value to return
  int integer = 0;
  for (int i = s_.size() - 1, pwr = 1; i >= 0; i--, pwr *= 10)
  {
    if (i != 0 && !isdigit(s_[i]))
    {
      return 0;
    }
    else if (i == 0 && s_[i] == '-')
    {
      return integer * -1;
    }

    integer += (s_[i] - '0') * pwr;
  }

  return integer;
}

Student CSV_Grades::parse_line(const std::string &line_) const
{
  static const int NO_OF_COMMAS = 5;
  static const int NO_OF_VALUES = NO_OF_COMMAS + 1;

  size_t comma_positions[NO_OF_COMMAS] = {};

  // the six substrings before converting to appropiate type
  // Format:        FirstName,LastName,Midterm1,Midterm2,Midterm3,Age
  // Value Types:   string,   string, int,      int,     int,     int
  std::string values[NO_OF_VALUES];

  for (size_t i = 0, prev_pos = 0; i < NO_OF_COMMAS; prev_pos = comma_positions[i], i++)
  {
    comma_positions[i] = line_.find(',', prev_pos) + 1;
  }

  for (size_t i = 0, prev_pos = 0; i < NO_OF_VALUES; i++, prev_pos = comma_positions[i - 1])
  {
    values[i] = line_.substr(prev_pos, comma_positions[i] - (prev_pos + 1));
  }

  return {values[0], values[1], {my_stoi(values[2]), my_stoi(values[3]), my_stoi(values[4])}, my_stoi(values[5])};
}

bool CSV_Grades::open_file_to_read(const std::string &filename_read_)
{
  if (!opened_file_to_read.empty())
  {
    std::cout << "Cerrando archivo anterior...\n";
    end_file_read();
  }

  in.open(filename_read_);

  if (!in.good())
  {
    std::cerr << "read err: file could not be opened.\n";
    end_file_read();
    return true;
  }
  else
  {
    opened_file_to_read = filename_read_;
  }
  return false;
}

bool CSV_Grades::open_file_to_write(const std::string &filename_write_)
{
  if (!opened_file_to_write.empty())
  {
    std::cout << "Cerrando archivo anterior...\n";
    end_file_write();
  }

  out.open(filename_write_, std::ios::app);

  if (!out.good())
  {
    std::cerr << "write err: file could not be opened.\n";
    end_file_write();
    return true;
  }
  else
  {
    opened_file_to_write = filename_write_;
  }
  return false;
}

bool CSV_Grades::open_file_to_overwrite(const std::string &filename_overwrite_)
{
  if (!opened_file_to_write.empty())
  {
    std::cout << "Cerrando archivo anterior...\n";
    end_file_write();
  }

  out.open(filename_overwrite_, std::ios::trunc);

  if (!out.good())
  {
    std::cerr << "err: file could not be opened.\n";
    end_file_write();
    return true;
  }
  else
  {
    opened_file_to_write = filename_overwrite_;
  }
  return false;
}

std::vector<Student> CSV_Grades::read_students_from_file()
{
  std::vector<Student> students;
  std::string line;

  // Skip header line
  std::getline(in, line);

  // Read each student line
  while (std::getline(in, line))
  {
    if (!line.empty())
    {
      Student student = parse_line(line);
      students.push_back(student);
    }
  }

  return students;
}

void CSV_Grades::write_header_to_file()
{
  static const std::string HEADER = "Nombre,Apellido,Parcial1,Parcial2,Parcial3,Edad";
  out << HEADER << "\n";
}

void CSV_Grades::write_student_to_file(const Student &s_)
{
  out << s_.to_csv_line() << "\n";
}

void CSV_Grades::update_file(const std::vector<Student> &s_list)
{
  open_file_to_overwrite(opened_file_to_read);
  write_header_to_file();
  for (Student s : s_list)
  {
    out << s.to_csv_line() << "\n";
  }
  end_file_write();
}

void CSV_Grades::end_file_read()
{
  in.close();
  opened_file_to_read = "";
}

void CSV_Grades::end_file_write()
{
  out.close();
  opened_file_to_write = "";
}
