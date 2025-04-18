#!/bin/bash

run_test () {
    N="$1"

    valgrind --leak-check=full --log-file=valgrind_log ./../avm examples/$N.test 2> progerr_log 1> \
        progout_log 

#    if [[ !($? -eq 0) ]]; then
#        echo FAILED TO RUN VALGRIND 
#        exit $?
#    fi

    echo -n "$N "

    LEAK=$(grep "no leaks are possible" valgrind_log)

    if [[ !($? -eq 0) ]]; then
        echo FAILED TO RUN GREP
        exit $?
    fi

    cat progout_log >> progerr_log

    OUTPUT=$(diff progerr_log "examples/$N.answer")

    if [[ !($? -eq 0) ]]; then
        echo FAILED TO RUN DIFF 
        echo $OUTPUT
        exit $?
    fi

    if [[ -z "$LEAK" ]]; then
       echo LEAK KO 
       echo $LEAK
    else
        echo LEAK OK
    fi

    echo -n "$N "
    if [[ -z "$OUTPUT" ]]; then
        echo OK
    else
        echo KO
        echo $OUTPUT
    fi
}

run_test 00
run_test 01
run_test 02
run_test 03
run_test 04
run_test 05
run_test 06
run_test 07
run_test 08
run_test 09

rm progerr_log progout_log valgrind_log
