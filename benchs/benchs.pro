TEMPLATE = subdirs

LIBS += lbenchmark

SUBDIRS += \
    bench_btreenode \
    virtual-vs-nonvirtual \
    item_insert_or_emplace
