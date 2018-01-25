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


def num_a_arr(n):
    return list(map(int,str(n)))

def mult_arr(arr):
    return reduce(mul,arr)

def pce_core(n,k):
    res=0
    num_arr=num_a_arr(n)
    num_arr_tam=len(num_arr)
    res=reduce(lambda mini,i:max(mini,mult_arr(num_arr[i:i+k])),range(num_arr_tam-k+1),0)
        
    return res

def pce_main():
    t = int(input().strip())
    for a0 in range(t):
        n,k = input().strip().split(' ')
        n,k = [int(n),int(k)]
        num = input().strip()
        caca=pce_core(num,k)
        print("{}".format(caca))


if __name__ == "__main__":
    FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
    logging.basicConfig(level=nivel_log, format=FORMAT)
    logger_cagada = logging.getLogger("asa")
    logger_cagada.setLevel(nivel_log)
    pce_main()
