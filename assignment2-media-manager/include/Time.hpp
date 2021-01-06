#ifndef TIME_HPP
#define TIME_HPP

#define FMT_HEADER_ONLY
#include <fmt/chrono.h>
#include <fmt/format.h>

#include <chrono>

class Time {
 public:
  Time(int minutes, int seconds)
      : time(std::chrono::minutes(minutes) + std::chrono::seconds(seconds)) {}
  Time(int seconds) : time(std::chrono::seconds(seconds)) {}
  Time(std::chrono::duration<int64_t> time) : time(time) {}
  bool operator==(const Time& rhs) const = default;
  std::chrono::duration<int64_t> getChronoTime() const { return time; }
  std::string print() { return fmt::format("{:%M:%S}", time); }

 private:
  std::chrono::duration<int64_t> time;
};
#endif  // TIME_HPP