#include "tests_checking.h"

#include <deque>
std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> students_works;
    std::vector<std::string> answer;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            students_works.emplace_front(student_actions[i].name);
        } else {
            students_works.emplace_back(student_actions[i].name);
        }
    }
    for (size_t i = 0; i < queries.size(); ++i) {
        answer.emplace_back(students_works[queries[i] - 1]);
    }
    return answer;
}
