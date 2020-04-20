#Arnaldo Torres
#launch philosophers - a program that simulates a solution to the dining philosopher problem.  

EXEC = dining-p
SEATS = $1

#for every seat make a philopher
for (i =0; $i < $SEATS; i+=1)

do
    ./$EXEC $SEATS $i &
    echo "./$EXEC $SEATS $i"

done