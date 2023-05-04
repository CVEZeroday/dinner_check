#include <iostream>
#include "main.h"
#include "json/json.h"

int main()
{
  saveStudentData(30206, "Mason", true);
  saveStudentData(30205, "John", false);
  return 0;
}
