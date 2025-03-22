#!/bin/bash

# Alat pokrecemo nad unit testovima
EXECUTABLE="../../Mini-Student-Management-System/MSMS"

# Fajl u koji će se sačuvati rezultati
OUTPUT_FILE="valgrind_memcheck_output_$(date +%Y%m%d%H%M%S).txt"

# Pokrećemo program kroz valgrind sa memcheck opcijom i upisujemo rezultat u fajl
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$OUTPUT_FILE $EXECUTABLE

echo "Valgrind memcheck test završen. Rezultati su u fajlu: $OUTPUT_FILE"