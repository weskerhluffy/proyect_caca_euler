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

sumas_de_cuadrados=None

def pce_genera_sumas_de_cuadrados(n):
    global sumas_de_cuadrados
    sumas_de_cuadrados=[0]
    for i in range(1,n+1):
        sumas_de_cuadrados.append(sumas_de_cuadrados[i-1]+i*i)
#    logger_cagada.debug("sumas de cuadrados {}".format(sumas_de_cuadrados))
def pce_suma_consecutiva(n):
    return n*(n+1)>>1
def pce_suma_consecutiva_cuadrada(n):
    return int(pow(pce_suma_consecutiva(n),2))


def pce_core(numero):
    global sumas_de_cuadrados
    if not sumas_de_cuadrados:
        pce_genera_sumas_de_cuadrados(int(1E4))
    logger_cagada.debug("el num es {}".format(numero))
    mierda=abs(sumas_de_cuadrados[numero]-pce_suma_consecutiva_cuadrada(numero))
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
