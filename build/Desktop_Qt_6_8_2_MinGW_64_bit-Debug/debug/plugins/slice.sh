#!/usr/bin/env bash
# script.sh
# $1 — полный путь к исходному .c‑файлу (Windows-путь: /mnt/c/…)
# $2 — критерий среза, например main:21:sum
set -e

# 1. Перевод .c → .bc
clang -g -O0 -emit-llvm -c "$1" -o /tmp/input.bc

# 2. Вызов slicer
/mnt/c/Diplom_project/Static_analyser/symbiotic/sbt-slicer/build-10.0.0/src/sbt-slicer \
    -c "$2" /tmp/input.bc -o /tmp/slice.bc

# 3. Конвертация llvm‑bc → .c
/mnt/c/Diplom_project/Static_analyser/symbiotic/llvm2c/build-10.0.0/llvm2c \
    /tmp/slice.bc -o /tmp/slice.c

# 4. Вывод готового .c в stdout
cat /tmp/slice.c
