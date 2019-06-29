#include <iostream>
#include <string>
#include <vector>

#include "btreeitem.h"

template <class T, class K>
bool m(BTreeItem<T, K> &&x, BTreeItem<T, K> y) {
  return x < y;
}

int main() {
  BTreeItem<int, std::string> a(12, "lol"), b(14, "kek");
  m(std::move(a), std::move(b));
  return 0;
}
