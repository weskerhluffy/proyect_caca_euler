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
from math import gcd

nivel_log = logging.ERROR
nivel_log = logging.DEBUG
logger_cagada = None


PRIMOS=[2,3,5,7,11,13,17,19,23,29,31,37]

def pce_encuentra_primo_hasta_n(n):
    global PRIMOS
    i=bisect_left(PRIMOS,n)
    mierda_enc=PRIMOS[max(i,0)]
    return PRIMOS[:i+1] if mierda_enc==n else PRIMOS[:i]
# XXX: https://stackoverflow.com/questions/3154454/what-is-the-most-efficient-way-to-calculate-the-least-common-multiple-of-two-int
def mcm(x,y):
    return x*y//gcd(x,y)

def pce_core(numero):
    logger_cagada.debug("el num es {}".format(numero))
#    primos=pce_encuentra_primo_hasta_n(numero)
#    logger_cagada.debug("los primos son {}".format(primos))
    mierda=reduce(mcm,range(1,numero+1))
    logger_cagada.debug("la mierda es {}".format(mierda))
    res=mierda

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
