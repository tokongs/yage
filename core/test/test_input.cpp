#include "catch2/catch.hpp"

unsigned int Factoria( unsigned int number ) {
    return number <= 1 ? number : Factoria(number-1)*number;
}

TEST_CASE( "Factorials are computssssed", "[factorial]" ) {
    REQUIRE( Factoria(1) == 1 );
    REQUIRE( Factoria(2) == 2 );
    REQUIRE( Factoria(3) == 6 );
    REQUIRE( Factoria(10) == 3628800 );
    REQUIRE( Factoria(11) == 3628800 );
}