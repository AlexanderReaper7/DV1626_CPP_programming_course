#include "Time.hpp"

/* fmt is used to format the time in the print functuin */
#define FMT_HEADER_ONLY
#include <fmt/chrono.h>
#include <fmt/format.h>

Time::Time(int minutes, int seconds)
    : time(std::chrono::minutes(minutes) + std::chrono::seconds(seconds)) {}

Time::Time(int seconds) : time(std::chrono::seconds(seconds)) {}

Time::Time(std::chrono::duration<int64_t> time) : time(time) {}

bool Time::operator==(const Time& rhs) const { return time == rhs.time; }

bool Time::operator!=(const Time& rhs) const { return !(*this == rhs); }

std::chrono::duration<int64_t> Time::getChronoTime() const { return time; }

std::string Time::print() const { return fmt::format("{:%M:%S}", time); }