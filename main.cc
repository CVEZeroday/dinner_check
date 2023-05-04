/********************************************/
/* This source code is part of Dinner_Check */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*           File Name: main.cc             */
/*   Created by CVE_zeroday on 05.02.2023   */
/*               (T.Y.Kim)                  */
/********************************************/
// NOTE: This file is for test. Don't compile in release version.

#include <iostream>
#include "main.h"
#include "json/json.h"

int main()
{
  saveStudentData(30206, "Mason", true);
  saveStudentData(30205, "John", false);
  return 0;
}
