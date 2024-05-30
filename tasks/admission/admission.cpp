#include "admission.h"

int CompDate(Date first, Date second) {
    if (first.year > second.year) {
        return 1;
    } else if (first.year < second.year) {
        return -1;
    } else if (first.month > second.month) {
        return 1;
    } else if (first.month < second.month) {
        return -1;
    } else if (first.day > second.day) {
        return 1;
    } else if (first.day < second.day) {
        return -1;
    }
    return 0;
}
int CompName(Student first, Student second) {

    if (first.name.compare(second.name) > 0) {
        return 1;
    } else if (first.name.compare(second.name) < 0) {
        return -1;
    }
    return 0;
}
int CompPoints(Applicant first, Applicant second) {
    if (first.points > second.points) {
        return -1;
    } else if (first.points < second.points) {
        return 1;
    }
    return 0;
}
bool CompareStudents(const Applicant* first, const Applicant* second) {
    if (CompPoints(*first, *second) < 0) {
        return true;
    } else if (CompPoints(*first, *second) > 0) {
        return false;
    } else if (CompDate(first->student.birth_date, second->student.birth_date) < 0) {
        return true;
    } else if (CompName(first->student, second->student) < 0) {
        return true;
    }
    return false;
}
bool FinalCompare(const Student* first, const Student* second) {
    if (CompName(*first, *second) < 0) {
        return true;
    } else if (CompName(*first, *second) > 0) {
        return false;
    } else if (CompDate(first->birth_date, second->birth_date) < 0) {
        return true;
    }
    return false;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> sorted_applicants;
    std::unordered_map<std::string, uint64_t> size_university;
    AdmissionTable answer;
    for (const auto& applicant : applicants) {
        sorted_applicants.push_back(&applicant);
    }
    for (const auto& university : universities) {
        size_university[university.name] = university.max_students;
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), CompareStudents);
    for (const auto& applicant : sorted_applicants) {
        for (const auto& university : applicant->wish_list) {
            if (size_university[university] > 0) {
                answer[university].push_back(&(applicant->student));
                --size_university[university];
                break;
            }
        }
    }
    for (auto& entry : answer) {
        std::sort(entry.second.begin(), entry.second.end(), FinalCompare);
    }
    return answer;
}
