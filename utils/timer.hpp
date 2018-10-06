#pragma once

#include <iostream>
#include <chrono>
#include <string>

class Cumulative_timer
{
public:
  Cumulative_timer(const std::string &name) : m_ns(0), m_name(name) {}
  ~Cumulative_timer()
  {
    std::cerr << m_name << " - Total active time " << m_ns.count() << "ns"
              << std::endl;
  }
  void begin() { m_start = std::chrono::high_resolution_clock::now(); }
  void end()
  {
    const auto end = std::chrono::high_resolution_clock::now();
    m_ns += end - m_start;
  }

private:
  std::chrono::high_resolution_clock::time_point m_start;
  std::chrono::nanoseconds m_ns;
  std::string m_name;
};
