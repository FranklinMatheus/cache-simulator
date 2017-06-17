#ifndef _CACHE_HPP_
#define _CACHE_HPP_

    #include "common.hpp"

    class Cache
    {
        size_t m_size;
        std::vector< Line > m_lines;
        
        public:
            Cache( size_t l_ = 0 , int line_size = 0 )
                : m_size( l_ )
            {
                for( auto i(0u); i < l_; ++i )
                {
                    m_lines.push_back( Line( i, line_size ) );
                }
            }

            bool is_allocated( const int &address, std::vector< int > &parameters )
            {
                int temp_block = address/parameters[0];
                auto temp_line( -1 );

                switch( parameters[3] )
                {
                    case 1: // <! mapeamento direto
                        temp_line = temp_block % parameters[1];
                        if( m_lines[temp_line].m_block.m_index == temp_block )
                        {
                            return true;
                        }
                        break;
                    case 2: // <! mapeamento totalmente associativo
                        for( auto i( 0u ); i < m_lines.size(); ++i )
                        {
                            if( m_lines[i].m_block.m_index == temp_block )
                            {
                                return true;
                            }
                        }
                        break;
                    case 3: // <! mapeamento parcialmente associativo
                        int set_size = parameters[1]/parameters[4]; // set_size = cache_lines / num_sets
                        int set = temp_block % parameters[4]; // set = block_index % num_sets

                        for( auto i( set*set_size ); i < set*set_size + set_size; ++i )
                        {
                            if( m_lines[i].m_block.m_index == temp_block )
                            {
                                return true;
                            }
                        }
                        break;
                }
                return false;
            }

            void address_used( const int address, const int clock, const std::vector< int > &parameters )
            {
                int temp_block = address/parameters[0];
                auto temp_line( -1 );

                switch( parameters[3] )
                {
                    case 1: // <! mapeamento direto
                        temp_line = temp_block % parameters[1];
                        m_lines[temp_line].times_used++;
                        m_lines[temp_line].last_time_used = clock;
                    
                        break;
                    case 2: // <! mapeamento totalmente associativo
                        for( auto i( 0u ); i < m_lines.size(); ++i )
                        {
                            if( m_lines[i].m_block.m_index == temp_block )
                            {
                                m_lines[i].times_used++;
                                m_lines[i].last_time_used = clock;
                                break;
                            }
                        }
                    case 3: // <! mapeamento parcialmente associativo
                        int set_size = parameters[1]/parameters[4]; // set_size = cache_lines / num_sets
                        int set = temp_block % parameters[4]; // set = block_index % num_sets

                        for( auto i( set*set_size ); i < set*set_size + set_size; ++i )
                        {
                            if( m_lines[i].m_block.m_index == temp_block )
                            {
                                m_lines[i].times_used++;
                                m_lines[i].last_time_used = clock;
                            }
                        }
                        break;
                }
            }

            void write_content( const int address, const int content, Memory &mem, std::vector< int > &parameters )
            {
                int temp_block_index = address/parameters[0];
                auto temp_line( -1 );

                switch( parameters[3] )
                {
                    case 1: // <! mapeamento direto
                        temp_line = temp_block_index % parameters[1];

                        for( auto & word : m_lines[temp_line].m_block.m_words )
                        {
                            if( word.m_address == address )
                            {
                                word.m_content = content;
                                std::cout << "\n[NOW] the address " << address << " has a content equal to: " << content << "\n\n";
                            }
                        }

                        if ( parameters[6] == 2 )
                        {    
                            mem.change_content( content, address, temp_block_index );
                        }
                        break;
                    case 2: // <! mapeamento totalmente associativo
                        for( auto i( 0u ); i < m_lines.size(); ++i )
                        {
                            if( m_lines[i].m_block.m_index == temp_block_index )
                            {
                                for( auto & word : m_lines[i].m_block.m_words )
                                {
                                    if( word.m_address == address )
                                    {
                                        word.m_content = content;
                                        std::cout << "\n[NOW] the address " << address << " has a content equal to: " << content << "\n\n";
                                    }
                                }

                                if ( parameters[6] == 2 )
                                {    
                                    mem.change_content( content, address, temp_block_index );
                                }
                            }
                        }
                        break;
                    case 3: // <! mapeamento parcialmente associativo
                        int set_size = parameters[1]/parameters[4]; // set_size = cache_lines / num_sets
                        int set = temp_block_index % parameters[4]; // set = block_index % num_sets

                        for( auto i( set*set_size ); i < set*set_size + set_size; ++i )
                        {
                            if( m_lines[i].m_block.m_index == temp_block_index )
                            {
                                for( auto & word : m_lines[i].m_block.m_words )
                                {
                                    if( word.m_address == address )
                                    {
                                        word.m_content = content;
                                        std::cout << "\n[NOW] the address " << address << " has a content equal to: " << content << "\n\n";
                                    }
                                }
                                if ( parameters[6] == 2 )
                                {    
                                    mem.change_content( content, address, temp_block_index );
                                }
                            }
                        }
                        break;
                }
            }

            void mapping_invalid( int &identifier_ )
            {
                auto temp(0);
                std::cout << "\n===============================\n";
                std::cout << "MAPPING ERROR! THE CORRECT WAS: \n";
                std::cout << "1 to DIRECT MAPPING\n";
                std::cout << "2 to TOTALLY ASSOCIATIVE\n";
                std::cout << "3 to ASSOCIATIVE BY JOINT\n";
                std::cout << "and you passed " << identifier_;
                std::cout << "\n===============================\n";
                std::cout << "By this way, insert a valid mapping identifier: ";
                std::cin >> temp;
                if( temp != 1 and temp != 2 and temp != 3 )
                {
                    std::cout << "INVALID IDENTIFIER AGAIN! YOU SHALL NOT PASS!\n\n\n";
                    exit(0);
                }
                identifier_ = temp;
            }

            void write_invalid( int &identifier_ )
            {
                auto temp(0);
                std::cout << "\n===============================\n";
                std::cout << "WRITE ERROR! THE CORRECT WAS: \n";
                std::cout << "1 to WRITE-BACK\n";
                std::cout << "2 to WRITE-THROUGH\n";
                std::cout << "and you passed " << identifier_;
                std::cout << "\n===============================\n";
                std::cout << "By this way, insert a valid write identifier: ";
                std::cin >> temp;
                if( temp != 1 and temp != 2 )
                {
                    std::cout << "INVALID IDENTIFIER AGAIN! YOU SHALL NOT PASS!\n\n\n";
                    exit(0);
                }
                identifier_ = temp;
            }

            void substitution_invalid( int &identifier_ )
            {
                auto temp(0);
                std::cout << "\n===============================\n";
                std::cout << "SUBSTITUTION ERROR! THE CORRECT WAS: \n";
                std::cout << "1 to RANDOM SUBSTITUTION\n";
                std::cout << "2 to FIFO SUBSTITUTION\n";
                std::cout << "3 to LFU SUBSTITUTION\n";
                std::cout << "4 to LRU SUBSTITUTION\n";
                std::cout << "and you passed " << identifier_;
                std::cout << "\n===============================\n";
                std::cout << "By this way, insert a valid substitution identifier: ";
                std::cin >> temp;
                if( temp != 1 and temp != 2 and temp != 3 and temp != 4 )
                {
                    std::cout << "INVALID IDENTIFIER AGAIN! YOU SHALL NOT PASS!\n\n\n";
                    exit(0);
                }
                identifier_ = temp;
            }

            void allocate( const int address, Memory &mem ,const int clock, std::vector< int > &parameters )
            {
                int temp_block_index = address/parameters[0];
                auto temp_line( -1 );
                Block temp_block = mem.get_block( temp_block_index );

                switch( parameters[3] )
                {
                    case 1: // <! mapeamento direto
                        temp_line = temp_block_index % parameters[1];
                        
                        if( parameters[6] == 1 ) // caso a escrita for write-back
                            mem.write_back( m_lines[temp_line].m_block );
                        
                        m_lines[temp_line] = temp_block;
                        m_lines[temp_line].age = clock;

                        std::cout << "allocated at LINE " << temp_line;
                        std::cout << " \u27A4 BLOCK " << temp_block_index << " was substituted!\n";
                        break;
                    case 2: // <! mapeamento totalmente associativo
                        if( parameters[5] == 1 ) random( 0, m_lines.size(), temp_block, mem, parameters[6] );
                        else if( parameters[5] == 2 ) fifo( 0, m_lines.size(), temp_block, clock, mem, parameters[6] );
                        else if( parameters[5] == 3 ) lfu( 0, m_lines.size(), temp_block, clock, mem, parameters[6] );
                        else if( parameters[5] == 4 ) lru( 0, m_lines.size(), temp_block, clock, mem, parameters[6] );
                        else
                        {
                            substitution_invalid( parameters[5] );
                            return;
                        }
                        break;
                    case 3: // <! mapeamento parcialmente associativo
                        int set_size = parameters[1]/parameters[4]; // set_size = cache_lines / num_sets
                        int set = temp_block_index % parameters[4]; // set = block_index % num_sets

                        if( parameters[5] == 1 ) random( set*set_size, set*set_size + set_size, temp_block, mem, parameters[6] );
                        else if( parameters[5] == 2 ) fifo( set*set_size, set*set_size + set_size, temp_block, clock, mem, parameters[6] );
                        else if( parameters[5] == 3 ) lfu( set*set_size, set*set_size + set_size, temp_block, clock, mem, parameters[6] );
                        else if( parameters[5] == 4 ) lru( set*set_size, set*set_size + set_size, temp_block, clock, mem, parameters[6] );
                        else
                        {
                            substitution_invalid( parameters[5] );
                            return;
                        }
                        break;
                }
            }

            void random( int first_, int last_, Block block_, Memory &mem, const int write )
            {
                std::random_device r;
                std::default_random_engine eng( r() );
                std::uniform_int_distribution<int> uniform_dist( first_, last_-1 );
                int line_index = uniform_dist( eng );
                
                if( write == 1 ) // caso a escrita for write-back
                    mem.write_back( m_lines[line_index].m_block );

                m_lines[line_index] = block_;

                std::cout << "allocated at LINE " << line_index;
                std::cout << " \u27A4 BLOCK " << block_.m_index << " was substituted!\n";
            }

            void fifo( int first_, int last_, Block block_, const int clock, Memory &mem, const int write )
            {
                
                auto slow = m_lines.begin() + first_;
                auto fast = m_lines.begin() + first_;

                for( /* empty */ ; fast != m_lines.begin() + last_; ++fast )
                {
                    std::cout << fast->m_index << "\n";
                    if( fast->age < slow->age ) // clock de 'nascimento' for menor
                    {
                        slow = fast;
                    }
                }

                if( write == 1 ) // caso a escrita for write-back
                    mem.write_back( m_lines[slow->m_index].m_block );
                
                m_lines[slow->m_index].m_block = block_;
                // ajusta os valores quanto aos clocks
                m_lines[slow->m_index].age = clock;
                m_lines[slow->m_index].times_used = 0; // vai ser incrementado em address_used()
                m_lines[slow->m_index].last_time_used = clock;

                std::cout << "allocated at LINE " << slow->m_index;
                std::cout << " \u27A4 BLOCK " << block_.m_index << " was substituted!\n";
            }

            void lfu( int first_, int last_, Block block_, const int clock, Memory &mem, const int write )
            {
                auto slow = m_lines.begin() + first_;
                auto fast = m_lines.begin() + first_;

                for( /* empty */ ; fast != m_lines.begin() + last_; ++fast )
                {
                    if( fast->times_used < slow->times_used )
                    {
                        slow = fast;
                    }
                }

                if( write == 1 ) // caso a escrita for write-back
                    mem.write_back( m_lines[slow->m_index].m_block );
                
                m_lines[slow->m_index].m_block = block_;
                // ajusta os valores quanto aos clocks
                m_lines[slow->m_index].age = clock;
                m_lines[slow->m_index].times_used = 0; // vai ser incrementado em address_used()
                m_lines[slow->m_index].last_time_used = clock;

                std::cout << "allocated at LINE " << slow->m_index;
                std::cout << " \u27A4 BLOCK " << block_.m_index << " was substituted!\n";
            }

            void lru( int first_, int last_, Block block_, const int clock, Memory &mem, const int write )
            {
                auto slow = m_lines.begin() + first_;
                auto fast = m_lines.begin() + first_;

                for( /* empty */ ; fast != m_lines.begin() + last_; ++fast )
                {
                    if( fast->last_time_used < slow->last_time_used )
                    {
                        slow = fast;
                    }
                }

                if( write == 1 ) // caso a escrita for write-back
                    mem.write_back( m_lines[slow->m_index].m_block );
                
                m_lines[slow->m_index].m_block = block_;
                // ajusta os valores quanto aos clocks
                m_lines[slow->m_index].age = clock;
                m_lines[slow->m_index].times_used = 0; // vai ser incrementado em address_used()
                m_lines[slow->m_index].last_time_used = clock;

                std::cout << "allocated at LINE " << slow->m_index;
                std::cout << " \u27A4 BLOCK " << block_.m_index << " was substituted!\n";
            }

            friend std::ostream & operator<<( std::ostream &os_, const Cache &cache_ )
            {
                os_ << "=================================\n";
                os_ << "CACHE\n";
                os_ << "---------------------------------\n";
                os_ << "linha\tbloco\tend.\tcont.\n";
                os_ << "---------------------------------\n";
                for( auto line : cache_.m_lines )
                {
                    os_ << line;
                }
                os_ << "=================================\n";
                return os_;
            }
    };

#endif