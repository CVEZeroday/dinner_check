#include <iostream>
#include "main.h"
#include "json/json.h"

int main()
{
  initializeJsonFile();
  saveStudentData(30206, "Mason", true);
  saveStudentData(30205, "John", false);
  checkStudent(30205);
  uncheckStudent(30206);
  return 0;
}
