#!/bin/bash

file="main.cpp"
Usage="/////////// Usage: ./msd.sh  Phi  D  ///////////"
# for t in {0..9}


if [ -n "$1" ] && [ -n "$2" ]; then
    echo "///// Phi = $1 ---- D = $2 /////"
else 
   echo "///// ${Usage} /////" 
   exit 1
fi 

dir=$(cd `dirname $0`;pwd)

for Phi in $1             #0.10 0.40 0.45 
do 
 for S in 2.0 2.0 2.5 3.0    #2.0 2.5 3.0           # 2.0 3.0 4.0 5.0 #4.0
 do 
  for D in $2                                      #R in 1.0 
  do 
    #D=$(echo "$R * 2.0" | bc)
   for Fa in 10.0    #15.0
   do
    for Kb in 0.0
    do 
      for t in 001   # 15 30             # 01 02 03 10 15 30  
      do 
       title="${Phi}Phi_${S}S_${D}D"
       dir1="${Kb}Kb_${Fa}Fa"
       echo "--------------- ${title} ------------------"
       sed  "35s/0.10/${Phi}/;36s/2.0/${S}/;37s/2.0/${D}/;" $file  > msd.$t.cpp
       #sed -e "10s/1/$t/g" -e "17,19s/001/0$t/g" $file  > 0$t.msd.cpp
       g++ -std=c++0x paras.cpp files.cpp msd.$t.cpp -o msd.$t      #for NJU
#  g++ -std=c++11 *.cpp -o $t.msd        #for Mac
       echo "-------------- g++ -std=c++0x paras.cpp files.cpp msd.$t.cpp -o msd.$t ----------------------"
       mv msd.$t ${title}/${dir1}/ && mv msd.$t.cpp ${title}/${dir1}/
       cd ${title}/${dir1}/
       #nohup ./msd.$t > msd.$t.output &
       #echo "nohup ./msd.$t > msd.$t.output &"
       echo "------------ bsub -q serial -J msd.$t -n 1 -o msd.$t.output -e msd.$t.err ./msd.$t ------------------"
       bsub -q serial -J msd.$t -n 1 -o msd.$t.output -e msd.$t.err ./msd.$t 
       cd ../../
     done
     done 
    done 
   done 
 done 
done
bjobs
echo "${Usage}"
