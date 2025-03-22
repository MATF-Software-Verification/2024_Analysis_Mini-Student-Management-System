#!/bin/bash

callgrind_output_file="callgrind.out.$(date +%Y%m%d%H%M%S)"   # Fajl sa Callgrind podacima
callgrind_annotate_output_file="callgrind_annotate_$(date +%Y%m%d%H%M%S).txt"  # Tekstualni izveštaj

# Putanja do izvršnog fajla
EXECUTABLE="../../Mini-Student-Management-System/MSMS"

# Pokretanje Callgrind analize
echo "Pokrećem Valgrind Callgrind analizu..."
valgrind --tool=callgrind --callgrind-out-file=$callgrind_output_file $EXECUTABLE

# Generisanje čitljivog izveštaja
echo "Generišem tekstualni izveštaj..."
callgrind_annotate --auto=yes $callgrind_output_file > $callgrind_annotate_output_file

# Prikaz lokacije rezultata
echo "naliza završena!"
echo "Callgrind podaci sačuvani u: $callgrind_output_file"
echo "Annotirani izveštaj dostupan u: $callgrind_annotate_output_file"

# Omogućavanje vizuelizacije
echo "Pokreni KCacheGrind za vizuelnu analizu pomoću:"
echo "kcachegrind $callgrind_output_file"

