#!/bin/bash

file="main.cpp"
# for t in {0..9}

for t in 10   # 15 30             # 01 02 03 10 15 30  
do
  sed -e "10s/1/$t/g" -e "17,19s/001/0$t/g" $file  > 0$t.msd.cpp
  g++ -std=c++0x paras.cpp files.cpp 0$t.msd.cpp -o 0$t.msd      #for NJU
#  g++ -std=c++11 *.cpp -o $t.msd        #for Mac
  nohup ./0$t.msd > 0$t.output &
done 
