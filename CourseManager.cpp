#include "CourseManager.hpp"

#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace registration {

void CourseManager::addStudent(const StudentRecord& record) {
    const int studentId = getId(record);
    if (students_.count(studentId) != 0) {
        throw std::invalid_argument("student already exists");
    }
    students_.emplace(studentId, record);
}

const StudentRecord& CourseManager::getStudent(int id) const {
    const auto it = students_.find(id);
    if (it == students_.end()) {
        throw std::invalid_argument("student not found");
    }
    return it->second;
}

void CourseManager::createCourse(const std::string& courseName) {
    if (courseName.empty()) {
        throw std::invalid_argument("course name must not be empty");
    }
    if (courseEnrollments_.count(courseName) != 0) {
        throw std::invalid_argument("course already exists");
    }
    courseEnrollments_.emplace(courseName, std::set<int>{});
    courseGrades_.emplace(courseName, std::map<int, double>{});
}

void CourseManager::enrollStudent(int studentId, const std::string& courseName) {
    if (students_.count(studentId) == 0) {
        throw std::invalid_argument("student not found");
    }
    const auto courseIt = courseEnrollments_.find(courseName);
    if (courseIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }
    if (!courseIt->second.insert(studentId).second) {
        throw std::invalid_argument("student already enrolled");
    }
}

bool CourseManager::isEnrolled(int studentId, const std::string& courseName) const {
    const auto courseIt = courseEnrollments_.find(courseName);
    if (courseIt == courseEnrollments_.end()) {
        return false;
    }
    return courseIt->second.count(studentId) != 0;
}

int CourseManager::getEnrollmentCount(const std::string& courseName) const {
    const auto courseIt = courseEnrollments_.find(courseName);
    if (courseIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }
    return static_cast<int>(courseIt->second.size());
}

void CourseManager::removeStudent(int studentId, const std::string& courseName) {
    const auto courseIt = courseEnrollments_.find(courseName);
    if (courseIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }
    if (courseIt->second.erase(studentId) == 0) {
        throw std::invalid_argument("student not enrolled");
    }
    const auto gradesIt = courseGrades_.find(courseName);
    if (gradesIt != courseGrades_.end()) {
        gradesIt->second.erase(studentId);
    }
}

std::vector<int> CourseManager::getEnrolledStudents(const std::string& courseName) const {
    const auto courseIt = courseEnrollments_.find(courseName);
    if (courseIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }
    return std::vector<int>(courseIt->second.begin(), courseIt->second.end());
}

std::vector<std::string> CourseManager::getStudentCourses(int studentId) const {
    if (students_.count(studentId) == 0) {
        throw std::invalid_argument("student not found");
    }

    std::vector<std::string> courses;
    for (const auto& [courseName, students] : courseEnrollments_) {
        if (students.count(studentId) != 0) {
            courses.push_back(courseName);
        }
    }
    return courses;
}

std::vector<int> CourseManager::studentsInBothCourses(const std::string& firstCourse, const std::string& secondCourse) const {
    const auto firstIt = courseEnrollments_.find(firstCourse);
    const auto secondIt = courseEnrollments_.find(secondCourse);
    if (firstIt == courseEnrollments_.end() || secondIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }

    std::vector<int> result;
    std::set_intersection(firstIt->second.begin(), firstIt->second.end(),
                          secondIt->second.begin(), secondIt->second.end(),
                          std::back_inserter(result));
    return result;
}

std::vector<int> CourseManager::studentsInEitherCourse(const std::string& firstCourse, const std::string& secondCourse) const {
    const auto firstIt = courseEnrollments_.find(firstCourse);
    const auto secondIt = courseEnrollments_.find(secondCourse);
    if (firstIt == courseEnrollments_.end() || secondIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }

    std::vector<int> result;
    std::set_union(firstIt->second.begin(), firstIt->second.end(),
                   secondIt->second.begin(), secondIt->second.end(),
                   std::back_inserter(result));
    return result;
}

void CourseManager::assignGrade(int studentId, const std::string& courseName, double grade) {
    if (grade < 0.0 || grade > 100.0) {
        throw std::invalid_argument("grade must be between 0 and 100");
    }
    if (students_.count(studentId) == 0) {
        throw std::invalid_argument("student not found");
    }
    const auto courseIt = courseEnrollments_.find(courseName);
    if (courseIt == courseEnrollments_.end()) {
        throw std::invalid_argument("course not found");
    }
    if (courseIt->second.count(studentId) == 0) {
        throw std::invalid_argument("student not enrolled");
    }
    courseGrades_[courseName][studentId] = grade;
}

double CourseManager::getCourseAverage(const std::string& courseName) const {
    const auto gradesIt = courseGrades_.find(courseName);
    if (gradesIt == courseGrades_.end() || gradesIt->second.empty()) {
        throw std::invalid_argument("course has no grades");
    }

    double sum = 0.0;
    for (const auto& [studentId, grade] : gradesIt->second) {
        (void)studentId;
        sum += grade;
    }
    return sum / static_cast<double>(gradesIt->second.size());
}

int CourseManager::getTotalStudents() const {
    return static_cast<int>(students_.size());
}

int CourseManager::getTotalCourses() const {
    return static_cast<int>(courseEnrollments_.size());
}

std::vector<std::string> CourseManager::getAllCourses() const {
    std::vector<std::string> courses;
    courses.reserve(courseEnrollments_.size());
    for (const auto& [courseName, students] : courseEnrollments_) {
        (void)students;
        courses.push_back(courseName);
    }
    return courses;
}

std::vector<int> CourseManager::getAllStudentIds() const {
    std::vector<int> ids;
    ids.reserve(students_.size());
    for (const auto& [studentId, record] : students_) {
        (void)record;
        ids.push_back(studentId);
    }
    return ids;
}

} // namespace registration
