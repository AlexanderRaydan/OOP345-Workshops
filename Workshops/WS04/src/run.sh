filename=$*

rm -f output

g++ -Wall -std=c++17 -g -o output $filename

./output Stations1.txt Stations2.txt CustomerOrders.txt AssemblyLine.txt
rm output