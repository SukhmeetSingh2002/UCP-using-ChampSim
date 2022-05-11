# taking input
NUM_CORE=${1?ERROR: Number of cpu not provided};
NUM_INS=${2:-10};
REP_POLICY=${3:-ucp};
NUM_WARM=${4:-1};
TRACE1=${5:-gcc_13B.trace.xz};
TRACE2=${6:-mcf_46B.trace.xz};

./build_champsim.sh bimodal no no no no $REP_POLICY $NUM_CORE 2> ./Build.log

retValue=$?;
if [ $retValue -eq 0 ]
then

    echo "------------------\nBuild done\n";
    echo "Cores: $NUM_CORE, Instructions: $NUM_INS, Warmup: $NUM_WARM\n";


    echo "Running your code...\n";
    ./run_2core.sh bimodal-no-no-no-no-${REP_POLICY}-2core $NUM_WARM $NUM_INS 0 $TRACE1 $TRACE2 

    retValue=$?;
    if [ $retValue -eq 0 ]
    then
        echo "Successfully run\n";
    fi

fi