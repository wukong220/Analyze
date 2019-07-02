#!/bin/bash
# for t in {0..9}

file="main.cpp"
#for t in 001 002 003 010 015 030  
#do
# sed -e "10s/1/$t/g" -e "17,19s/001/0$t/g" $file  > 0$t.msd.cpp
#  g++ -std=c++0x paras.cpp files.cpp 0$t.msd.cpp -o 0$t.msd      #for NJU
#  nohup ./0$t.msd > 0$t.output &
#done 

name="0.1_3.0"

g++ -std=c++0x paras.cpp files.cpp $file -o $name.msd
nohup ./$name.msd > $name.output &
#./$name.msd
