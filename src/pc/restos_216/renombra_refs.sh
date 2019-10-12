#for log in $(ls *.c.log)
for log in $(ls in4[3-9]*c.log in5?.c.log)
do
	prefijo=${log%.c.log}
	echo "prefixo $prefijo"
	mv $log $prefijo.ref.log
done
