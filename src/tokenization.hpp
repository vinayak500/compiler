#pragma once

#include<optional>
#include<vector>
#include<string>

enum class TokenType{
    exit ,
    int_lit,
    semi
};

struct Token{
    TokenType type;
    std::optional<std::string> value{}; 
};



class Tokenizer{

public:    
   inline explicit Tokenizer(std::string src)
   : m_src(std::move(src))
   {

   }

   
   inline std::vector<Token> tokenize(){
          std::string buf;
          std::vector<Token> tokens;
          while(peak().has_value()){
            if(std::isalpha(peak().value())){
              buf.push_back(consume());

              while(peak().has_value() && std::isalnum(peak().value())){
                buf.push_back(consume());
              }

              if(buf == "exit"){
                 tokens.push_back({.type= TokenType::exit});
                        buf.clear();
                        continue;
              }else{
                    std::cerr<<"You messed up !" <<std::endl;
                        exit(EXIT_FAILURE);
              }
          } 
          else if (std::isdigit(peak().value())){
                   buf.push_back(consume());

                    while(peak().has_value() && std::isdigit(peak().value())){
                buf.push_back(consume());
              }

                tokens.push_back({.type= TokenType::int_lit , .value = buf});
                buf.clear();
                continue;

          } else if(std::isspace(peak().value())){
            consume();
            continue;
          }else if(peak().value() == ';'){
            tokens.push_back({.type= TokenType::semi});
            consume();
            continue;
          }else{
              std::cerr<<"you messed up!"<<std::endl;
                exit(EXIT_FAILURE);
          }
     }
     m_index = 0;  
        return tokens;
   } 

      

private:

   std::optional<char> peak(int ahead=1)
   {
     if(m_index + ahead > m_src.length()){
       return {};
     }else{
        return m_src.at(m_index);
     }
   }

     char consume()
     {
       return m_src.at(m_index++);
     }

   const std::string m_src;
    int m_index=0;


};