#include<iostream>
#include<fstream>
#include<sstream>
#include<optional>
#include<vector>

#include "tokenization.hpp"
#include "Parser.hpp"
#include "generation.hpp"

int main(int argc , char* argv[]){
   
   if(argc != 2){
    std::cerr<<"Invalid Usage """<<std::endl;
    std::cerr<<"hydro <input.hy>"<<std::endl;
    return EXIT_FAILURE;
   }


    std::string contents;
    {
      std::stringstream contents_stream;
      std:: fstream input(argv[1] , std::ios::in);
      contents_stream << input.rdbuf();
      contents = contents_stream.str();

    }

       Tokenizer tokenizer(std::move(contents));
       std::vector<Token> tokens = tokenizer.tokenize();

       Parser parser(std::move(tokens));
       std::optional<NodeExit>  tree = parser.Parse();


       if(!tree.has_value()){
          std::cerr<<"No exit statement found!"<<std::endl;
          exit(EXIT_FAILURE);
       }

       Generator generator(tree.value());
       {
            std::fstream file("out.asm" , std::ios::out);
            file << generator.generate();
       }

      
      system("nasm -felf64 ./out.asm ");
      system("ld out.o -o out");


   //std::cout<<contents<<std::endl;
    //std::cout<<argv[0]<<std::endl;
   return EXIT_SUCCESS;
}