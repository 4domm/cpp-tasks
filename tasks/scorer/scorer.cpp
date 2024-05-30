#include "scorer.h"

#include "unordered_map"
struct Task {
    bool success;
    bool no_merge = true;
};
bool CompareEvent(const Event *event1, const Event *event2) {
    return event1->time < event2->time;
};
ScoreTable GetScoredStudents(const Events &events, time_t score_time) {
    std::vector<const Event *> happened_events;
    happened_events.reserve(events.size());
    for (auto &event : events) {
        if (event.time <= score_time) {
            happened_events.push_back(&event);
        }
    }
    std::sort(happened_events.begin(), happened_events.end(), CompareEvent);

    std::unordered_map<std::string_view, std::unordered_map<std::string_view, Task>> student_tasks;
    for (auto event : happened_events) {
        Task &task = student_tasks[event->student_name][event->task_name];
        switch (event->event_type) {
            case EventType::CheckFailed:
                task.success = false;
                break;
            case EventType::CheckSuccess:
                task.success = true;
                break;
            case EventType::MergeRequestOpen:
                task.no_merge = false;
                break;
            case EventType::MergeRequestClosed:
                task.no_merge = true;
                break;
        }
    }

    ScoreTable score_table;
    for (auto &[student, tasks] : student_tasks) {
        std::set<TaskName> resolved;
        for (auto &[task, state] : tasks) {
            if (state.success && state.no_merge) {
                resolved.insert(std::string{task.begin(), task.end()});
            }
        }
        if (!resolved.empty()) {
            score_table[{student.begin(), student.end()}] = std::move(resolved);
        }
    }
    return score_table;
}