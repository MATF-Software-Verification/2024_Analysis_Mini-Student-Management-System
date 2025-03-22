#!/bin/bash

set -e  # Zaustavi ako bilo koja komanda ne uspe

# 📂 Putanje
PROJECT_DIR="../Mini-Student-Management-System"
BUILD_DIR="build"
COV_DIR="coverage"

# Očisti prethodne pokrivenosti i binarne fajlove
rm -rf ${BUILD_DIR} ${COV_DIR} *.gcda *.gcno *.csv
mkdir -p ${BUILD_DIR} ${COV_DIR}

# revodjenje sa opcijama za pokrivenost
g++ -o ${BUILD_DIR}/test_all tests/test_all.cpp ${PROJECT_DIR}/src/*.cpp \
    -I ${PROJECT_DIR}/include \
    -std=c++11 -Wno-format -D UNIT_TESTING --coverage

# Pokreni unit testove
./${BUILD_DIR}/test_all 


# Prikupljanje podataka o pokrivenosti
lcov --capture --directory ${BUILD_DIR} --output-file ${COV_DIR}/coverage.info

# Filtriranje da pokrije samo kod iz `Mini-Student-Management-System/src`
lcov --remove ${COV_DIR}/coverage.info "/usr/*" '*/include/*' '*/catch.hpp' --output-file ${COV_DIR}/filtered_coverage.info

# Generisanje HTML izveštaja
genhtml ${COV_DIR}/filtered_coverage.info --output-directory ${COV_DIR}

echo "Pokrivenost generisana! Otvori coverage/index.html u browseru."
