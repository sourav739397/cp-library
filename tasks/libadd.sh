#!/usr/bin/env bash
# Usage: ./libadd.sh main.cpp
# Expands headers recursively, searches for files in all subfolders
# Keeps #ifdef LOCAL ... #endif, removes /* ... */ comments in headers
# Overwrites the original file safely

set -e

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <file.cpp>" >&2
  exit 1
fi

orig_file="$1"
tmp_file="$(mktemp)"  # temporary file

declare -A included   # already included files
# root_dir="$(pwd)"     # start search from current directory
root_dir="/home/sourav739397/cp-library"  # start search from cp-library

# Recursive expansion function
expand() {
  local file="$1"
  local dir
  dir="$(dirname "$file")"

  if [[ ! -f "$file" ]]; then
    echo "// [WARN] Missing file: $file" >&2
    return
  fi

  # skip duplicate includes
  if [[ ${included["$file"]} ]]; then
    return
  fi
  included["$file"]=1

  local skip_comment=0
  local in_local_block=0

  while IFS= read -r line || [[ -n "$line" ]]; do
    # Keep #ifdef LOCAL ... #endif block as-is
    if [[ "$line" =~ ^[[:space:]]*#ifdef[[:space:]]+LOCAL ]]; then
      in_local_block=1
      echo "$line" >> "$tmp_file"
      continue
    fi

    if [[ "$in_local_block" -eq 1 ]]; then
      echo "$line" >> "$tmp_file"
      if [[ "$line" =~ ^[[:space:]]*#endif ]]; then
        in_local_block=0
      fi
      continue
    fi

    # Skip /* ... */ comments
    if [[ "$line" =~ ^[[:space:]]*/\* ]]; then
      skip_comment=1
      continue
    fi
    if [[ "$skip_comment" -eq 1 && "$line" =~ \*/ ]]; then
      skip_comment=0
      continue
    fi
    if [[ "$skip_comment" -eq 1 ]]; then
      continue
    fi

    # Expand #include "..."
    if [[ "$line" =~ ^[[:space:]]*#include[[:space:]]+\"([^\"]+)\" ]]; then
      local inc="${BASH_REMATCH[1]}"
      
      # Search for the file recursively from project root
      local inc_path
      inc_path=$(find "$root_dir" -type f -name "$inc" | head -n1)
      
      if [[ -z "$inc_path" ]]; then
        echo "// [WARN] Could not find include: $inc" >&2
      else
        expand "$inc_path"
      fi
    else
      # normal line
      echo "$line" >> "$tmp_file"
    fi
  done < "$file"
}

# Start expansion
expand "$orig_file"

# Overwrite original file safely
mv "$tmp_file" "$orig_file"
echo "✅ Expanded and overwritten $orig_file"
