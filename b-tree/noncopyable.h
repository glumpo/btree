#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

/*
 * inherit to prevent copy
 */
class NonCopyable {
 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif  // NONCOPYABLE_H
