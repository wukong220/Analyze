#!/bin/bash

# for t in {0..9}

for t in 002    #001 002 003 005 010 015 030  
do
  sed "10,19s/001/$t/g" msd.cpp 
  g++ -std=c++0x *.cpp -o $t.msd      #for NJU
#  g++ -std=c++11 *.cpp -o $t.msd        #for Mac
  nohup ./$t.msd > $t.output &
done 
