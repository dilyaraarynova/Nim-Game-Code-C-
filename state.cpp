
#include "state.h"
#include <string>

state::state( std::initializer_list< unsigned int > init )
{ 
   for (unsigned int val : init) {
      sticks.push_back(val);
   }
}

state::state( unsigned int i1, unsigned int i2 )
{ 
   sticks = std::vector<unsigned int>(i2 - i1 + 1);

   unsigned int val = i1;

   for (unsigned int i = 0; i <= i2 - i1; i++) {
      sticks.at(i) = val;
      val++;
   }
}

unsigned int state::sum( ) const 
{
   unsigned int sum = 0;

   for (unsigned int i = 0; i < sticks.size(); i++) {
      sum += sticks.at(i);
   }

   return sum;
}

std::optional< move > state::randommove( ) const 
{ 
   if (sum ()) {
      unsigned int row = rand () % sticks.size() + 1;

      if (sticks.at(row - 1) == 0) {
         while (sticks.at(row - 1) == 0) {
            row = rand() % sticks.size() + 1;
         }
      }

      unsigned int remain = rand() % (sticks.at(row - 1));

      return move( row - 1, remain );
   } 
   else 
      return std::optional< move > ( );
}


std::optional< move >
state::usermove( std::ostream& out, std::istream& in ) const
{
   // It seems to me that usermove( ) is the same as randommove( ),
   // with the only difference that rand( ) should be replaced by
   // user( ). We could make it into a template. 

   if( sum( ))
   {
      while( true )
      {
         std::string inp;
         try
         {
            out << "row? "; out. flush( );
            in >> inp; 

            unsigned int row = std::stoul( inp ); inp. clear( );

            if( row > 0 && row <= sticks. size( )) 
            {
               unsigned int row1 = row - 1;  // This is a type conversion! 
               if( sticks[ row1 ] )
               {
                  out << "how many remaining? "; out. flush( );
                  in >> inp; 
                  unsigned int remain = std::stoul( inp ); inp. clear( ); 

                  if( remain < sticks[ row1 ] )
                     return move( row1, remain );
                  else
                  {
                     out << "having " << remain 
                         << " remaining is not possible, "
                         << "you have to remove at least one stick\n";
                  }
               }
               else 
               {
                  out << "row " << row << " is already empty\n";
               }
            }
            else
            {
               out << "row " << row << " is not a valid row, ";
               out << "rows are between 1 and " << sticks. size( ) << "\n";
            }
            
         }
         catch( std::invalid_argument& inv )
         {
            out << inp << " is not a number\n";
         }
         catch( std::out_of_range& r )
         {
            out << inp << " is too big\n";
         }
      }
   }
   else
      return std::optional< move > ( );
}


void state::make( move m )
{ 
  if (sticks.at(m.row) == 0 || m.remaining > sticks.at(m.row)) {
   std::abort();
  } 
  sticks.at(m.row) = m.remaining;  
}

std::optional<move> state::removelastmorethantwo() const {

   int cnt_rows_two = 0, row_two = -1;

   for (unsigned int i = 0; i < sticks.size(); ++i) {
      if (sticks[i] >= 2) {
         cnt_rows_two++;
         row_two = i;
      }
   }
   
   if (cnt_rows_two != 1) {
      return std::nullopt;
   }

   int cnt_rows_one = 0;

   for (unsigned int i = 0; i < sticks.size(); ++i) {
      if (sticks[i] == 1) {
         cnt_rows_one++;
      }
   }

   if (cnt_rows_one == 0) {
      return move(row_two, sticks[row_two]);
   }

   int remaining_sticks = sticks[row_two];

   for (unsigned int i = 0; i < sticks.size(); ++i) {

      if (i == row_two) {
         continue;
      }

      if (sticks[i] == 1) {
         remaining_sticks ^= 1;
      }
   }
   return move(row_two, remaining_sticks);
}


unsigned int state::nimber() const {

   unsigned int res = 0;

   for (unsigned int i = 0; i < sticks.size(); ++i) {
      res ^= sticks[i];
   }

   return res;
}

std::optional<move> state::makenimberzero() const
{
   unsigned int n = nimber();

   if (n == 0) {
      return std::nullopt;
   }

   while (true) {

      int row = rand() % sticks.size();
      unsigned int new_sticks = sticks[row] ^ n;

      if (new_sticks < sticks[row]) {
         return move(row, new_sticks);
      }
   }
}

void state::print( std::ostream& out ) const
{
   for (unsigned int i = 0; i < sticks.size(); i++) {
      out << i + 1 << ": "; 
      for (unsigned int j = 0; j < sticks.at(i); j++) {
         out << 1 << " ";
      }
      out << '\n';
   }
}


