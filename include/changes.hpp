#ifndef _CHANGES_HPP_
#define _CHANGES_HPP_

    struct Changes
    {
        int line_index;
        int block_index;

        Changes( int l_, int b_ )
            : line_index( l_ )
            , block_index( b_ )
        { /* empty */ }
    };

#endif