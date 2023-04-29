#! /bin/bash


#arguments pass to this bash script
#Use: on terminal type (for example) >> ./jcacheGet.sh shms 1791

#User input
spec=$1    #hms, shms or coin
run=$2


#for run in {1149..1171}
#do
    

#Use: on terminal type (for example) >> jcacheGet.sh shms 1791
#spec=$1 
#runNUM=$2

#for run in {1149..1171}
#do

#filename='DEUTERON_ANALYSIS/hcswif/runlists/d2_full.dat'


#for run in $(cat $filename) ; do    
#for run in {3368..3379} ; do    
echo ${run}
#mss="/mss/hallc/spring17/raw/${spec}_all_0${run}.dat"
#mss="/mss/hallc/c-polhe3/raw/${spec}_all_${run}.dat"                                
mss="/mss/hallc/c-cafe-2022/raw/${spec}_all_${run}.dat"
#mss="/mss/hallc/c-pionlt/raw/${spec}_all_${run}.dat" 
#mss="/mss/hallc/xem2/raw/${spec}_all_${run}.dat"

jcacheCMD="jcache get ${mss} -e cyero002@gmail.com -x"

echo "Executing command: ${jcacheCMD}" 
eval ${jcacheCMD}    

#done

  
