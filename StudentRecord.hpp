#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace registration {

using StudentRecord = std::tuple<std::string, int, double>;

StudentRecord createRecord(const std::string& name, int id, double grade);
const std::string& getName(const StudentRecord& record);
int getId(const StudentRecord& record);
double getGrade(const StudentRecord& record);
void unpackRecord(const StudentRecord& record, std::string& name, int& id, double& grade);
std::string formatRecord(const StudentRecord& record);
double averageGrade(const std::vector<StudentRecord>& records);
StudentRecord bestStudent(const std::vector<StudentRecord>& records);
std::vector<StudentRecord> sortByGrade(const std::vector<StudentRecord>& records);
std::vector<StudentRecord> sortByName(const std::vector<StudentRecord>& records);
std::vector<StudentRecord> filterByGrade(const std::vector<StudentRecord>& records, double minGrade);

} // namespace registration
