TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += app slice

# алиас "slice" указывает на каталог plugins/Slice
slice.subdir  = plugins/Slice
slice.depends = app   # <- гарантирует сборку app перед плагином
