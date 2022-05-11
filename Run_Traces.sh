CORE1=("GemsFDTD_716B" "bwaves_1861B" "bzip2_281B" "cactusADM_1495B" "gcc_56B")
CORE2=("gobmk_135B" "lbm_1004B" "leslie3d_1186B" "milc_744B" "omnetpp_340B")


for i in 0 1 2 3 4 
do
	./run_Universal.sh 2 100 ucp 50 ${CORE1[i]}.trace.xz ${CORE2[i]}.trace.xz &
  if [ $i -eq 1 ]; then
  wait
  sleep 3m
  fi
  if [ $i -eq 3 ]; then
  wait
  sleep 3m
  fi
done

for i in 0 1 2 3 4 
do
  k=4-i;
	./run_Universal.sh 2 100 ucp 50 ${CORE1[i]}.trace.xz ${CORE2[k]}.trace.xz &
  if [ $i -eq 0 ]; then
  wait
  sleep 3m
  fi
  if [ $i -eq 2 ]; then
  wait
  sleep 3m
  fi
done