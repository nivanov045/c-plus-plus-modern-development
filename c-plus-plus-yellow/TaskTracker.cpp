#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

//enum class TaskStatus {
//  NEW,          // новая
//  IN_PROGRESS,  // в разработке
//  TESTING,      // на тестировании
//  DONE          // завершена
//};
//
//using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const
  {
    if (_tasksDataBase.count(person))
      return _tasksDataBase.at(person);
    return {};
  }

  void AddNewTask(const string& person)
  {
    ++_tasksDataBase[person][TaskStatus::NEW];
  }

  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
  {
    if (!_tasksDataBase.count(person))
      return {};
    TasksInfo personsTaskInfo = _tasksDataBase.at(person);
    TasksInfo performed, unperformed = personsTaskInfo;
    for (auto ts = static_cast<int>(TaskStatus::NEW); ts != static_cast<int>(TaskStatus::DONE); ts++) {
      auto currentStatus = static_cast<TaskStatus>(ts);
      auto nextStatus = static_cast<TaskStatus>(ts + 1);
      if (!personsTaskInfo.count(currentStatus))
        continue;
      if (personsTaskInfo.at(currentStatus) <= task_count) {
        performed[nextStatus] = personsTaskInfo.at(currentStatus);
        unperformed.erase(currentStatus);
        task_count -= personsTaskInfo.at(currentStatus);
      } else {
        performed[nextStatus] = task_count;
        unperformed[currentStatus] -= task_count;
        break;
      }
    }
    for (auto ts = static_cast<int>(TaskStatus::NEW); ts != static_cast<int>(TaskStatus::DONE) + 1; ts++) {
      auto status = static_cast<TaskStatus>(ts);
      _tasksDataBase.at(person).erase(status);
      if (performed.count(status))
        _tasksDataBase.at(person)[status] = performed.at(status);
      if (unperformed.count(status))
        _tasksDataBase.at(person)[status] += unperformed.at(status);
    }
    unperformed.erase(TaskStatus::DONE);
    return tie(performed, unperformed);
  }

private:
  map<string, TasksInfo> _tasksDataBase;
};

//void PrintTasksInfo(TasksInfo tasks_info) {
//  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//    ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//    ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//    ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
//}
//
//int main() {
//  TeamTasks tasks;
//  tasks.AddNewTask("Ilia");
//  for (int i = 0; i < 3; ++i) {
//    tasks.AddNewTask("Ivan");
//  }
//  cout << "Ilia's tasks: ";
//  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//  cout << "Ivan's tasks: ";
//  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
//
//  TasksInfo updated_tasks, untouched_tasks;
//
//  tie(updated_tasks, untouched_tasks) =
//    tasks.PerformPersonTasks("Ivan", 2);
//  cout << "Updated Ivan's tasks: ";
//  PrintTasksInfo(updated_tasks);
//  cout << "Untouched Ivan's tasks: ";
//  PrintTasksInfo(untouched_tasks);
//
//  tie(updated_tasks, untouched_tasks) =
//    tasks.PerformPersonTasks("Ivan", 2);
//  cout << "Updated Ivan's tasks: ";
//  PrintTasksInfo(updated_tasks);
//  cout << "Untouched Ivan's tasks: ";
//  PrintTasksInfo(untouched_tasks);
//
//  return 0;
//}