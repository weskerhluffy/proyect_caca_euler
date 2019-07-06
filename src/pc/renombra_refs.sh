for log in $(ls *.c.log)
do
	prefijo=${log%.c.log}
	echo "prefixo $prefijo"
	mv $log $prefijo.ref.log
done
