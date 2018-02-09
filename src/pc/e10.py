#!/programas/python3.5/bin/python3
'''
Created on 08/10/2017
@author: ernesto
'''

import sys
import logging
from bisect import bisect_left
from functools import reduce
from operator import mul,truediv,mod
from math import gcd,pow

nivel_log = logging.ERROR
nivel_log = logging.DEBUG
logger_cagada = None


def es_primo(n):
    if n<2 or not (n&1):
        return False
    i=3
    while i*i<=n:
        if not(n%i):
            return False
        i+=1
    return True

primos=None
suma_primos=None

def genera_primos(n):
    global primos
    primos=[0]
    es_primo_arr=[True]*(n+1)
    for num in range(2,n+1):
        es_primo=es_primo_arr[num]
#        logger_cagada.debug("numeri {}".format(num))
        if es_primo:
            num_tmp=num<<1
            while num_tmp<=n:
 #               logger_cagada.debug("no s primo {}".format(num_tmp))
                es_primo_arr[num_tmp]=False
                num_tmp+=num
  #          logger_cagada.debug("anadido a primos {}".format(num))
            primos.append(num)
        
#    logger_cagada.debug("los primos son {}".format(primos))

def genera_suma_primos(n):
    global suma_primos
    suma_primos=[0]
    es_primo_arr=[True]*(n+1)
    for num in range(2,n+1):
        es_primo=es_primo_arr[num]
#        logger_cagada.debug("numeri {}".format(num))
        if es_primo:
            num_tmp=num<<1
            while num_tmp<=n:
 #               logger_cagada.debug("no s primo {}".format(num_tmp))
                es_primo_arr[num_tmp]=False
                num_tmp+=num
            suma_primos.append(num+suma_primos[-1])
  #          logger_cagada.debug("anadido a suma_primos {}".format(num))
#    logger_cagada.debug("los suma_primos son {}".format(suma_primos))
        

def pce_core(numero):
    res=0
    global primos
    if not primos:
        genera_primos(int(1E6))
        genera_suma_primos(int(1E6))
    i=bisect_left(primos,numero)
    if numero==primos[i]:
    	offset=0
    else:
    	offset=1
    res=suma_primos[max(i-offset,0)]
    return res

def pce_main():
    t = int(input().strip())
    for a0 in range(t):
        n = int(input().strip())
        ass=pce_core(n)
        print(ass)
#    for i in range(101102,1000000):
#        ass=pce_core(str(i))

if __name__ == "__main__":
    FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
    logging.basicConfig(level=nivel_log, format=FORMAT)
    logger_cagada = logging.getLogger("asa")
    logger_cagada.setLevel(nivel_log)
    pce_main()
