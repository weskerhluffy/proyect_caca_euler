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
#nivel_log = logging.DEBUG
logger_cagada = None

def calc_b(a,N):
    return N*(N-2*a)/(2*(N-a))

def pce_core(N):
    res=-1
    for a in range(N-1,0,-1):
#        logger_cagada.debug("chale {}".format(a))
        b=calc_b(a,N)
        if b.is_integer() and b>a:
#            logger_cagada.debug("q caraxo {}".format(b))
            c=N-a-b
            res=int(a*b*c)
            break

    return res

def pce_main():
    t = int(input().strip())
    for a0 in range(t):
        n = int(input().strip())
        caca=pce_core(n)
#        print("{}".format(caca))


if __name__ == "__main__":
    FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
    logging.basicConfig(level=nivel_log, format=FORMAT)
    logger_cagada = logging.getLogger("asa")
    logger_cagada.setLevel(nivel_log)
    pce_main()
