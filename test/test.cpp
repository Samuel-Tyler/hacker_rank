#include "print_coloured.hpp"

#include <algorithm>
#include <experimental/filesystem>
#include <experimental/string_view>
#include <fstream>
#include <future>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include <csignal>
#include <cstring>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define fs std::experimental::filesystem
using namespace std::chrono_literals;
using namespace std::string_literals;

const char* executable_name = "hacker_rank";
const char* input_file_name = "input";

enum class Test_result
{
  untested,
  testing,
  success,
  output_mistmatch,
  crash,
  timeout,
  no_reference_data
};

bool compare_output_files(const std::string& p1, const std::string& p2)
{
  std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

  if (f1.fail() || f2.fail())
  {
    return false; // file problem
  }

  std::vector<char> no_ws_f1;
  std::vector<char> no_ws_f2;

  no_ws_f1.reserve(f1.tellg());
  no_ws_f2.reserve(f2.tellg());

  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);

  while (f1.good())
  {
    char a = f1.get();
    if (!(a == ' ' || a == '\r' || a == '\n'))
    {
      no_ws_f1.push_back(a);
    }
  }

  while (f2.good())
  {
    char a = f2.get();
    if (!(a == ' ' || a == '\r' || a == '\n'))
    {
      no_ws_f2.push_back(a);
    }
  }

  return true;
}

std::string to_string(const Test_result& test_result) noexcept
{
  switch (test_result)
  {
  case Test_result::untested:
    return "untested"s;
  case Test_result::success:
    return "success"s;
  case Test_result::output_mistmatch:
    return "output_mistmatch"s;
  case Test_result::crash:
    return "crash"s;
  case Test_result::timeout:
    return "timeout"s;
  case Test_result::testing:
    return "testing"s;
  case Test_result::no_reference_data:
    return "no reference data"s;
  default:
    return ""s;
  }
}

Console_colour colour(const Test_result& test_result) noexcept
{
  switch (test_result)
  {
  case Test_result::untested:
    return Console_colour::FG_DEFAULT;
  case Test_result::success:
    return Console_colour::FG_LIGHT_GREEN;
  case Test_result::output_mistmatch:
    return Console_colour::FG_LIGHT_RED;
  case Test_result::crash:
    return Console_colour::FG_LIGHT_RED;
  case Test_result::timeout:
    return Console_colour::FG_LIGHT_RED;
  case Test_result::testing:
    return Console_colour::FG_RED;
  case Test_result::no_reference_data:
    return Console_colour::FG_LIGHT_YELLOW;
  default:
    return Console_colour::FG_DEFAULT;
  }
}

struct Test_case
{
  Test_case() : test_result(Test_result::untested), execution_time(0) {}
  std::string               name;
  fs::path                  path;
  Test_result               test_result;
  std::chrono::milliseconds execution_time;
};

struct Problem
{
  Problem(const fs::path& _path)
      : path(_path), name(fs::absolute(_path).stem().string())
  {
  }
  fs::path               path;
  std::string            name;
  std::vector<Test_case> test_cases;
};

std::vector<Problem> find_problems(const std::string& search_path)
{
  std::vector<Problem> paths;

  auto add_path = [&paths](const fs::path& path) {
    if (fs::exists(path / std::string(executable_name)))
    {
      auto& problem = paths.emplace_back(path);

      for (const auto dir : fs::recursive_directory_iterator(path))
      {
        if (dir.path().stem().string().find("input") != std::string::npos)
        {

          Test_case test_case;
          test_case.name = absolute(dir.path()).stem().string();
          test_case.path = dir.path();
          problem.test_cases.push_back(test_case);
        }
      }
    }
  };

  add_path(search_path);

  auto root_dir = fs::directory_iterator(search_path);
  for (const auto& problem_dir : root_dir)
  {
    add_path(problem_dir.path());
  }

  std::sort(paths.begin(), paths.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.path < rhs.path;
  });
  return paths;
}

enum class Field
{
  problem,
  test_data,
  test_result,
  test_duration
};

int GetFieldSize(Field field)
{
  switch (field)
  {
  case Field::problem:
    return 25;
  case Field::test_data:
    return 15;
  case Field::test_result:
    return 20;
  case Field::test_duration:
    return 8;
  default:
    return 0;
  }
}

std::string GetFieldTitle(Field field)
{
  switch (field)
  {
  case Field::problem:
    return "Problem"s;
  case Field::test_data:
    return "Test Case"s;
  case Field::test_result:
    return "Result"s;
  case Field::test_duration:
    return "Time (s)"s;
  default:
    return ""s;
  }
}

void print(Field field, const std::string& field_text,
           Console_colour console_colour = Console_colour::FG_LIGHT_CYAN)
{
  std::string to_print =
      static_cast<int>(field_text.length()) <= GetFieldSize(field)
          ? field_text
          : field_text.substr(0, GetFieldSize(field));
  to_print += std::string(
      GetFieldSize(field) - static_cast<int>(to_print.length()), ' ');
  print_coloured(to_print, console_colour);
  std::cout << " | ";
}

