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

def generador_primos():
    yield 2
    i=3
    while True:
       if es_primo(i):
           yield i
       i+=2

primos=None

def genera_primos(n):
    global primos
    primos=[0]
    degenere=generador_primos()
    for i in range(n):
        primos.append(next(degenere))
#    logger_cagada.debug("los primos son {}".format(primos))

def pce_core(numero):
    res=0
    global primos
    if not primos:
        genera_primos(int(1E4))
    res=primos[numero]
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
