#include <iostream>
#include <fstream>
#include "json.h"

#define JSON_PATH "./dinner_checker_student_data.json"

// STUDENT_DATA.name == student name
// STUDENT_DATA.id == student number
// STUDENT_DATA.data == bitmask
typedef struct STUDENT_DATA
{
  const char *name;
  int id;
  bool checked;
} STUDENT_DATA;
// 16 Bytes

int saveStudentData(int id, std::string name, bool checked)
{
  std::ifstream i_json_file(JSON_PATH, std::ifstream::binary);
  std::ofstream o_json_file(JSON_PATH, std::ofstream::binary);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  Json::Value studentData;
  studentData["studentNumber"] = id;
  studentData["studentName"] = name;
  studentData["checked"] = false;

  root.append(studentData);

  Json::StreamWriterBuilder builder;
  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

  writer->write(root, &std::cout);
  writer->write(root, &o_json_file);

  return 0;
}

// toggleStudent.argtypes = (c.c_wchar_p)
// toggleStudent.restype = c.c_int
// input : student id to toggle
// output : exec code (0: executed normally, 1: error)
int toggleStudent(int id)
{
  STUDENT_DATA data_;
  data_.id = 0;
  data_.name = "";
  data_.checked = false;

  std::ifstream i_json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  for (Json::Value& studentData_ : root["studentData"])
  {
    if (studentData_["studentNumber"].asInt() == id)
    {
      studentData_["checked"] = true;
    }
  }

  std::ofstream o_json_file(JSON_PATH, std::ofstream::binary);
  o_json_file << root;
  o_json_file.close();

  return 0;
}

// getSpecificStudentData.argtypes = (c.c_wchar_p)
// getSpecificStudentData.restype = STUDENT_DATA
// input : student id to get data
// output : STUDENT_DATA stucture of id, returns (id 0) if there is no userdata of id.
STUDENT_DATA getSpecificStudentData(int id)
{
  STUDENT_DATA data_;
  data_.id = 0;
  data_.name = "";
  data_.checked = false;

  std::ifstream json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  json_file >> root;
  json_file.close();

  for (const Json::Value& studentData_ : root["studentData"])
  {
    if (studentData_["studentNumber"].asInt() == id)
    {
      data_.id = id;
      data_.name = studentData_["studentName"].asCString();
      data_.checked = studentData_["checked"].asBool();
      break;
    }
  }
  
  return data_;
}

// getStudentsData.argtypes = none
// getStudentsData.restype = vector<STUDENT_dATA>
// input : none
// output : Data of all of the students
std::vector<STUDENT_DATA> getStudentsData()
{
  std::vector<STUDENT_DATA> data_v;
  STUDENT_DATA data_;

  std::ifstream json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  json_file >> root;
  json_file.close();

  for (const Json::Value& studentData_ : root["studentData"])
  {
    data_.id = studentData_["studentNumber"].asInt();
    data_.name = studentData_["studentName"].asCString();
    data_.checked = studentData_["checked"].asBool();
    data_v.push_back(data_);
  }

  return data_v;
}
