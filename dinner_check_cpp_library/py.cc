/********************************************/
/* This source code is part of Dinner_Check */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*            File Name: py.cc              */
/*   Created by CVE_zeroday on 05.02.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

#include "json/json.h"
// external library headers

//#include <python3.11/Python.h>
#include <python3.10/Python.h>
#include <memory>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
// system headers

#include "main.h"
// project headers

void thrd_initTimer()
{
  std::cout << "timer thread initialized!\n";
  while(1)
  {
    std::time_t now = std::time(nullptr);
    std::tm* currentTime = std::localtime(&now);

    std::tm scheduledTime = *currentTime;
    scheduledTime.tm_hour = 0;
    scheduledTime.tm_min = 0;
    scheduledTime.tm_sec = 0;

    std::time_t scheduledTimestamp = std::mktime(&scheduledTime);
    std::time_t nextDayTimestamp = scheduledTimestamp + 24 * 60 * 60;
    int remainingTime = nextDayTimestamp - now;

    std::this_thread::sleep_for(std::chrono::seconds(remainingTime));

    initializeJsonFile(true);
  }
}

__attribute__((constructor)) void init()
{
  std::cout << "dinnerchecker library loaded successfully\n";
  initializeJsonFile(false);
  std::cout << "initializing timer thread...\n";
  std::thread timerThread(thrd_initTimer);
  timerThread.detach();
}

static PyObject* py_initializeJsonFile(PyObject* self, PyObject* args)
{
  int result = initializeJsonFile(false);

  return Py_BuildValue("i", result);
}
static PyObject* py_resetJsonFile(PyObject* self, PyObject* args)
{
  int result = initializeJsonFile(true);

  return Py_BuildValue("i", result);
}

static PyObject* py_saveStudentData(PyObject* self, PyObject* args)
{
  int id;
  const char* name;
  int checked;

  if (!PyArg_ParseTuple(args, "isi", &id, &name, &checked)) {
    return NULL;
  }

  int result = saveStudentData(id, name, checked);

  return Py_BuildValue("i", result);
}

static PyObject* py_uncheckStudent(PyObject* self, PyObject* args)
{
  int id;
  if (!PyArg_ParseTuple(args, "i", &id)) {
    return NULL;
  }

  int result = uncheckStudent(id);

  return Py_BuildValue("i", result);
}

static PyObject* py_checkStudent(PyObject* self, PyObject* args)
{
  int id;
  if (!PyArg_ParseTuple(args, "i", &id)) {
    return NULL;
  }

  int result = checkStudent(id);

  return Py_BuildValue("i", result);
}

static PyObject* py_getSpecificStudentDataOfDate(PyObject* self, PyObject* args)
{
  int id;
  const char* date;
  if (!PyArg_ParseTuple(args, "si", &date, &id))
  {
    return NULL;
  }

  STUDENT_DATA result = getSpecificStudentDataOfDate(date, id);

  PyObject* dict = PyDict_New();
  PyDict_SetItemString(dict, "studentNumber", PyLong_FromLong(result.id));
  PyDict_SetItemString(dict, "name", PyUnicode_FromString(result.name.c_str()));
  PyDict_SetItemString(dict, "isChecked", result.checked ? Py_True : Py_False);
  PyDict_SetItemString(dict, "date", PyUnicode_FromString(result.time.c_str()));

  return dict;
}

static PyObject* py_getSpecificStudentData(PyObject* self, PyObject* args)
{
  int id;
  if (!PyArg_ParseTuple(args, "i", &id))
  {
    return NULL;
  }

  STUDENT_DATA result = getSpecificStudentData(id);

  PyObject* dict = PyDict_New();
  PyDict_SetItemString(dict, "studentNumber", PyLong_FromLong(result.id));
  PyDict_SetItemString(dict, "name", PyUnicode_FromString(result.name.c_str()));
  PyDict_SetItemString(dict, "isChecked", result.checked ? Py_True : Py_False);
  PyDict_SetItemString(dict, "date", PyUnicode_FromString(result.time.c_str()));

  return dict;
}

static PyObject* py_getStudentsData(PyObject* self, PyObject* args)
{
  std::vector<STUDENT_DATA> results = getStudentsData();

  PyObject* list = PyList_New(results.size());
  for (size_t i = 0; i < results.size(); i++) 
  {
    STUDENT_DATA result = results[i];
    PyObject* dict = PyDict_New();

    PyDict_SetItemString(dict, "studentNumber", PyLong_FromLong(result.id));
    PyDict_SetItemString(dict, "name", PyUnicode_FromString(result.name.c_str()));
    PyDict_SetItemString(dict, "isChecked", result.checked ? Py_True : Py_False);
    PyDict_SetItemString(dict, "date", PyUnicode_FromString(result.time.c_str()));
    PyList_SetItem(list, i, dict);
  }

  return list;
}

static PyObject* py_getStudentsDataOfDate(PyObject* self, PyObject* args)
{
  const char* date;
  if (!PyArg_ParseTuple(args, "s", &date)) {
    return NULL;
  }

  std::vector<STUDENT_DATA> results = getStudentsDataOfDate(date);

  PyObject* list = PyList_New(results.size());
  for (size_t i = 0; i < results.size(); i++) 
  {
    STUDENT_DATA result = results[i];
    PyObject* dict = PyDict_New();

    PyDict_SetItemString(dict, "studentNumber", PyLong_FromLong(result.id));
    PyDict_SetItemString(dict, "name", PyUnicode_FromString(result.name.c_str()));
    PyDict_SetItemString(dict, "isChecked", result.checked ? Py_True : Py_False);
    PyDict_SetItemString(dict, "date", PyUnicode_FromString(result.time.c_str()));
    PyList_SetItem(list, i, dict);
  }

  return list;
}

/*
static PyObject* py_deleteStudentData(PyObject* self, PyObject* args)
{
  int id;
  if (!PyArg_ParseTuple(args, "i", &id)) {
    return NULL;
  }

  int result = deleteStudentData(id);

  return Py_BuildValue("i", result);
}

static PyObject* py_deleteAllStudentsData(PyObject* self, PyObject* args)
{
  int result = deleteAllStudentsData();

  return Py_BuildValue("i", result);
}
*/

