#include <iostream>
#include <string>

struct student
{
  std::string fname;
  std::string lname;
  int midterms[3];
  int age;
};

int str_to_int(const std::string &s_)
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

student parse(const std::string &l_)
{
  // comma positions.
  size_t div[5];
  // the six substrings before converting to appropiate type
  std::string substr[6];

  return {"XD", "XDD", 1, 2, 3, 18};
}

void print_student(const student &s_)
{
  std::cout << "student:\nfirst name: " + s_.fname + "\nlast name: " + s_.lname + "\nmidterm grades: " << s_.midterms[0] << ", " << s_.midterms[1] << ", " << s_.midterms[2] << "\nage: " << s_.age << std::endl;
}

int main()
{
  std::cout << str_to_int("12 8");
  // Interface run;
  return 0;
}