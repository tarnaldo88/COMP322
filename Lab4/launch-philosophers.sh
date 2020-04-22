#Arnaldo Torres
#launch philosophers - a program that simulates a solution to the dining philosopher problem.  

EXEC=dining-p
SEATS=$1
child=$!
pids=()


sigHandler(){
	for((i=0; $i<$SEATS; i+=1))
	do
		kill -TERM ${pids[i]} 2>/dev/null #children are killed
	done
    	exit 0
}

trap 'sigHandler' TERM

#for every seat(n) create a philosopher
for ((i=0; $i<$SEATS; i+=1))
do

	./$EXEC $SEATS $i &

	pids[${i}]=$! #pid of children
done
wait
