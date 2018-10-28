#!/bin/bash
usage() {
    echo 'usage:
    ./logkernel.sh ./prog
outputfile: ./output.log'
}
recover() {
    # not started yet
    while [ `ps aux|grep -v grep|grep -wv logkernel|grep $1 -w|wc -l` -eq 0 ]; do
        :
    done
    # detect finish
    while [ `ps aux|grep -v grep|grep -wv logkernel -w|grep $1 -w|wc -l` -gt 0 ]; do
        :
    done
    cat /sys/kernel/debug/tracing/trace > output.log
    # Recover
    echo nop > /sys/kernel/debug/tracing/current_tracer
    echo > /sys/kernel/debug/tracing/set_ftrace_pid
    echo 0 > /sys/kernel/debug/tracing/max_graph_depth
    echo 1 > /sys/kernel/debug/tracing/options/funcgraph-irqs
}
[ "x$1" == "x-help" ] && usage && exit
[ "x$2" == "x-r" ] && recover $3 && exit
echo Must be root!
(`pwd`/logkernel.sh $1 -r $$ &)
echo 0 > /sys/kernel/debug/tracing/tracing_on
echo $$ > /sys/kernel/debug/tracing/set_ftrace_pid
echo 0 > /sys/kernel/debug/tracing/max_graph_depth
echo function_graph > /sys/kernel/debug/tracing/current_tracer
echo 0 > /sys/kernel/debug/tracing/options/funcgraph-irqs                                
echo 1 > /sys/kernel/debug/tracing/tracing_on
# Run task as current pid
exec $1
