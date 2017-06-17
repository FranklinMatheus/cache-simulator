#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

    #include "common.hpp"

    struct Block
    {
        int m_index;
        std::vector< Word > m_words;

        Block( int i_, int block_size )
            : m_index( i_ )
        {
            if( i_ >= 0 )
            {
                for( auto i( i_*block_size ); i < ( i_ + 1 )*block_size; ++i )
                {
                    m_words.push_back( Word( i, 0 ) );
                }
            }
            else
            {
                for( auto i( 0 ); i < block_size; ++i )
                {
                    m_words.push_back( Word() );
                }
            }
        }

        friend std::ostream & operator<<( std::ostream &os_, const Block &block_  )
        {
            for( auto word : block_.m_words )
            {
                os_ << block_.m_index << "\t" << word << "\n";
            }
            return os_;
        }
    };

#endif