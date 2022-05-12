date >> time.txt

CORE1=("GemsFDTD_716B" "bwaves_1861B" "bzip2_281B" "cactusADM_1495B" "gcc_56B")
CORE2=("gobmk_135B" "lbm_1004B" "leslie3d_1186B" "milc_744B" "omnetpp_340B")


# for i in 0 4
# do
# 	./run_Universal.sh 2 100 ucp 50 ${CORE1[i]}.trace.xz ${CORE2[i]}.trace.xz 
# 	./run_Universal.sh 2 100 lru 50 ${CORE1[i]}.trace.xz ${CORE2[i]}.trace.xz 
#   sleep 1m

# done

# for i in 0 1 2 3 4 
# do
#   k=4-i;
# 	./run_Universal.sh 2 100 ucp 50 ${CORE1[i]}.trace.xz ${CORE2[k]}.trace.xz &
# 	./run_Universal.sh 2 100 lru 50 ${CORE1[i]}.trace.xz ${CORE2[k]}.trace.xz &
#   wait
#   sleep 2m

# done

# ./build_champsim.sh bimodal no no no no ucp 4 2>./Build.log &
# ./build_champsim.sh bimodal no no no no lru 4 2>./Build.log &
# wait
# ./run_4core.sh bimodal-no-no-no-no-ucp-4core 50 100 0 ${CORE1[0]}.trace.xz ${CORE2[3]}.trace.xz ${CORE1[1]}.trace.xz ${CORE2[4]}.trace.xz &
# ./run_4core.sh bimodal-no-no-no-no-lru-4core 50 100 0 ${CORE1[0]}.trace.xz ${CORE2[3]}.trace.xz ${CORE1[1]}.trace.xz ${CORE2[4]}.trace.xz &

# wait
# sleep 3m
# # 8 core
./build_champsim.sh bimodal no no no no ucp 8 2>./Build.log
./run_8core.sh bimodal-no-no-no-no-ucp-8core 50 100 0 ${CORE1[0]}.trace.xz ${CORE2[0]}.trace.xz ${CORE1[1]}.trace.xz ${CORE2[1]}.trace.xz ${CORE1[2]}.trace.xz ${CORE2[2]}.trace.xz ${CORE1[3]}.trace.xz ${CORE2[3]}.trace.xz 

# sleep 3m

# ./build_champsim.sh bimodal no no no no lru 8 2>./Build.log
# ./run_8core.sh bimodal-no-no-no-no-lru-8core 50 100 0 ${CORE1[0]}.trace.xz ${CORE2[0]}.trace.xz ${CORE1[1]}.trace.xz ${CORE2[1]}.trace.xz ${CORE1[2]}.trace.xz ${CORE2[2]}.trace.xz ${CORE1[3]}.trace.xz ${CORE2[3]}.trace.xz 

# date >> time.txt