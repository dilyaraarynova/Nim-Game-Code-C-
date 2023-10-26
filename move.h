
#ifndef MOVE_
#define MOVE_ 1

#include <iostream>
#include <optional>

struct move
{
   unsigned int row;
   unsigned int remaining;

   move( unsigned int row, unsigned int remaining )
      : row( row ), remaining( remaining )
   { }
};

inline std::ostream& operator << ( std::ostream& out, move m )
{
   out << "move( " << m. row << ", " << m. remaining << " )";
   return out; 
}


inline 
std::ostream& 
operator << ( std::ostream& out, const std::optional< move > & opt )
{
   if( opt. has_value( ))  
      out << opt. value( );
   else
      out << "(undefined move)";
   return out;
}

 
#endif

