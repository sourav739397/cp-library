# write every function in single line
alias clr="printf '\33c'"
co() { g++ -std=c++23 -O2 -Wall -Wextra
 -Wshadow -Wconversion -fsanitize=address 
 -fsanitize=undefined -fsanitize=signed-integer-overflow 
 -D_GLIBCXX_DEBUG -o $1 $1.cpp; } 
run() { co $1 && ./$1; }