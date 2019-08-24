'''
Created on 6 jul 2019

@author: ernestoalvarado
'''
import random
from math import gcd,sqrt
# XXX: https://djangocentral.com/python-program-to-check-if-a-number-is-perfect-square/
def square(n):
	return int(sqrt(n) + 0.5) ** 2 == n
if __name__ == '__main__':
	i=0
	N=10
	q=10
	s=45
	maxn=int(1E7)
	while i<N:
		# XXX: https://stackoverflow.com/questions/3996904/generate-random-integers-between-0-and-9
		a=random.randint(1,2)
		b=random.randint(-100,100)
		c=random.randint(-10000000,10000000)
		d=b*b-4*a*c
		if gcd(gcd(a,b),c)==1 and (d<1 or not square(d)):
			f=open("in{}.txt".format(s+i),'w')
			f.write("{} {} {}".format(a,b,c))
			f.write("{}\n".format(q))
			for n in range(maxn,maxn-(q>>1),-1):
				f.write("{}\n".format(n))
			for n in range(0,(q>>1)):
				f.write("{}\n".format(n))
			f.close()
			i+=1
