#include "json/json.h"
#include <python3.11/Python.h>

#include "main.h"

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

static PyObject* py_checkStudent(PyObject* self, PyObject* args)
{
  int id;
  if (!PyArg_ParseTuple(args, "i", &id)) {
    return NULL;
  }

  int result = checkStudent(id);

  return Py_BuildValue("i", result);
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
    PyList_SetItem(list, i, dict);
  }

  return list;
}

static PyMethodDef myMethods[] = {
  {"saveStudentData", py_saveStudentData, METH_VARARGS, "Save Student Data to .json file.\ninput: (int student_number, int student_name, bool student_is_checked)\noutput: 0 if executed normally, 1 if executed with error"},
  {"checkStudent", py_checkStudent, METH_VARARGS, "Check the Student.\ninput: (int student_number)\noutput: 0 if executed normally, 1 if executed with error"},
  {"getSpecificStudentData", py_getSpecificStudentData, METH_VARARGS, "Get the Data of Specific Student.\ninput: (int student_number)\noutput: Dictionary { \"studentNumber\":student_number, \"name\":student_name, \"isChecked\":student_is_checked }"},
  {"getStudentsData", py_getStudentsData, METH_NOARGS, "Get the Data of All Students.\ninput: none\noutput: List of Dictionary { \"studentNumber\":student_number, \"name\":student_name, \"isChecked\":student_is_checked "},
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
