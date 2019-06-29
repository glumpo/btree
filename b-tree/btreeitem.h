#ifndef BTREEITEM_H
#define BTREEITEM_H

#include <utility>

#include "noncopyable.h"

/*
 * Contains pair of objects. NonCopyable, Movable.
 */
template <class Key_t, class Val_t>
class BTreeItem : private NonCopyable {
 public:
  /*
   * Since C++11 rvalue link will be moved, so
   * BTreeItem(st::move(k), std::move(v)) will take 2 moves
   */
  BTreeItem(Key_t _k, Val_t _v) : key(std::move(_k)), val(std::move(_v)) {}
  virtual ~BTreeItem() {}

  BTreeItem(BTreeItem &&other) noexcept
      : key(std::move(other.key)), val(std::move(other.val)) {}
  BTreeItem &operator=(BTreeItem &&other) noexcept {
    if (this != &other) {
      key = std::move(other.key);
      val = std::move(other.val);
    }
    return other;
  }

  bool operator<(const BTreeItem &r) const noexcept {
    return this->key < r.key;
  }
  bool operator==(const BTreeItem &r) const noexcept {
    return this->key == r.key;
  }
  bool operator!=(const BTreeItem &r) const noexcept {
    return this->key != r.key;
  }

 public:
  using KeyType = Key_t;
  using ValueType = Val_t;

 private:
  Key_t key;
  Val_t val;
};

#endif  // BTREEITEM_H
