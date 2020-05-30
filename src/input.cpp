#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "graph.hpp"
#include "input.hpp"


namespace killdozer {
	namespace input {

    int departmentMaxWorkingHours(
      std::string const &department_name,
      std::vector<Researcher> const &researchers
    ) {
      std::string dep_name;
      int total_working_hours = 0;
      int working_hours_max = 0;
      for(Researcher const &r: researchers) {
        dep_name = std::get<1>(r);
        working_hours_max = std::get<3>(r);
        if(dep_name != department_name) {
          continue;
        }
        total_working_hours = total_working_hours + working_hours_max;
      }
      return total_working_hours;
    }

    int taskGroupMaxWorkingHours(
      std::string const &tg_name,
      std::vector<Task> const &tasks
    ) {
      std::string t_tg_name;
      int total_working_hours = 0;
      int working_hours_max = 0;
      for(Task const &t: tasks) {
        t_tg_name = std::get<1>(t);
        working_hours_max = std::get<5>(t);
        if(t_tg_name != tg_name) {
          continue;
        }
        total_working_hours = total_working_hours + working_hours_max;
      }
      return total_working_hours;
    }

    void createSchedulingGraph(
      killdozer::graph::DAG &dag,
      std::string const &start_label,
      std::string const &termination_label,
      std::vector<Department> const &departments,
      std::vector<Researcher> const &researchers,
      std::vector<TaskGroup> const &task_groups,
      std::vector<Task> const &tasks
      ) {
        // Add starting node
        dag.adjacenceMap[start_label] = std::vector<killdozer::graph::Edge>();

        // Add departments node
        for(Department const &dep: departments) {
          std::string dep_name = std::get<0>(dep);
          int max_dep_working_hours = departmentMaxWorkingHours(dep_name, researchers);

          dag.adjacenceMap[dep_name] = std::vector<killdozer::graph::Edge>();
          dag.adjacenceMap[start_label].push_back({
            // From, to, maxFlow, MinFlow, cost, currentFlow
            start_label, dep_name, max_dep_working_hours, 0, 0, 0
          });
        };

        // Add researchers
        for(Researcher const &r: researchers) {
          std::string r_name = std::get<0>(r);
          std::string r_dep_name = std::get<1>(r);
          int r_importance = std::get<2>(r);
          int r_max_working_hours = std::get<3>(r);

          dag.adjacenceMap[r_name] = std::vector<killdozer::graph::Edge>();
          dag.adjacenceMap[r_dep_name].push_back({
            // From, to, maxFlow, MinFlow, cost, currentFlow
            r_dep_name, r_name, r_max_working_hours, 0, r_importance, 0
          });
        };

        // Add termination node
        dag.adjacenceMap[termination_label] = std::vector<killdozer::graph::Edge>();

        // Add task groups
        for(TaskGroup const &tg: task_groups) {
          std::string tg_name = std::get<0>(tg);
          int tg_required_working_hours = std::get<2>(tg);
          int tg_max_possible_working_hours = taskGroupMaxWorkingHours(
            tg_name,
            tasks
          );

          dag.adjacenceMap[tg_name] = std::vector<killdozer::graph::Edge>();
          dag.adjacenceMap[tg_name].push_back({
            // From, to, maxFlow, MinFlow, cost, currentFlow
            tg_name, termination_label, tg_max_possible_working_hours, tg_required_working_hours, 0, 0
          });
        };

        // Add tasks
        for(Task const &t: tasks) {
          std::string t_name = std::get<0>(t);
          std::string t_tg_name = std::get<1>(t);
          int t_min = std::get<4>(t);
          int t_max = std::get<5>(t);

          dag.adjacenceMap[t_name] = std::vector<killdozer::graph::Edge>();
          dag.adjacenceMap[t_name].push_back({
            // From, to, maxFlow, MinFlow, cost, currentFlow
            t_name, t_tg_name, t_max, t_min, 0, 0
          });
        };

      // TODO: Connection between researchesr and taks..

      // 1 - Research to separate researcher day
      // 2 - day into possilbe tasks
      // (special case - time conflict)
    }

    void parseFromStdin(
      killdozer::graph::DAG &dag,
      std::string const &start_label,
      std::string const &termination_label
    ) {
      std::vector<Department> departments;
      std::vector<Researcher> researchers;
      std::vector<TaskGroup> task_groups;
      std::vector<Task> tasks;

      std::string input_line;
         
      // First line: number of departments
      std::getline(std::cin, input_line);
      int number_of_departments = std::stoi(input_line);
      
      for(int i = 0; i < number_of_departments; i++) {
        // Department info
        std::getline(std::cin, input_line);

        std::istringstream d_stream(input_line);
        std::string d_part0, d_part1;
        
        d_stream >> d_part0 >> d_part1;

        std::string department_name = d_part0;
        int department_size = std::stoi(d_part1);

        departments.push_back(
          std::make_tuple(
            department_name,
            department_size
          )
        );

        for(int j = 0; j < department_size; j++) {
          // Researcher info
          std::getline(std::cin, input_line);
          std::istringstream r_stream(input_line);
          
          std::string r_part0, r_part1, r_part2, r_part3;
        
          r_stream >> r_part0 >> r_part1 >> r_part2 >> r_part3;

          int importance = std::stoi(r_part1);
          int max_working_hours_total = std::stoi(r_part2);
          int max_working_hours_per_day = std::stoi(r_part3);

          researchers.push_back(
            std::make_tuple(
              // Guarantee researcher names are unique
              department_name + "|" + r_part0,
              department_name,
              importance,
              max_working_hours_total,
              max_working_hours_per_day
            )
          );
        };
      };

      // Number of task groups
      std::getline(std::cin, input_line);
      int number_of_task_groups = std::stoi(input_line);

      for(int i = 0; i < number_of_task_groups; i++) {
        // Task group info
        std::getline(std::cin, input_line);

        std::istringstream tg_stream(input_line);
        std::string tg_part0, tg_part1, tg_part2;
        
        tg_stream >> tg_part0 >> tg_part1 >> tg_part2;

        std::string task_group_name = tg_part0;
        int task_group_size = std::stoi(tg_part1);
        int working_hours_to_completion = std::stoi(tg_part2);

        task_groups.push_back(
          std::make_tuple(
            task_group_name,
            task_group_size,
            working_hours_to_completion
          )
        );

        for(int j = 0; j < task_group_size; j++) {
          // Task info
          std::getline(std::cin, input_line);
          std::istringstream t_stream(input_line);
          
          std::string t_part0, t_part1, t_part2, t_part3;
        
          t_stream >> t_part0 >> t_part1 >> t_part2 >> t_part3;

          int day = std::stoi(t_part0);
          int time = std::stoi(t_part1);
          int working_hours_min = std::stoi(t_part2);
          int working_hours_max = std::stoi(t_part3);

          tasks.push_back(
            std::make_tuple(
              // groupname|day|time
              task_group_name + "|" + t_part0 + "|" + t_part1,
              task_group_name,
              day, 
              time,
              working_hours_min,
              working_hours_max
            )
          );
        };
      }

      createSchedulingGraph(
        dag,
        start_label,
        termination_label,
        departments,
        researchers,
        task_groups,
        tasks
      );
    }

	}
}
