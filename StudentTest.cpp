#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "CourseManager.hpp"
#include "StringUtils.hpp"
#include "StudentRecord.hpp"
#include "TypeTraitsUtils.hpp"

#include <fstream>

using namespace registration;

TEST_CASE("StudentTest createRecord") {
    auto record = createRecord("Alice", 1, 91.5);
    CHECK(getName(record) == "Alice");
    CHECK(getId(record) == 1);
    CHECK(getGrade(record) == doctest::Approx(91.5));
}

TEST_CASE("StudentTest createRecord invalid id") {
    CHECK_THROWS_AS(createRecord("Alice", 0, 50.0), std::invalid_argument);
}

TEST_CASE("StudentTest createRecord invalid grade") {
    CHECK_THROWS_AS(createRecord("Alice", 1, -1.0), std::invalid_argument);
}

TEST_CASE("StudentTest unpackRecord") {
    auto record = createRecord("Bob", 2, 80.0);
    std::string name;
    int id = 0;
    double grade = 0.0;
    unpackRecord(record, name, id, grade);
    CHECK(name == "Bob");
    CHECK(id == 2);
    CHECK(grade == doctest::Approx(80.0));
}

TEST_CASE("StudentTest formatRecord") {
    auto record = createRecord("Cara", 3, 77.7);
    CHECK(formatRecord(record) == "Cara (ID: 3, Grade: 77.7)");
}

TEST_CASE("StudentTest averageGrade") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 80.0),
        createRecord("B", 2, 90.0)
    };
    CHECK(averageGrade(records) == doctest::Approx(85.0));
}

TEST_CASE("StudentTest bestStudent") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 80.0),
        createRecord("B", 2, 95.0)
    };
    CHECK(getName(bestStudent(records)) == "B");
}

TEST_CASE("StudentTest sortByGrade") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 80.0),
        createRecord("B", 2, 95.0),
        createRecord("C", 3, 85.0)
    };
    auto sorted = sortByGrade(records);
    CHECK(getName(sorted[0]) == "B");
    CHECK(getName(sorted[2]) == "A");
}

TEST_CASE("StudentTest sortByName") {
    std::vector<StudentRecord> records = {
        createRecord("Charlie", 3, 70.0),
        createRecord("Alice", 1, 90.0),
        createRecord("Bob", 2, 80.0)
    };
    auto sorted = sortByName(records);
    CHECK(getName(sorted[0]) == "Alice");
    CHECK(getName(sorted[1]) == "Bob");
    CHECK(getName(sorted[2]) == "Charlie");
}

TEST_CASE("StudentTest filterByGrade") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 60.0),
        createRecord("B", 2, 70.0),
        createRecord("C", 3, 90.0)
    };
    auto filtered = filterByGrade(records, 65.0);
    CHECK(filtered.size() == 2);
}

TEST_CASE("StudentTest CourseManager add and fetch") {
    CourseManager cm;
    cm.addStudent(createRecord("Alice", 1, 90.0));
    CHECK(getName(cm.getStudent(1)) == "Alice");
}

TEST_CASE("StudentTest CourseManager duplicate student") {
    CourseManager cm;
    cm.addStudent(createRecord("Alice", 1, 90.0));
    CHECK_THROWS_AS(cm.addStudent(createRecord("Alice2", 1, 80.0)), std::invalid_argument);
}

TEST_CASE("StudentTest CourseManager createCourse") {
    CourseManager cm;
    cm.createCourse("CPP");
    CHECK(cm.getTotalCourses() == 1);
}

TEST_CASE("StudentTest CourseManager enroll and check") {
    CourseManager cm;
    cm.addStudent(createRecord("Alice", 1, 90.0));
    cm.createCourse("CPP");
    cm.enrollStudent(1, "CPP");
    CHECK(cm.isEnrolled(1, "CPP") == true);
}

