#ifndef TBTREENODE_H
#define TBTREENODE_H

#include <stdexcept>
#include <vector>

#include "btreeitem.h"
#include "noncopyable.h"

/*
 * Node of BTree, NonCopyable
 */
template <class Key_t, class Val_t>
class BTreeNode : private NonCopyable {
 private:
  const size_t min_degree;
  const size_t max_degree;

 protected:
  using Item_t = BTreeItem<Key_t, Val_t>;

 public:
  /*
   * Takes BTree degree as argument.
   * Throws std::out_of_range exception on bad degree.
   */
  explicit BTreeNode(size_t degree)
      : min_degree(degree - 1), max_degree(2 * degree - 1) {
    if (degree < 2) {
      throw std::out_of_range("Degree of BTree can`t be less then 2");
    }
  }

 public:
  BTreeNode* Split();
  size_t Size();
};

#endif  // TBTREENODE_H
