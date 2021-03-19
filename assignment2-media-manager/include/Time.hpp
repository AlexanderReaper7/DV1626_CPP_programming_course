#ifndef TIME_HPP
#define TIME_HPP
#include <chrono>
#include <string>
/**
 * This is a thin wrapper class around the C++ std::chrono class. Chrono has a
 * quite complex interface. This should make working with time units simpler.
 */
class Time {
 public:
  /** Constructor that accepts time as minutes and seconds*/
  Time(int minutes, int seconds);
  /**
   * Constructor that accepts seconds only. 122 seconds will result in two
   * minutes and two seconds
   */
  Time(int seconds);
  /** Constructor that accepts time as a chrono object. Probably not needed*/
  Time(std::chrono::duration<int64_t> time);
  /** Operator overload for equals comparison, i.e. `time1 == time2` */
  bool operator==(const Time& rhs) const;
  /** Operator overload for not equals comparison, i.e. `time1 != time2` */
  bool operator!=(const Time& rhs) const;
  /** Returns time as a chrono object. Probably not needed*/
  std::chrono::duration<int64_t> getChronoTime() const;
  /** Prints the stored time as minutes:seconds. E.g. 12:34 */
  std::string print() const;

 private:
  /** The chrono object that actually stores the time */
  std::chrono::duration<int64_t> time;
};
#endif  // TIME_HPP