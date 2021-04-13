#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"

int main(int argc, char **argv)
{
    std::string file_name;

    
    if (argc > 2)
    {
        std::cout << "Too many arguments given" << std::endl;
        exit(EXIT_FAILURE);
    }
    else

        
        if (argc == 2)
    {
        file_name = argv[1];
        file_name += ".s21";

        std::ofstream output_file;
        output_file.open(file_name, std::ios_base::app);
        output_file << " ";
        in_file.open(file_name);
    }

    
    else if (argc == 1)
    {
        std::string input;
        std::ofstream temp_file;
        file_name = "stdin.temp";

        temp_file.open(file_name, std::ios::trunc);

        do
        {
            
            getline(std::cin, input);
            temp_file << input << "\n";
            
        } while (!input.empty());

        temp_file.close(); 
        in_file.open(file_name);
    }

    
    if (in_file)
    {
        Node *root = parser(); 
        printTree(root);     
    }
    else
    { 
        std::cout << "--ERROR-- Cannot open " << file_name << " for reading file" << std::endl;

        exit(EXIT_FAILURE);
    }
    in_file.close();
    return 0;
}