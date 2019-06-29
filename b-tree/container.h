#ifndef BTREENODECONTAINER_H
#define BTREENODECONTAINER_H

#include <cstddef>
#include <utility>

#include "btreeitem.h"
#include "noncopyable.h"

/*
 * Abstract class for containing BTreeItems in BTreeNode.
 * Virtual functions may have some overhead
 * Check assembler and benchmark ("virtual-vs-nonvirtual")
 */
template <class Key_t, class Val_t>
class Container : private NonCopyable {
 protected:
  using Item_t = BTreeItem<Key_t, Val_t>;

 private:
  /*
   * Methods with Do prefix are used in NVI idiom
   */
  virtual bool DoAddItem(const Key_t&, Val_t&&) = 0;
  virtual const Val_t& DoGetItem(const Key_t&) const = 0;
  virtual Val_t DoPopItem(const Key_t&) = 0;

 public:
  /*
   * Reserves memory if implementation allows
   */
  Container(size_t n);

  Container();

 public:
  /*
   * Adds item into container
   * takes item`s value as Val_t val without links or pointers.
   * C++11 garants that rvalues will be moved in that case,
   * lvalues will be copyed.
   */
  bool AddItem(const Key_t& key, Val_t val) {
    return DoAddItem(key, std::move(val));
  }

  const Val_t& operator[](const Key_t& key) const {
    return DoGetItem(std::move(key));
  }

  /*
   * Calls operator[] const and uses const_cast on it`s result
   */
  Val_t& operator[](const Key_t& key) {
    return const_cast<Val_t&>(static_cast<const Container&>(*this)[key]);
  }
};

#endif  // BTREENODECONTAINER_H
