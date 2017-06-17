#include "simulator.hpp"
#include <iostream>
#include <fstream>

int main( int argc, char *argv[] )
{
    std::vector< int > parametros;

    if( argc <= 1 )
    {
        std::cout << ">>>> You SHOULD PASS a file as argument!\n";
        return EXIT_FAILURE;
    }
    else
    {
        std::string filename = argv[1];
        std::ifstream file( filename );

        if( !file.is_open() )
        {
            std::cout << ">>>> ERROR opening the file: " << filename << " !\n";
            return EXIT_FAILURE;
        }
        else
        {
            int temp;
            std::cout << ">>>> READING the parameters...\n";
            for( auto i( 0 ); i < 7; ++i ) // lê os 7 parametros.
            {
                if( file >> temp )
                {
                    parametros.push_back( temp );
                    std::cout << "[OK]\n";
                }
                else
                {
                    std::cout << "> [FAIL]\n";
                    std::cout << "> Was found only " << i << " parameters of 7!\n";
                    return EXIT_FAILURE;
                }
            }
            std::cout << "SUCCESS reading the parameters!!\n\n";
        }
    }

    execute_simulator( parametros );

    return EXIT_SUCCESS;
}