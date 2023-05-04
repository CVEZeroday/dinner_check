#include <iostream>
#include <fstream>
#include <ctime>

#include "json/json.h"

#define DINNER_CHECKER_API_VERSION "0.1"

#define FORMAT_DATE(n) (n < 10 ? "0"+std::to_string(n) : std::to_string(n))
#define DATE (std::to_string(t.tm_year+1900)+FORMAT_DATE(t.tm_mon+1)+FORMAT_DATE(t.tm_mday))

#ifdef _WIN64
#define JSON_PATH (".\\data\\" + DATE + "_student_dinner_data.json")
#define JSON_PATH_DATE(date_) (".\\data\\" + date_ + "_student_dinner_data.json")
#define JSON_PATH_BACKUP (".\\data\\backup_student_dinner_data.json")
#endif
#ifdef linux
#define JSON_PATH ("./data/" + DATE + "_student_dinner_data.json")
#define JSON_PATH_DATE(date_) ("./data/" + date_ + "_student_dinner_data.json")
#define JSON_PATH_BACKUP ("./data/backup_student_dinner_data.json")
#endif

#define FILE_CHECK(path) \
std::ifstream __file(path); \
if (!__file.good()) \
{ \
  initializeJsonFile(); \
}

typedef struct STUDENT_DATA
{
  std::string name;
  int id;
  bool checked;
  std::string time;
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
                          + FORMAT_DATE(t.tm_mon + 1) + "-"
                          + FORMAT_DATE(t.tm_mday) + " "
                          + FORMAT_DATE(t.tm_hour) + ":"
                          + FORMAT_DATE(t.tm_min) + ":"
                          + FORMAT_DATE(t.tm_sec);
  headerData["version"] = DINNER_CHECKER_API_VERSION;
  root["headerData"] = headerData;
  root["studentData"] = Json::arrayValue;

  try
  {
    std::ifstream i_json_file(JSON_PATH_BACKUP);
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
  FILE_CHECK(JSON_PATH);

  std::ifstream i_json_file(JSON_PATH);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  Json::Value& studentData = root["studentData"];

  Json::Value newStudent;
  newStudent["studentNumber"] = id;
  newStudent["studentName"] = name;
  newStudent["checked"] = checked;
  newStudent["checked_time"] = "";
  
  studentData.append(newStudent);

  std::ofstream o_json_file;

  o_json_file.open(JSON_PATH);
  Json::StreamWriterBuilder o_builder;
	o_builder["commentStyle"] = "None";
	o_builder["indentation"] = "    ";
  std::unique_ptr<Json::StreamWriter> writer(o_builder.newStreamWriter());

  writer->write(root, &o_json_file);
  o_json_file.close();

  std::ofstream o_json_file_backup;
  o_json_file_backup.open(JSON_PATH_BACKUP);
  writer->write(root["studentData"], &o_json_file_backup);
  o_json_file_backup.close();

  return 0;
}

inline int uncheckStudent(int id)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);
  FILE_CHECK(JSON_PATH);

  STUDENT_DATA data_;
  data_.id = 0;
  data_.name = "";
  data_.checked = false;

  std::ifstream i_json_file(JSON_PATH);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  bool flag = true;
  for (Json::Value& studentData_ : root["studentData"])
  {
    if (studentData_["studentNumber"].asInt() == id)
    {
      studentData_["checked"] = false;
      studentData_["checked_time"] = "";
      flag = false;
      break;
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

  return flag;
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
  FILE_CHECK(JSON_PATH);

  std::ifstream i_json_file(JSON_PATH);

  Json::Value root;
  i_json_file >> root;
  i_json_file.close();

  bool flag = true;
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
      flag = false;
      break;
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

  return flag;
}

/**************************/
/* getSpecificStudentData */
/**************************/
inline STUDENT_DATA getSpecificStudentData(int id)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);
  FILE_CHECK(JSON_PATH);

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
      data_.name = studentData_["studentName"].asString();
      data_.checked = studentData_["checked"].asBool();
      data_.time = studentData_["checked_time"].asString();
      break;
    }
  }
  
  return data_;
}
/********************************/
/* getSpecificStudentDataOfDate */
/********************************/
inline STUDENT_DATA getSpecificStudentDataOfDate(std::string date, int id)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);
  FILE_CHECK(JSON_PATH);

  STUDENT_DATA data_;
  data_.id = 0;
  data_.name = "";
  data_.checked = false;

  std::ifstream json_file(JSON_PATH_DATE(date), std::ifstream::binary);

  Json::Value root;
  json_file >> root;
  json_file.close();

  for (const Json::Value& studentData_ : root["studentData"])
  {
    if (studentData_["studentNumber"].asInt() == id)
    {
      data_.id = id;
      data_.name = studentData_["studentName"].asString();
      data_.checked = studentData_["checked"].asBool();
      data_.time = studentData_["checked_time"].asString();
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
  FILE_CHECK(JSON_PATH);

  std::vector<STUDENT_DATA> data_v;
  STUDENT_DATA data_;

  std::ifstream json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  json_file >> root;
  json_file.close();
  for (const Json::Value& studentData_ : root["studentData"])
  {
    data_.id = studentData_["studentNumber"].asInt();
    data_.name = studentData_["studentName"].asString();
    data_.checked = studentData_["checked"].asBool();
    data_.time = studentData_["checked_time"].asString();
    data_v.push_back(data_);
  }

  return data_v;
}

/*************************/
/* getStudentsDataOfDate */
/*************************/
inline std::vector<STUDENT_DATA> getStudentsDataOfDate(std::string date)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);
  FILE_CHECK(JSON_PATH);

  std::vector<STUDENT_DATA> data_v;
  STUDENT_DATA data_;

  std::ifstream json_file(JSON_PATH_DATE(date), std::ifstream::binary);

  Json::Value root;
  json_file >> root;
  json_file.close();
  for (const Json::Value& studentData_ : root["studentData"])
  {
    data_.id = studentData_["studentNumber"].asInt();
    data_.name = studentData_["studentName"].asString();
    data_.checked = studentData_["checked"].asBool();
    data_.time = studentData_["checked_time"].asString();
    data_v.push_back(data_);
  }

  return data_v;
}

inline int deleteStudentData(int id)
{
  struct tm t;
  time_t curr_time = time(nullptr);
  localtime_r(&curr_time, &t);
  FILE_CHECK(JSON_PATH);

  std::ifstream json_file(JSON_PATH, std::ifstream::binary);

  Json::Value root;
  json_file >> root;
  json_file.close();
  Json::Value& studentData = root["studentData"];

  bool flag = true;
  for (int i = 0; i < studentData.size(); i++)
  {
    if (studentData[i]["studentNumber"].asInt() == id)
    {
      studentData.removeIndex(i, nullptr);
      flag = false;
      break;
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

  return flag;
}
