#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/csv_import.h"
#include "../../Mini-Student-Management-System/include/interface.h"


using namespace SMS;

struct SetupCSVTests {
    SetupCSVTests() {
        init_all_csvs();  
    }
};

TEST_CASE_METHOD(SetupCSVTests, "Reading a valid CSV file", "[csv_valid_read_util]") {
    Csv::csv_handler test_handler("db/courses.csv");  
    REQUIRE_NOTHROW(csv_read_util(test_handler, "courses", {"Course ID", "Course name", "Class"}));
    
    Csv::table& table = test_handler.get_table();
    REQUIRE(table.has_key("Course ID"));
    REQUIRE(table.has_key("Course name"));
    REQUIRE(table.has_key("Class"));
}

TEST_CASE_METHOD(SetupCSVTests, "Handling missing CSV file", "[csv_invalid_read_util]") {
    Csv::csv_handler fake_handler("db/fake.csv");  

    REQUIRE_THROWS_AS(csv_read_util(fake_handler, "fake", {"ID", "Name"}), std::runtime_error);
}

TEST_CASE_METHOD(SetupCSVTests, "Initializing all CSV files", "[init_all_csvs]") {
    REQUIRE_NOTHROW(init_all_csvs());  
    REQUIRE(attendancelist.get_table().num_rows() > 0);
    REQUIRE(courses.get_table().num_rows() > 0);
    REQUIRE(scoreboard.get_table().num_rows() > 0);
}
