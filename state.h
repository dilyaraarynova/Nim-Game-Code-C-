
#ifndef STATE_
#define STATE_  1

#include <vector>
#include <iostream>

#include "move.h"

struct state 
{

   std::vector< unsigned int > sticks; 

   state( std::initializer_list< unsigned int > init ); 
   state( unsigned int i1, unsigned int i2 );

   unsigned int sum( ) const; 
   
   std::optional< move > randommove( ) const;
      // If there are sticks, then return a valid random move.
      // Note that row is the index in sticks, not the 
      // number that is shown to the user by print( ).

   void make( move m ); 
      // Make move m. We assume that move m is possible

   std::optional< move >
   usermove( std::ostream& out, std::istream& in ) const;

   void print( std::ostream& out ) const;

   std::optional<move>removelastmorethantwo() const; 

   unsigned int nimber() const;

   std::optional<move> makenimberzero( ) const;
};


inline std::ostream& operator << ( std::ostream& out, const state& st )
{
   st. print( out );
   return out;
}

#endif

