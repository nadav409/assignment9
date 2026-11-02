#include "StudentRecord.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace registration {

// Checks that the name, id and grade are valid and builds the tuple record.
StudentRecord createRecord(const std::string& name, int id, double grade) {
    if (name.empty()) {
        throw std::invalid_argument("name must not be empty");
    }
    if (id <= 0) {
        throw std::invalid_argument("id must be positive");
    }
    if (grade < 0.0 || grade > 100.0) {
        throw std::invalid_argument("grade must be between 0 and 100");
    }
    return StudentRecord{name, id, grade};
}

const std::string& getName(const StudentRecord& record) {
    return std::get<0>(record);
}

int getId(const StudentRecord& record) {
    return std::get<1>(record);
}

double getGrade(const StudentRecord& record) {
    return std::get<2>(record);
}

// Copies the three fields of the tuple into the given output variables.
void unpackRecord(const StudentRecord& record, std::string& name, int& id, double& grade) {
    name = getName(record);
    id = getId(record);
    grade = getGrade(record);
}

// Builds a text like "Name (ID: 1, Grade: 90.0)" with an ostringstream, grade with one decimal.
std::string formatRecord(const StudentRecord& record) {
    std::ostringstream output;
    output << getName(record) << " (ID: " << getId(record) << ", Grade: "
           << std::fixed << std::setprecision(1) << getGrade(record) << ")";
    return output.str();
}

// Returns the average grade of all the records, throws if the list is empty.
double averageGrade(const std::vector<StudentRecord>& records) {
    if (records.empty()) {
        throw std::invalid_argument("records must not be empty");
    }

    double sum = 0.0;
    for (const auto& record : records) {
        sum += getGrade(record);
    }
    return sum / static_cast<double>(records.size());
}

// Finds the student with the highest grade using max_element.
// If grades are equal, the name and then the id decide.
StudentRecord bestStudent(const std::vector<StudentRecord>& records) {
    if (records.empty()) {
        throw std::invalid_argument("records must not be empty");
    }

    return *std::max_element(records.begin(), records.end(), [](const StudentRecord& left, const StudentRecord& right) {
        if (getGrade(left) != getGrade(right)) {
            return getGrade(left) < getGrade(right);
        }
        if (getName(left) != getName(right)) {
            return getName(left) > getName(right);
        }
        return getId(left) > getId(right);
    });
}

// Returns a sorted copy from the highest grade to the lowest, ties sorted by name and id.
std::vector<StudentRecord> sortByGrade(const std::vector<StudentRecord>& records) {
    std::vector<StudentRecord> sorted = records;
    std::sort(sorted.begin(), sorted.end(), [](const StudentRecord& left, const StudentRecord& right) {
        if (getGrade(left) != getGrade(right)) {
            return getGrade(left) > getGrade(right);
        }
        if (getName(left) != getName(right)) {
            return getName(left) < getName(right);
        }
        return getId(left) < getId(right);
    });
    return sorted;
}

// Returns a copy sorted by name, then by id and grade.
std::vector<StudentRecord> sortByName(const std::vector<StudentRecord>& records) {
    std::vector<StudentRecord> sorted = records;
    std::sort(sorted.begin(), sorted.end(), [](const StudentRecord& left, const StudentRecord& right) {
        if (getName(left) != getName(right)) {
            return getName(left) < getName(right);
        }
        if (getId(left) != getId(right)) {
            return getId(left) < getId(right);
        }
        return getGrade(left) < getGrade(right);
    });
    return sorted;
}

// Keeps only the records with a grade above minGrade.
std::vector<StudentRecord> filterByGrade(const std::vector<StudentRecord>& records, double minGrade) {
    std::vector<StudentRecord> filtered;
    for (const auto& record : records) {
        if (getGrade(record) > minGrade) {
            filtered.push_back(record);
        }
    }
    return filtered;
}

} // namespace registration
