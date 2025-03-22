#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/date.h"
#include <iostream>

TEST_CASE("Testiranje konstruktora date") {
    date d(2024, 2, 29, 14, 30);  
    REQUIRE(d.year == 2024);
    REQUIRE(d.month == 2);
    REQUIRE(d.day == 29);
    REQUIRE(d.hour == 14);
    REQUIRE(d.minute == 30);

    date d2(2023, 4, 31, 10, 0);  
    REQUIRE(d2.day == 30);
}

TEST_CASE("Testiranje metode now()") {
    date d;
    d.now();  
    REQUIRE(d.year > 2020);  
    REQUIRE(d.month >= 1);
    REQUIRE(d.month <= 12);
    REQUIRE(d.day >= 1);
    REQUIRE(d.day <= 31);
}

TEST_CASE("Testiranje metode compile()") {
    date d(2024, 12, 25, 10, 15);
    
    Csv::multitype format("YYYY-MM-DD");
    Csv::multitype formattedDate = d.compile(format);

    std::string formattedStr = formattedDate.to_str();
    
    REQUIRE(formattedStr == "2024-12-25");
}


TEST_CASE("Testiranje metode add_day()") {
    date d(2024, 2, 28, 10, 30);
    date d2 = d.add_day(1);  
    REQUIRE(d2.day == 29);

    date d3 = d2.add_day(1);
    REQUIRE(d3.day == 1);
    REQUIRE(d3.month == 3);
}

TEST_CASE("Testiranje operacija poredjenja") {
    date d1(2024, 2, 15, 12, 0);
    date d2(2024, 2, 16, 12, 0);

    REQUIRE(d1 < d2);
    REQUIRE(d2 > d1);
    REQUIRE(d1 != d2);

    date d3 = d1;
    REQUIRE(d1 == d3);
}

TEST_CASE("Testiranje metode substract()") {
    date d1(2024, 2, 1, 10, 0);
    date d2(2024, 2, 10, 10, 0);

    REQUIRE(d2.substract(d1) == 9);
    REQUIRE(d1.substract(d2) == -9);
}
