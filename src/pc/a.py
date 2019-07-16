i=0
while i < 18446744073709551615:
	if(i**i>18446744073709551615):
		print("limite i {} {}".format(i,i**i))
		break
	i+=1
