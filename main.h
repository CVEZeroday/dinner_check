#include <iostream>
#include <fstream>
#include <ctime>

#include "json/json.h"

#ifdef _WIN64
#include <io.h>
#endif
#ifdef linux
#include <unistd.h>
#endif

#define DINNER_CHECKER_API_VERSION "0.1"

#ifdef _WIN64
#define JSON_PATH (".\\data\\" + std::to_string(t.tm_year+1900)+std::to_string(t.tm_mon+1)+std::to_string(t.tm_mday)+ "_student_dinner_data.json")
#define JSON_PATH_BACKUP (".\\data\\backup_student_dinner_data.json")
#endif
#ifdef linux
#define JSON_PATH ("./data/" + std::to_string(t.tm_year+1900)+std::to_string(t.tm_mon+1)+std::to_string(t.tm_mday)+ "_student_dinner_data.json")
#define JSON_PATH_BACKUP ("./data/backup_student_dinner_data.json")
#endif

#define FILE_CHECK() \
if (access(JSON_PATH.c_str(), 0) != -1) \
{ \
  initializeJsonFile(); \
}

typedef struct STUDENT_DATA
{
  std::string name;
  int id;
  bool checked;
  long time;
} STUDENT_DATA;
// 9 Bytes

inline int initializeJsonFile()
{
  Json::Value root;
  Json::Value headerData;
  Json::Value studentData;
 
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);

  Json::Value date;
  date.append(t.tm_year + 1900);
  date.append(t.tm_mon + 1);
  date.append(t.tm_mday);
  date.append(t.tm_hour);
  date.append(t.tm_min);
  date.append(t.tm_sec);

  headerData["date"] = date;
  headerData["date_str"] = std::to_string(t.tm_year + 1900) + "-"
                          + std::to_string(t.tm_mon + 1) + "-"
                          + std::to_string(t.tm_mday) + " "
                          + std::to_string(t.tm_hour) + ":"
                          + std::to_string(t.tm_min) + ":"
                          + std::to_string(t.tm_sec);
  headerData["version"] = DINNER_CHECKER_API_VERSION;
  root["headerData"] = headerData;

  try
  {
    std::ifstream i_json_file(JSON_PATH_BACKUP, std::ifstream::binary);
    i_json_file >> studentData;
    i_json_file.close();

    for (Json::Value& studentData_ : root["studentData"])
    {
      studentData_["checked"] = false;
      studentData_["checked_time"] = "";
    }
  } catch(std::exception err) {}

  Json::StreamWriterBuilder o_builder;
	o_builder["commentStyle"] = "None";
	o_builder["indentation"] = "    ";
  std::unique_ptr<Json::StreamWriter> writer(o_builder.newStreamWriter());

  std::ofstream o_json_file;
  o_json_file.open(JSON_PATH);

  writer->write(root, &o_json_file);
  o_json_file.close();

  return 0;
}

inline int saveStudentData(int id, const std::string& name, bool checked)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);
  FILE_CHECK();

  std::ofstream o_json_file;

  std::ifstream i_json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  Json::Value studentData;
  studentData["studentNumber"] = id;
  studentData["studentName"] = name;
  studentData["checked"] = checked;
  studentData["checked_time"] = "";

  //try
  //{
    root["studentData"].append(studentData);
  //} catch(std::exception err)
  //{
  //  root["studentData"] = studentData;
  //}

  o_json_file.open(JSON_PATH);
  Json::StreamWriterBuilder o_builder;
	o_builder["commentStyle"] = "None";
	o_builder["indentation"] = "    ";
  std::unique_ptr<Json::StreamWriter> writer(o_builder.newStreamWriter());

  writer->write(root, &o_json_file);
  o_json_file.close();

  std::ofstream o_json_file_backup;
  o_json_file_backup.open(JSON_PATH_BACKUP);
  writer->write(studentData, &o_json_file_backup);
  o_json_file_backup.close();

  return 0;
}

inline int uncheckStudent(int id)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);

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
      studentData_["checked"] = false;
      studentData_["checked_time"] = "";
    }
  }

  std::ofstream o_json_file(JSON_PATH, std::ofstream::binary);
  o_json_file << root;
  o_json_file.close();

  Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "    ";
  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

  writer->write(root, &o_json_file);

  return 0;
}

inline int checkStudent(int id)
{
  STUDENT_DATA data_;
  data_.id = 0;
  data_.name = "";
  data_.checked = false;

  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);

  std::ifstream i_json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  for (Json::Value& studentData_ : root["studentData"])
  {
    if (studentData_["studentNumber"].asInt() == id)
    {
      studentData_["checked"] = true;
      studentData_["checked_time"] = std::to_string(t.tm_year + 1900) + "-"
                                  + std::to_string(t.tm_mon + 1) + "-"
                                  + std::to_string(t.tm_mday) + " "
                                  + std::to_string(t.tm_hour) + ":"
                                  + std::to_string(t.tm_min) + ":"
                                  + std::to_string(t.tm_sec);
    }
  }

  std::ofstream o_json_file(JSON_PATH, std::ofstream::binary);
  o_json_file << root;
  o_json_file.close();

  Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "    ";
  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

  writer->write(root, &o_json_file);

  return 0;
}

/**************************/
/* getSpecificStudentData */
/**************************/
inline STUDENT_DATA getSpecificStudentData(int id)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);

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
      data_.time = studentData_["checked_time"].asInt();
      break;
    }
  }
  
  return data_;
}

/*******************/
/* getStudentsData */
/*******************/
inline std::vector<STUDENT_DATA> getStudentsData()
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);

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
    data_.time = studentData_["checked_time"].asInt();
    data_v.push_back(data_);
  }

  return data_v;
}

