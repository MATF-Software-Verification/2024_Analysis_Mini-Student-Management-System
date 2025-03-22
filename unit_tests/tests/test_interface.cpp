#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/interface.h"
#include <sstream>

TEST_CASE("Operator >> za Csv::multitype radi ispravno") {
    std::istringstream input("TestString");
    Csv::multitype value;
    input >> value;

    REQUIRE(value.to_str() == std::string("TestString"));
}

TEST_CASE("Operator << za Csv::multitype radi ispravno") {
    std::ostringstream output;
    Csv::multitype value("OutputTest");
    output << value;

    REQUIRE(output.str() == "OutputTest");
}

TEST_CASE("readline funkcija čita red ispravno") {
    std::istringstream input("This is a test\n");
    Csv::multitype result;
    
    readline(input, result);
    
    REQUIRE(std::string(result.to_str()) == "This is a test");
}

TEST_CASE("print_note ispisuje tačne vrednosti") {
    std::ostringstream output;
    Interface::print_note("Ovo je test", "Naslov", false, output);
    
    std::string expected =
        "[ NOTE: Naslov ]\n"
        "____\n"
        "\n"
        "Ovo je test\n"
        "____\n"
        "\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("select_menu funkcije rade ispravno") {
    Interface::select_menu menu;
    menu.set_title("Meni test");
    menu.add_item(1, "Opcija 1");
    menu.add_item(2, "Opcija 2");

    std::istringstream input("1\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE(std::string(menu.print_menu_and_wait(false, std::cout).to_str()) == "1"); 
    std::cin.rdbuf(std::cin.rdbuf());


    REQUIRE(menu.remove_item_by_no(1) == true);
    REQUIRE(menu.remove_item_by_no(1) == false);  
}

TEST_CASE("input_menu funkcije rade ispravno") {
    Interface::input_menu menu;
    menu.set_title("Input meni test");

    menu.add_item("Unesite broj", true);
    menu.add_item("Unesite tekst", false);

    std::istringstream input("42\ntext\n");
    std::ostringstream output;
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    auto results = menu.print_menu_and_wait(false, output);

    std::cin.rdbuf(cin_backup);

    REQUIRE(results.size() == 2);
    REQUIRE(results.at(0).to_int() == 42);
    REQUIRE(std::string(results.at(1).to_str()) == "text");

    REQUIRE(menu.remove_item_by_desc("Unesite broj", true) == true);  
    REQUIRE(menu.remove_item_by_desc("Nepostojeći unos", true) == false); 
}
