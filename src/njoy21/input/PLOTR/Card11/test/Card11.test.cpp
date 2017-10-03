#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "njoy21.hpp"

using namespace njoy::njoy21::input;

SCENARIO( "Validating card11 inputs",
          "[PLOTR], [Card11]" ){

  GIVEN( "valid PLOTR Card11 inputs" ){
    WHEN( "All values are given" ){
      iRecordStream<char> issCard11(
            std::istringstream(" 10.0 50.0 2.0 -3.0 -2.0 -0.5 / " ) );
      PLOTR::Card11 card11(issCard11);

      THEN( "the members can be tested" ){
        REQUIRE( APPROX( 10.0 ) == card11.xv.value );
        REQUIRE( APPROX( 50.0 ) == card11.yv.value );
        REQUIRE( APPROX( 2.0 ) == card11.zv.value );
        REQUIRE( APPROX( -3.0 ) == card11.x3.value );
        REQUIRE( APPROX( -2.0 ) == card11.y3.value );
        REQUIRE( APPROX( -0.5 ) == card11.z3.value );
      }
    } //WHEN
    WHEN( "All zeros" ){
      iRecordStream<char> issCard11( std::istringstream(
                           " 0.0 0.0 0.0 0.0 0.0 0.0 / " ) );
      PLOTR::Card11 card11(issCard11);

      THEN( "the members can be tested" ){
        REQUIRE( APPROX( 0.0 ) == card11.xv.value );
        REQUIRE( APPROX( 0.0 ) == card11.yv.value );
        REQUIRE( APPROX( 0.0 ) == card11.zv.value );
        REQUIRE( APPROX( 0.0 ) == card11.x3.value );
        REQUIRE( APPROX( 0.0 ) == card11.y3.value );
        REQUIRE( APPROX( 0.0 ) == card11.z3.value );
      }
    } //WHEN
    WHEN( "No values" ){
      iRecordStream<char> issCard11( std::istringstream( " /" ) );
      PLOTR::Card11 card11(issCard11);

      THEN( "the default values are returned" ){
        REQUIRE( APPROX( 15.0 ) == card11.xv.value );
        REQUIRE( APPROX( -15.0 ) == card11.yv.value );
        REQUIRE( APPROX( 15.0 ) == card11.zv.value );
        REQUIRE( APPROX( 2.5 ) == card11.x3.value );
        REQUIRE( APPROX( 6.5 ) == card11.y3.value );
        REQUIRE( APPROX( 2.5 ) == card11.z3.value );
      }
    }
  } // GIVEN
}//SCENARIO
