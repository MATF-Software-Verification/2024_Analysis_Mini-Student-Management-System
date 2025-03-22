#!/bin/bash

# Postavljanje putanja
SRC_DIR="../Mini-Student-Management-System/src"
INCLUDE_DIR="../Mini-Student-Management-System/include"
PROJECT_DIR="../Mini-Student-Management-System"
OUTPUT_FILE="clang_tidy_report_$(date +%Y%m%d%H%M%S).txt"

# Opcije za Clang-Tidy
CLANG_TIDY_OPTIONS="-checks=clang-diagnostic-*,clang-analyzer-*,modernize-use-auto,modernize-use-nullptr,modernize-use-noexcept,modernize-use-emplace,modernize-use-emplace-back,modernize-loop-convert,modernize-use-using"

# Brisanje prethodnih rezultata ako postoje
if [ -f "$OUTPUT_FILE" ]; then
    rm "$OUTPUT_FILE"
fi

echo "Pokreće se Clang-Tidy analiza sa detaljnom konfiguracijom..."

# Pokretanje Clang-Tidy nad svim .cpp fajlovima u /src direktorijumu
for file in "$SRC_DIR"/*.cpp; do
    echo "Analiziram fajl: $file"
    clang-tidy "$file" -p="$PROJECT_DIR" $CLANG_TIDY_OPTIONS >> "$OUTPUT_FILE" 2>&1
done

echo "Analiza završena. Izveštaj sačuvan u: $OUTPUT_FILE"
