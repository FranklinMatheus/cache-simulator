#ifndef _SIMULATOR_HPP_
#define _SIMULATOR_HPP_

    #include "common.hpp"

    struct Command
    {
        std::string name;
        int address;
        int content;

        Command( std::string n_, int a_, int c_ = 0 )
            : name( n_ )
            , address( a_ )
            , content( c_ )
        { /* empty */ }
    };

    void execute_simulator( std::vector< int > & );
    void read( const int & , Cache &, Memory &, std::vector< int > &, const int & );
    void write( const int & , const int & , Cache &, Memory &, std::vector< int > &, const int & );
    void show_details( const std::vector< int > & );

#endif