TEST_CASE("StudentTest CourseManager duplicate enrollment") {
    CourseManager cm;
    cm.addStudent(createRecord("Alice", 1, 90.0));
    cm.createCourse("CPP");
    cm.enrollStudent(1, "CPP");
    CHECK_THROWS_AS(cm.enrollStudent(1, "CPP"), std::invalid_argument);
}

TEST_CASE("StudentTest CourseManager removeStudent") {
    CourseManager cm;
    cm.addStudent(createRecord("Alice", 1, 90.0));
    cm.createCourse("CPP");
    cm.enrollStudent(1, "CPP");
    cm.removeStudent(1, "CPP");
    CHECK(cm.isEnrolled(1, "CPP") == false);
}

TEST_CASE("StudentTest CourseManager intersections") {
    CourseManager cm;
    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));
    cm.createCourse("CPP");
    cm.createCourse("Algo");
    cm.enrollStudent(1, "CPP");
    cm.enrollStudent(2, "CPP");
    cm.enrollStudent(1, "Algo");
    auto both = cm.studentsInBothCourses("CPP", "Algo");
    CHECK(both.size() == 1);
    CHECK(both[0] == 1);
}

TEST_CASE("StudentTest CourseManager unions") {
    CourseManager cm;
    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));
    cm.createCourse("CPP");
    cm.createCourse("Algo");
    cm.enrollStudent(1, "CPP");
    cm.enrollStudent(2, "Algo");
    auto either = cm.studentsInEitherCourse("CPP", "Algo");
    CHECK(either.size() == 2);
}

TEST_CASE("StudentTest assignGrade and average") {
    CourseManager cm;
    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));
    cm.createCourse("CPP");
    cm.enrollStudent(1, "CPP");
    cm.enrollStudent(2, "CPP");
    cm.assignGrade(1, "CPP", 100.0);
    cm.assignGrade(2, "CPP", 80.0);
    CHECK(cm.getCourseAverage("CPP") == doctest::Approx(90.0));
}

TEST_CASE("StudentTest getAllCourses and ids") {
    CourseManager cm;
    cm.createCourse("B");
    cm.createCourse("A");
    cm.addStudent(createRecord("Bob", 2, 70.0));
    cm.addStudent(createRecord("Alice", 1, 80.0));
    auto courses = cm.getAllCourses();
    auto ids = cm.getAllStudentIds();
    CHECK(courses[0] == "A");
    CHECK(ids[0] == 1);
}

TEST_CASE("StudentTest toUpper and toLower") {
    CHECK(toUpper("abC") == "ABC");
    CHECK(toLower("AbC") == "abc");
}

TEST_CASE("StudentTest trim and split") {
    CHECK(trim("  hello  ") == "hello");
    auto parts = split("a,b,", ',');
    CHECK(parts.size() == 3);
    CHECK(parts[2] == "");
}

TEST_CASE("StudentTest join and replace") {
    CHECK(join(std::vector<std::string>{"a", "b"}, ",") == "a,b");
    CHECK(replaceAll("aabb", "bb", "xx") == "aaxx");
}

TEST_CASE("StudentTest startsWith endsWith") {
    CHECK(startsWith("hello", "he") == true);
    CHECK(endsWith("hello", "lo") == true);
}

TEST_CASE("StudentTest countChar palindrome reverse") {
    CHECK(countChar("hello", 'l') == 2);
    CHECK(isPalindrome("Race Car") == true);
    CHECK(reverseString("abc") == "cba");
}

TEST_CASE("StudentTest type traits") {
    CHECK(describeType<int>() == "integral");
    CHECK(isNumeric<double>() == true);
    CHECK(areSameType<int, int>() == true);
    CHECK(numericToString(7) == "7");
    CHECK(safeAdd(3, 4) == 7);
    CHECK(getZero<std::string>() == "");
}

TEST_CASE("StudentTest file exists") {
    std::ifstream file("StudentTest.cpp");
    CHECK(file.good());
}
