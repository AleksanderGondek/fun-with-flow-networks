#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <tuple>
#include <vector>

#include "graph.hpp"


namespace killdozer {
  namespace input {

    // Name, Size
    typedef std::tuple<std::string, int> Department;
    // Name, Department, Importance, Total max working hours, max working hours per day
    typedef std::tuple<std::string, std::string, int, int, int> Researcher;
    // Name, subtask count, total working hours count
    typedef std::tuple<std::string, int, int> TaskGroup;
    // Name, TaskGroup, Day, Time, minimal working hours, max working hours
    typedef std::tuple<std::string, std::string, int, int, int, int> Task;

    void parseFromStdin(killdozer::graph::DAG &dag);
    void createSchedulingGraph(
      killdozer::graph::DAG &dag,
      std::vector<Department> const &departments,
      std::vector<Researcher> const &researchers,
      std::vector<TaskGroup> const &task_groups,
      std::vector<Task> const &tasks
    );
  }
}

#endif
