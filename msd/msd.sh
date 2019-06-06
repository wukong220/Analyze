#!/bin/bash

# for t in {0..9}

for t in 001 002 003 010 015 030  
do
  sed "10,19s/001/$t/g" main.cpp  > $t.msd.cpp
  g++ -std=c++0x paras.cpp files.cpp $t.msd.cpp -o $t.msd      #for NJU
#  g++ -std=c++11 *.cpp -o $t.msd        #for Mac
  nohup ./$t.msd > $t.output &
done 