static PyMethodDef myMethods[] = {
  {"initializeJsonFile", py_initializeJsonFile, METH_NOARGS, "Initialize the Json File to write.\ninput: none\noutput: 0 (fixed)\nNote: Don't use in normal situation. May cause critical error."},
  {"resetJsonFile", py_resetJsonFile, METH_NOARGS, "Reset the Json File.\ninput: none\noutput: 0 (fixed)\nNote: Don't use in normal situation. May cause critical error. !!! THIS FUNCTIONS IS FOR DEBUG !!!"},
  {"saveStudentData", py_saveStudentData, METH_VARARGS, "Save Student Data to .json file.\ninput: (int student_number, str student_name, bool student_is_checked)\noutput: 0 (fixed)"},
  {"uncheckStudent", py_uncheckStudent, METH_VARARGS, "Uncheck the Student.\ninput: (int student_number)\noutput: 0 if executed normally, 1 if there is no matching student"},
  {"checkStudent", py_checkStudent, METH_VARARGS, "Check the Student.\ninput: (int student_number)\noutput: 0 if executed normally, 1 if there is no matching student"},
  {"getSpecificStudentData", py_getSpecificStudentData, METH_VARARGS, "Get the Data of Specific Student.\ninput: (int student_number)\noutput: Dictionary { \"studentNumber\":student_number, \"name\":student_name, \"isChecked\":student_is_checked }"},
  {"getSpecificStudentDataOfDate", py_getSpecificStudentDataOfDate, METH_VARARGS, "Get the Data of Specific Student of Specific Date.\ninput: (str date, int student_number)\noutput: Dictionary { \"studentNumber\":student_number, \"name\":student_name, \"isChecked\":student_is_checked }. If there is no data of the date, It'll return a dictionary whose student number is -1."},
  {"getStudentsData", py_getStudentsData, METH_NOARGS, "Get the Data of All Students.\ninput: none\noutput: List of Dictionary { \"studentNumber\":student_number, \"name\":student_name, \"isChecked\":student_is_checked }"},
  {"getStudentsDataOfDate", py_getStudentsDataOfDate, METH_VARARGS, "Get the Data of All Students of Specific Date.\ninput: (str date)\noutput: List of Dictionary {\"studentNumber\":student_number, \"name\":student_name, \"isChecked\":student_is_checked }. If there is no data of the date, It'll return an empty list."},
  //{"deleteStudentData", py_deleteStudentData, METH_VARARGS, "Delete the Data of Specific Student.\ninput: (int student_number)\noutput: 0 if executed normally, 1 if there is no matching student"},
  //{"deleteAllStudentsData", py_deleteAllStudentsData, METH_VARARGS, "Delete the Data of All Students.\ninput: none\noutput: 0 (fixed)"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef myModule = {
  PyModuleDef_HEAD_INIT,
  "dinnerchecker",
  "A Python module for checking dinner of Byeongjeoom Highschool",
  -1,
  myMethods
};

PyMODINIT_FUNC PyInit_dinnerchecker(void)
{
  return PyModule_Create(&myModule);
}
