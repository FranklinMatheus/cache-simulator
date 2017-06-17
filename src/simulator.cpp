#include "simulator.hpp"

void execute_simulator( std::vector< int > &parameters )
{
    Memory mem( parameters[2], parameters[0] );
    Cache cache( parameters[1], parameters[0] );
    auto curr_clock(0);

    std::string input = "";
    int temp_address, temp_content;

    std::cout << "================================\n";
    std::cout << ">>>> CACHE SIMULATOR\n";
    std::cout <<"---------------------------\n";
    std::cout << "> Type `help` in case of doubts.\n";
    std::cout << "================================\n\n";

    while( input != "quit" )
    {
        std::cout << "\u27A4 ";
        std::cin >> input;
        
        if( input == "quit" ) continue;

        if( input == "help" )
        {
            std::cout <<"===========================\n";
            std::cout << ">>>> CACHE SIMULATOR\n";
            std::cout <<"---------------------------\n";
            std::cout << "> commands: \n";
            std::cout << "> read [address]\n";
            std::cout << "> write [address] [content]\n";
            std::cout << "> show\n";
            std::cout << "> quit\n";
            std::cout << "> details\n";
            std::cout << "> help\n";
            std::cout << "===========================\n\n";
            continue;
        }

        if( input != "read" and input != "write" and input != "show" and input != "details" )
        {
            std::cout << "\u274E COMMAND ERROR! Type `help` in case of doubts.\n";
            continue;
        }
        if( input != "show" and input != "details" ) std::cin >> temp_address;
        if( input == "write" ) std::cin >> temp_content;

        if( input == "show" )
        {
            std::cout << cache << "\n" << mem;
        }
        else if ( input == "read" )
        {
            curr_clock++;
            read( temp_address, cache, mem, parameters, curr_clock );
        }
        else if( input == "write" )
        {
            curr_clock++;
            write( temp_address, temp_content, cache, mem, parameters, curr_clock );
        } else 
        {
            show_details( parameters );
        }
    }
    std::cout << "EXITING THE SIMULATOR...\n";
}

void read( const int &address, Cache &cache, Memory &mem, std::vector< int > &parameters, const int &clock )
{
    if( address >= parameters[0]*parameters[2] or address < 0 )
    {
        std::cout << "[read " << address << "] MEMORY MISS!\n";
        std::cout << "\u274E This address IS NOT ALLOCATED at the memory!\n";
        return;
    }

    auto temp( parameters[3] );
    if( temp != 1 and temp != 2 and temp != 3 )
    {
        cache.mapping_invalid( parameters[3] );
    }

    if( cache.is_allocated( address, parameters ) )
    {
        std::cout << "[read " << address << "] CACHE HIT!\n";
    }
    else
    {
        std::cout << "[read " << address << "] CACHE MISS! ";
        cache.allocate( address, mem, clock, parameters );
    }
    cache.address_used( address, clock, parameters );
    std::cout << "\n";
}

void write( const int &address, const int &content, Cache &cache, Memory &mem, std::vector< int > &parameters, const int &clock )
{
    if( address >= parameters[0]*parameters[2] or address < 0 )
    {
        std::cout << "[read " << address << "] MEMORY MISS!\n";
        std::cout << "\u274E This address IS NOT ALLOCATED at the memory!\n";
        return;
    }

    if( parameters[6] != 1 )
    {
        cache.write_invalid( parameters[6] );
    }

    auto temp( parameters[3] );
    if( temp != 1 and temp != 2 and temp != 3 )
    {
        cache.mapping_invalid( parameters[3] );
    }

    if( address >= parameters[0]*parameters[2] or address < 0 )
    {
        std::cout << "[write " << address << "] MEMORY MISS!\n";
        std::cout << "\u274E This address IS NOT ALLOCATED at the memory!\n";
    }

    if( cache.is_allocated( address, parameters ) )
    {
        std::cout << "[write " << address << "] CACHE HIT!\n";
    }
    else
    {
        std::cout << "[write " << address << "] CACHE MISS! ";
        cache.allocate( address, mem, clock, parameters );
    }
    cache.write_content( address, content, mem, parameters );
    std::cout << "\n";
}

void show_details( const std::vector< int > &parameters )
{
    std::cout <<"\n===========================\n";
    std::cout << ">>>> DETAILS\n";
    std::cout <<"===========================\n";
    std::cout << "BLOCK LENGHT: \t" << parameters[0] << "\n";
    std::cout <<"---------------------------\n";
    std::cout << "CACHE LINES:  \t" << parameters[1] << "\n";
    std::cout <<"---------------------------\n";
    std::cout << "MEMORY BLOCKS:\t" << parameters[2] << "\n";
    std::cout <<"---------------------------\n";
    std::cout << "MAPPING:      \t";
    switch( parameters[3] )
    {
        case 1:
            std::cout << "(1) DIRECT MAPPING\n";
            break;
        
        case 2:
            std::cout << "(2) TOTALLY ASSOCIATIVE\n";
            break;
        
        case 3:
            std::cout << "(3) ASSOCIATIVE BY JOINT\n";
            break;
        default:
            std::cout << "(!) INVALID\n";
            break;
    }
    std::cout <<"---------------------------\n";
    std::cout << "SETS QUANTITY:\t" << parameters[4] << "\n";
    std::cout <<"---------------------------\n";
    std::cout << "SUBSTITUTION: \t";
    switch( parameters[5] )
    {
        case 1:
            std::cout << "(1) RANDOM\n";
            break;
        
        case 2:
            std::cout << "(2) FIFO\n";
            break;

        case 3:
            std::cout << "(3) LFU\n";
            break;

        case 4:
            std::cout << "(4) LRU\n";
            break;
        default:
            std::cout << "(!) INVALID\n";
            break;
    }
    std::cout <<"---------------------------\n";
    std::cout << "WRITE:       \t";
    switch( parameters[6] )
    {
        case 1:
            std::cout << "(1) WRITE-BACK\n";
            break;
        
        case 2:
            std::cout << "(2) WRITE-THROUGH\n";
            break;
        default:
            std::cout << "(!) INVALID\n";
            break;
    }
    std::cout <<"===========================\n";
}