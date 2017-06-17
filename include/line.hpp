#ifndef _LINE_HPP_
#define _LINE_HPP_

    #include <ostream>
    #include "block.hpp"

    struct Line
    {
        int m_index;
        Block m_block;

        // essetial to substitute
        int last_time_used;
        int times_used;
        int age;

        Line( int i_, int line_size, int a_ = 0 )
            : m_index( i_ )
            , m_block ( Block( -1, line_size ) )
            , age( a_ )
        { /* empty */ }

        void operator=( const Block &block_ )
        {
            m_block = block_;
        } 

        friend std::ostream & operator<<( std::ostream &os_, const Line &line_  )
        {
            for( auto word : line_.m_block.m_words )
            {
                os_ << line_.m_index << "\t";
                
                if( line_.m_block.m_index != -1 )
                    os_ << line_.m_block.m_index << "\t";
                else
                    os_ << "#\t";
                
                os_ << word << "\n";
        }
            return os_;
        }
    };

#endif