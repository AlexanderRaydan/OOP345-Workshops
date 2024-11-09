filename=$*

rm -f output

g++ -Wall -std=c++17 -g -o output $filename

./output
rm output