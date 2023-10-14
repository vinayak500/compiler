#pragma once

#include "Parser.hpp"

class Generator{


public:
inline explicit Generator(NodeExit root)
: m_root(std::move(root))
{

}


    std::string generate()
    {
       std::stringstream output;
       output<<"global_start\n";
       output<<"_start:\n";

       output <<"    mov rax,60\n";
       output<<"    mov rdi," + m_root.expr.int_lit.value.value() + "\n";
       output<<"    syscall\n";
       return output.str(); 
    }

private:
   const NodeExit m_root;


};