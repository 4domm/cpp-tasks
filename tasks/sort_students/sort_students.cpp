#include "sort_students.h"

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
    if (first.last_name.compare(second.last_name) > 0) {
        return 1;
    } else if (first.last_name.compare(second.last_name) < 0) {
        return -1;
    } else if (first.name.compare(second.name) > 0) {
        return 1;
    } else if (first.name.compare(second.name) < 0) {
        return -1;
    }
    return 0;
}
bool CompFirst(Student first, Student second) {

    if (CompDate(first.birth_date, second.birth_date) < 0) {
        return true;
    } else if (CompDate(first.birth_date, second.birth_date) > 0) {
        return false;
    } else if (CompName(first, second) < 0) {
        return true;
    } else if (CompName(first, second) > 0) {
        return false;
    }
    return true;
}
bool CompSecond(Student first, Student second) {

    if (CompName(first, second) < 0) {
        return true;
    } else if (CompName(first, second) > 0) {
        return false;
    } else if (CompDate(first.birth_date, second.birth_date) > 0) {
        return true;
    } else if (CompDate(first.birth_date, second.birth_date) < 0) {
        return false;
    }
    return true;
}
void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (static_cast<int>(sort_kind) == 1) {
        std::sort(students.begin(), students.end(), CompFirst);
    } else {
        std::sort(students.begin(), students.end(), CompSecond);
    }
}
