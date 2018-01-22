#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "njoy21.hpp"

using namespace njoy::njoy21::input;

SCENARIO( "POWR, Lib1, Card3, Rtemp",
          "[POWR] [Lib1] [Card3] [Rtemp]" ){
  GIVEN( "valid input" ){
    WHEN( "valid inputs are provided" ){
      for( double t : {0.0, 10.0, 100.0, 1000.0, 10000.0} ){
        iRecordStream<char> iss( std::istringstream( std::to_string( t ) ) );

        THEN( "the values can be verified" ){
          REQUIRE( t*dimwits::kelvin == argument::extract<
                                      POWR::Lib1::Card3::Rtemp >( iss ).value );
        }
      }
    } // WHEN

    WHEN( "no input is provided" ){
      iRecordStream<char> iss( std::istringstream( " /" ) );

      THEN( "the default value can be verified" ){
        REQUIRE( 300.0*dimwits::kelvin == argument::extract<
                                      POWR::Lib1::Card3::Rtemp >( iss ).value );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "invalid input" ){
    WHEN( "invalid values are provided" ){
      for( auto t : {-100.0, -10.0, -1.0, -0.1} ){
        iRecordStream<char> iss( std::istringstream( std::to_string( t ) ) );

        THEN( "an exception is thrown" ){
          REQUIRE_THROWS( argument::extract< POWR::Lib1::Card3::Rtemp >(
                                                                  iss ).value );
        }
      }
    }
  } // GIVEN
} // SCENARIO
