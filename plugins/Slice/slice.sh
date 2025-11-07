#!/usr/bin/env bash
# $1 — путь к исходному .c (WSL стиль /mnt/c/...), $2 — критерий (например "main:21:sum" или "21:sum")
set -euo pipefail
SRC="$1"
CRIT="$2"

# 1) .c → .bc (с дебаг-метой)
clang -g -O0 -emit-llvm -c "$SRC" -o /tmp/input.bc

# 2) Срез
/mnt/c/Diplom_project/Static_analyser/symbiotic/sbt-slicer/build-10.0.0/src/sbt-slicer \
  -c "$CRIT" /tmp/input.bc -o /tmp/slice.bc

# --- 2b) DOT_CFG из slice.bc (по первой/основной функции) ---
pushd /tmp >/dev/null
# Если в системе несколько версий LLVM, замени 'opt' на конкретную, например opt-10
opt -dot-cfg -disable-output /tmp/slice.bc || true
CFG_DOT="$(ls -1 cfg.*.dot 2>/dev/null | head -n1)"
echo "/*__BEGIN_DOT_CFG__*/"
[ -f "$CFG_DOT" ] && cat "$CFG_DOT"
echo "/*__END_DOT_CFG__*/"
# Опционально подчистим промежуточные .dot, чтобы не плодились файлы
rm -f cfg.*.dot 2>/dev/null || true
popd >/dev/null

# 3) Список строк исходника, реально оставшихся в срезе (по !DILocation)
# делаем IR представление
mapfile -t LINES < <( llvm-dis -o - /tmp/slice.bc \
  | grep -oP '!DILocation\(\s*line:\s*\K\d+' \
  | sort -n | uniq )

# 4) Построим видимую «выборку исходника» (без лишних пустых строк)
VISIBLE_TMP=/tmp/slice_visible.c
: > "$VISIBLE_TMP"
SRC_BASENAME="$(basename -- "$SRC")"
#начало Json
LINE_MAP_JSON='{"lineMap":{'
idx=1
for ln in "${LINES[@]}"; do
  # sed уже печатает с \n — НЕ добавляем второй \n
  sed -n "${ln}p" "$SRC" >> "$VISIBLE_TMP"
  LINE_MAP_JSON+=$(printf '"%d":{"file":"%s","line":%d},' "$idx" "$SRC_BASENAME" "$ln")
  idx=$((idx+1))
done
LINE_MAP_JSON="${LINE_MAP_JSON%,}" #удаляем запятую из мапы
LINE_MAP_JSON+='}}'

# --- 4b) DOT_VISIBLE по «видимым строкам» (из VISIBLE_TMP + lineMap) ---
DOT_TMP=/tmp/slice_visible.dot
{
  echo 'digraph G {'
  echo '  rankdir=LR; node [shape=box, fontsize=11];'
  idx=1
  for ln in "${LINES[@]}"; do
    safe_label=$(sed -n "${ln}p" "$SRC" | sed 's/\\/\\\\/g; s/"/\\"/g')
    printf '  n%d [label="%d: %s", id="line_%d", href="line:%d"];\n' "$idx" "$idx" "$safe_label" "$ln" "$ln"
    if (( idx > 1 )); then printf '  n%d -> n%d;\n' "$((idx-1))" "$idx"; fi
    idx=$((idx+1))
  done
  echo '}'
} > "$DOT_TMP"

echo "/*__BEGIN_DOT_VISIBLE__*/"
cat "$DOT_TMP"
echo "/*__END_DOT_VISIBLE__*/"

# 5) Полная декомпиляция llvm2c из slice.bc
LLVMC_TMP=/tmp/slice_llvm2c.c
/mnt/c/Diplom_project/Static_analyser/symbiotic/llvm2c/build-10.0.0/llvm2c \
  /tmp/slice.bc -o "$LLVMC_TMP"

# 6) Отдаём «бандл»: две секции + мета-блок
printf "/*__BEGIN_ORIGINAL_CUSTOM__*/"
cat "$VISIBLE_TMP"
echo "/*__END_ORIGINAL_CUSTOM__*/"
printf "/*__BEGIN_LLVM2C__*/"
cat "$LLVMC_TMP"
echo "/*__END_LLVM2C__*/"
printf "/*__IDE_METADATA__\n%s\n__IDE_METADATA_END__*/\n" "$LINE_MAP_JSON"
