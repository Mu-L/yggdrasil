
#!/bin/bash

find . -type f -name '*darwin16*' -print0 | while IFS= read -r -d '' f; do
  dir=$(dirname "$f")
  base=$(basename "$f")
  newbase=${base//darwin16/darwin}
  if [ "$base" != "$newbase" ]; then
    target="$dir/$newbase"
    if [ ! -e "$target" ]; then
      mv -v -- "$f" "$target"
    else
      ext=""
      name="$newbase"
      # 如果有扩展名，拆分
      if [[ "$newbase" == *.* ]]; then
        ext=".${newbase##*.}"
        name="${newbase%.*}"
      fi
      i=1
      while [ -e "$dir/${name}(${i})${ext}" ]; do
        i=$((i+1))
      done
      mv -v -- "$f" "$dir/${name}(${i})${ext}"
    fi
  fi
done