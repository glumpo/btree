#ifndef CONTAINERVECTOR_H
#define CONTAINERVECTOR_H

#include <algorithm>
#include <vector>

#include "btreeitem.h"
#include "container.h"

template <class Key_t, class Val_t,
          class KeyArg_t = typename DefaultKeyArg<Key_t>::type>
class ContainerVector : public Container<Key_t, Val_t, KeyArg_t> {
 private:
 private:
  virtual bool DoAddItem(KeyArg_t, Val_t&&) override {}
  virtual const Val_t& DoGetItem(KeyArg_t) const override {}
  virtual Val_t DoPopItem(KeyArg_t) override {}

 public:
  ContainerVector();
};

#endif  // CONTAINERVECTOR_H
