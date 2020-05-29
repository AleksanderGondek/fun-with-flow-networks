#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "graph.hpp"
#include "input.hpp"


namespace killdozer {
	namespace input {

    void parseFromStdin(killdozer::graph::DAG &dag) {
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
              r_part0,
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
          
          std::string t_part0, t_part1, t_part2, t_part3, t_part4;
        
          t_stream >> t_part0 >> t_part1 >> t_part2 >> t_part3 >> t_part4;

          int day = std::stoi(t_part1);
          int time = std::stoi(t_part2);
          int working_hours_min = std::stoi(t_part3);
          int working_hours_max = std::stoi(t_part4);

          tasks.push_back(
            std::make_tuple(
              t_part0,
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
        departments,
        researchers,
        task_groups,
        tasks
      );
    }

    void createSchedulingGraph(
      killdozer::graph::DAG &dag,
      std::vector<Department> const &departments,
      std::vector<Researcher> const &researchers,
      std::vector<TaskGroup> const &task_groups,
      std::vector<Task> const &tasks
      ) {
    }

	}
}
