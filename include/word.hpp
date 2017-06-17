#ifndef _WORD_HPP_
#define _WORD_HPP_

    #include "common.hpp"

    struct Word
    {
        int m_address;
        int m_content;

        Word( int a_ = -1, int c_ = 0 )
            : m_address( a_ )
            , m_content( c_ )
        { /* empty */ }

        friend std::ostream & operator<<( std::ostream &os_, const Word &word_  )
        {
            if( word_.m_address != -1 )
                os_ << word_.m_address << "\t";
            else
                os_ << "#\t";

             os_ << word_.m_content;
            return os_;
        }
    };

#endif