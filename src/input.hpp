#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <tuple>
#include <vector>

#include "graph.hpp"


namespace killdozer {
  namespace input {

    // Node Name, Size
    typedef std::tuple<std::string, int> Department;
    // Node Name, Department, Importance, Total max working hours, max working hours per day
    typedef std::tuple<std::string, std::string, int, int, int> Researcher;
    // Node Name, subtask count, total working hours required
    typedef std::tuple<std::string, int, int> TaskGroup;
    // Node Name, TaskGroup, Day, Time, minimal working hours, max working hours
    typedef std::tuple<std::string, std::string, int, int, int, int> Task;

    int departmentMaxWorkingHours(
      std::string const &department_name,
      std::vector<Researcher> const &researchers
    );

    int taskGroupMaxWorkingHours(
      std::string const &tg_name,
      std::vector<Task> const &tasks
    );

    void parseFromStdin(
      killdozer::graph::DAG &dag,
      std::string const &start_label,
      std::string const &termination_label
    );

    void createSchedulingGraph(
      killdozer::graph::DAG &dag,
      std::string const &start_label,
      std::string const &termination_label,
      std::vector<Department> const &departments,
      std::vector<Researcher> const &researchers,
      std::vector<TaskGroup> const &task_groups,
      std::vector<Task> const &tasks
    );
  }
}

#endif
