filename=$*

rm -f output

g++ -Wall -std=c++17 -g -o output $filename

./output english_large.csv english_small.csv
rm output