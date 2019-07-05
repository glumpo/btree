#ifndef BTREENODECONTAINER_H
#define BTREENODECONTAINER_H

#include <cstddef>
#include <type_traits>
#include <utility>

#include "btreeitem.h"
#include "noncopyable.h"

/*
 * If Key is integral of floating type, type = clean_type
 * Else if Key is struct/class object, type = lvalue_type
 * Else type = void
 */
template <class KeyArg_t>
struct DefaultKeyArg {
  // const KeyArg_t&
  using lvalue_type = typename std::add_const<
      typename std::add_lvalue_reference<KeyArg_t>::type>::type;

  // KeyArg_t
  using clean_type = typename std::decay<KeyArg_t>::type;

  using type = typename std::conditional<
      std::is_integral<KeyArg_t>::value ||
          std::is_floating_point<KeyArg_t>::value,
      clean_type,
      typename std::enable_if<std::is_class<KeyArg_t>::value,
                              lvalue_type>::type>::type;
};

/*
 * Abstract class for containing BTreeItems in BTreeNode.
 *
 * KeyArg_t is type to take Key in function.
 * Default is DefaultKeyArg<Key_t>::type (lvalue_reference or clean type in most
 * cases, check comment about it).
 *
 * Virtual functions may have some overhead
 * Check assembler and benchmark ("virtual-vs-nonvirtual")
 */
template <class Key_t, class Val_t,
          class KeyArg_t = typename DefaultKeyArg<Key_t>::type>
class Container : private NonCopyable {
 public:
  using Item_t = BTreeItem<Key_t, Val_t>;
  using

      private :
      /*
       * Methods with Do prefix are used in NVI idiom
       */
      virtual bool
      DoAddItem(KeyArg_t, Val_t&&) = 0;
  virtual const Val_t& DoGetItem(KeyArg_t) const = 0;
  virtual Val_t DoPopItem(KeyArg_t) = 0;

 public:
  Container();

  /*
   * Reserves memory if implementation allows
   */
  Container(size_t n);

 public:
  virtual ~Container() = default;

 public:
  /*
   * Add item into container
   * takes item`s value as Val_t val without links or pointers.
   * C++11 garants that rvalues will be moved in that case,
   * lvalues will be copyed.
   */
  bool AddItem(KeyArg_t key, Val_t val) {
    return DoAddItem(key, std::move(val));
  }

  const Val_t& operator[](KeyArg_t key) const {
    return DoGetItem(std::move(key));
  }

  /*
   * Calls operator[] const and uses const_cast on it`s result
   */
  Val_t& operator[](KeyArg_t key) {
    return const_cast<Val_t&>(static_cast<const Container&>(*this)[key]);
  }

  Val_t PopItem(KeyArg_t key) { return DoPopItem(key); }
};

#endif  // BTREENODECONTAINER_H
