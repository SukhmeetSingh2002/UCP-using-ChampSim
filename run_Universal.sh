# taking input
NUM_CORE=${1?ERROR: Number of cpu not provided};
NUM_INS=${2:-10};
NUM_WARM=${3:-1};

./build_champsim.sh bimodal no no no no lru $NUM_CORE 2> ./Build.log

retValue=$?;
if [ $retValue -eq 0 ]
then

    echo "------------------\nBuild done\n";
    echo "Cores: $NUM_CORE, Instructions: $NUM_INS, Warmup: $NUM_WARM\n";


    echo "Running your code...\n";
    ./run_2core.sh bimodal-no-no-no-no-lru-2core $NUM_WARM $NUM_INS 0 gcc_13B.trace.xz gcc_13B.trace.xz

    retValue=$?;
    if [ $retValue -eq 0 ]
    then
        echo "Successfully run\n";
    fi

fi