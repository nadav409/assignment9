#pragma once

#include "StudentRecord.hpp"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace registration {

class CourseManager {
public:
    void addStudent(const StudentRecord& record);
    const StudentRecord& getStudent(int id) const;
    void createCourse(const std::string& courseName);
    void enrollStudent(int studentId, const std::string& courseName);
    bool isEnrolled(int studentId, const std::string& courseName) const;
    int getEnrollmentCount(const std::string& courseName) const;
    void removeStudent(int studentId, const std::string& courseName);
    std::vector<int> getEnrolledStudents(const std::string& courseName) const;
    std::vector<std::string> getStudentCourses(int studentId) const;
    std::vector<int> studentsInBothCourses(const std::string& firstCourse, const std::string& secondCourse) const;
    std::vector<int> studentsInEitherCourse(const std::string& firstCourse, const std::string& secondCourse) const;
    void assignGrade(int studentId, const std::string& courseName, double grade);
    double getCourseAverage(const std::string& courseName) const;
    int getTotalStudents() const;
    int getTotalCourses() const;
    std::vector<std::string> getAllCourses() const;
    std::vector<int> getAllStudentIds() const;

private:
    std::map<int, StudentRecord> students_;
    std::map<std::string, std::set<int>> courseEnrollments_;
    std::map<std::string, std::map<int, double>> courseGrades_;
};

} // namespace registration
