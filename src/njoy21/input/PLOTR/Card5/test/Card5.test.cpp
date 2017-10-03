#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "njoy21.hpp"

using namespace njoy::njoy21::input;

SCENARIO( "Validating card5 inputs",
          "[PLOTR], [Card5]" ){
  // Simple values to create a PLOTR::Card4 with no Xtag value.
  iRecordStream<char> issCard4( std::istringstream( "1 0 / " ) );

  GIVEN( "valid PLOTR Card5 inputs" ){
    WHEN( "All values are given" ){
      Argument< PLOTR::Card4 > card4( issCard4 );
      iRecordStream<char> issCard5(
            std::istringstream(" 10.0 50.0 2 / " ) );
      PLOTR::Card5 card5( issCard5, &card4 );

      THEN( "the members can be tested" ){
        REQUIRE( APPROX( 10.0 ) == card5.el.value );
        REQUIRE( APPROX( 50.0 ) == card5.eh.value );
        REQUIRE( APPROX( 2.0 ) == card5.xstep.value );
        REQUIRE( APPROX( 10.0 ) == card4.xtag.value );
      }
    } //WHEN
    WHEN( "A couple defaults are used" ){
      Argument< PLOTR::Card4 > card4( issCard4 );
      iRecordStream<char> issCard5( std::istringstream(" 500.0 400000.0 / " ) );
      PLOTR::Card5 card5( issCard5, &card4 );

      THEN( "the members can be tested" ){
        REQUIRE( APPROX( 500.0 ) == card5.el.value );
        REQUIRE( APPROX( 400000.0 ) == card5.eh.value );
        REQUIRE( APPROX( 1.0 ) == card5.xstep.value );
        REQUIRE( APPROX( 500.0 ) == card4.xtag.value );
      }
    } //WHEN
    WHEN( "No values are given" ){
      Argument< PLOTR::Card4 > card4( issCard4 );
      iRecordStream<char> issCard5( std::istringstream(" / "));
      PLOTR::Card5 card5( issCard5, &card4 );

      THEN( "the members can be tested" ){
        REQUIRE( APPROX( 0.0 ) == card5.el.value );
        REQUIRE( APPROX( 1.0 ) == card5.eh.value );
        REQUIRE( APPROX( 1.0 ) == card5.xstep.value );
        REQUIRE( APPROX( 0.0 ) == card4.xtag.value );
      }
    } //WHEN
  } // GIVEN

  GIVEN( "invalid inputs" ){
    Argument< PLOTR::Card4 > card4( issCard4 );
    WHEN( "All values are wrong" ){
      iRecordStream<char> issCard5( std::istringstream(
             "-1.0 1.0 0.5/" ) );
  
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( PLOTR::Card5(issCard5, &card4) );
      }
    }//WHEN
    WHEN( "One value is wrong" ){
      {
        iRecordStream<char> issCard5( std::istringstream(
              "1.0 -1.0 0.5/" ) );

        THEN( "an exception is thrown" ){
          REQUIRE_THROWS( PLOTR::Card5(issCard5, &card4) );
        }
      }{
        iRecordStream<char> issCard5( std::istringstream(
              "1.0 4.0 -0.6/" ) );

        THEN( "an exception is thrown" ){
          REQUIRE_THROWS( PLOTR::Card5(issCard5, &card4) );
        }
      }
    }//WHEN
    WHEN( "An extra value is given" ){
      iRecordStream<char> issCard5( std::istringstream(
            "1.0 10.0 1.0 20 /" ) );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( PLOTR::Card5(issCard5, &card4) );
      }
    }//WHEN
  }//GIVEN
}//SCENARIO
