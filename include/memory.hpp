#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

    #include "common.hpp"

    class Memory
    {
        size_t m_size;
        std::vector< Block > m_blocks;

        public:
            Memory( size_t l_ = 0 , int block_size = 0 )
                : m_size( l_ )
            {
                for( auto i(0u); i < l_; ++i )
                {
                    m_blocks.push_back( Block( i, block_size ) );
                }
            }

            Block get_block( const int index )
            {
                return m_blocks[index];
            }

            void change_content( const int content, const int address, const int block_index )
            {
                for( auto & word : m_blocks[block_index].m_words )
                {
                    if( word.m_address == address )
                    {
                        word.m_content = content;
                        return;
                    }
                }
            }

            void write_back( const Block &block_ )
            {
                for( auto & block : m_blocks )
                {
                    if( block.m_index == block_.m_index )
                    {
                        if( block_.m_words[0].m_address != -1 )
                        {
                            block.m_words = block_.m_words;
                            return;
                        }
                    }
                }
            }

            friend std::ostream & operator<<( std::ostream &os_, const Memory &memory_ )
            {
                os_ << "=========================\n";
                os_ << "MEMORY\n";
                os_ << "-------------------------\n";
                os_ << "bloco\tend.\tcont.\n";
                os_ << "-------------------------\n";
                for( auto block : memory_.m_blocks )
                {
                    os_ << block;
                }
                os_ << "=========================\n";
                return os_;
            }
    };

#endif