void print(const std::vector<Problem>& problems)
{
  system("clear");
  std::vector<Field> fields = {Field::problem, Field::test_data,
                               Field::test_result, Field::test_duration};

  std::cout << " | ";
  for (const auto& field : fields)
  {
    print(field, GetFieldTitle(field), Console_colour::FG_LIGHT_CYAN);
  }

  std::cout << '\n';
  for (const auto& problem : problems)
  {
    for (const auto& test_case : problem.test_cases)
    {
      std::cout << " | ";
      print(Field::problem, problem.name);
      print(Field::test_data, test_case.name);
      print(Field::test_result, to_string(test_case.test_result),
            colour(test_case.test_result));
      print(Field::test_duration,
            std::to_string(test_case.execution_time.count() / 1000.0));
      std::cout << '\n';
    }
  }
}

int main(int argc, char** argv)
{
  bool all_tests_passed = true;

  std::string search_path = "..";
  if (argc > 1)
  {
    search_path = std::string(argv[1]);
  }
  std::ios::sync_with_stdio(true);

  auto problems = find_problems(search_path);
  for (auto& problem : problems)
  {
    for (auto& test_case : problem.test_cases)
    {
      test_case.test_result = Test_result::testing;
      print(problems);

      auto reference_output_filename = test_case.path.string();
      reference_output_filename.replace(
          reference_output_filename.find(input_file_name),
          std::strlen(input_file_name), "output");
      const auto  test_output_filename = reference_output_filename + ".tst";
      std::string command =
          (problem.path / std::string(executable_name)).string(); //+ " < " +
      //   test_case.path.string() + " > " +
      //  test_output_filename + " 2> /dev/null";

      const auto start = std::chrono::high_resolution_clock::now();

      int  pid = 0;
      auto process_result =
          std::async(std::launch::async, [&pid, &argv, &command, &test_case,
                                          &test_output_filename] {

            std::array<int, 2> pipe_stdin = {};
            std::array<int, 2> pipe_stdout = {};
            if (pipe(pipe_stdin.data()) < 0)
            {
              return -1;
            }
            if (pipe(pipe_stdout.data()) < 0)
            {
              return -1;
            }

            pid = fork();
            if (pid == 0)
            {
              close(pipe_stdin[1]);
              close(pipe_stdout[0]);

              dup2(pipe_stdin[0], fileno(stdin));
              dup2(pipe_stdout[1], fileno(stdout));
              auto ret = execl(command.c_str(), argv[0], NULL);
              exit(ret);
            }

            close(pipe_stdin[0]);
            close(pipe_stdout[1]);
            std::ifstream input_file(test_case.path);
            std::ofstream output_file(test_output_filename);

            while (true)
            {
              if (!input_file.good())
              {
                break;
              }
              std::string line;
              std::getline(input_file, line);
              const auto bytes_written =
                  write(pipe_stdin[1], line.data(), line.length());
              if (bytes_written != static_cast<int>(line.length()))
              {
                break;
              }
              const auto bytes_written2 = write(pipe_stdin[1], "\n", 1);
              if (bytes_written2 != 1)
              {
                break;
              }
            }
            while (true)
            {
              std::vector<char> buffer(512);

              auto bytes_read =
                  read(pipe_stdout[0], buffer.data(), buffer.size());
              if (bytes_read <= 0)
              {
                break;
              }

              output_file.write(buffer.data(), bytes_read);
            }

            std::cout << "writing done" << std::endl;
            int internal_stat;
            waitpid(pid, &internal_stat, 0);
            return internal_stat;
          });

      bool timed_out = false;
      while (process_result.wait_for(10ms) != std::future_status::ready)
      {
        const auto current = std::chrono::high_resolution_clock::now();

        test_case.execution_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(current -
                                                                  start);
        if (test_case.execution_time > 2s)
        {
          timed_out = true;
          kill(pid, SIGKILL);
          break;
        }
        //       print(problems);
      }

      const auto end = std::chrono::high_resolution_clock::now();
      const auto test_duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      test_case.execution_time = test_duration;

      auto res = process_result.get();
      if (timed_out)
      {
        test_case.test_result = Test_result::timeout;
      }
      else if (!WIFEXITED(res)) // != 0) // || (WEXITSTATUS(res) != 0))
      {
        test_case.test_result = Test_result::crash;
      }
      else if (!fs::exists(reference_output_filename))
      {
        test_case.test_result = Test_result::no_reference_data;
      }
      else if (!compare_output_files(reference_output_filename,
                                     test_output_filename))
      {
        test_case.test_result = Test_result::output_mistmatch;
      }
      else
      {
        test_case.test_result = Test_result::success;
      }

      if (test_case.test_result != Test_result::success)
      {
        all_tests_passed = false;
      }

      print(problems);
    }
    print(problems);
  }
  return all_tests_passed ? 0 : -1;
}
