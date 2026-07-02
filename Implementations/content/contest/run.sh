set -e

# optional color
C='\033[0;31m'
R='\033[0m'

g++ -std=c++23 -O2 -Wall -Wextra -Wshadow -Wconversion \
-fsanitize=address -fsanitize=undefined \
-fsanitize=signed-integer-overflow -o $1 $1.cpp;

./$1 < input.txt 2> error.txt 

echo -e "${C}$(cat error.txt)${R}"