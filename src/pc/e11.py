#!/programas/python3.5/bin/python3
'''
Created on 08/10/2017
@author: ernesto
'''

import sys
import logging
from bisect import bisect_left
from functools import reduce,partial
from operator import mul,truediv,mod
from math import gcd,pow

nivel_log = logging.ERROR
nivel_log = logging.DEBUG
logger_cagada = None


def caca_comun_imprime_matrix(matrix):
    return "\n".join(map(str,matrix))

def posicion_suma(pos_1, pos_2):
    return [pos_1[0] + pos_2[0], pos_1[1] + pos_2[1]]

def caca_comun_valor_en_posicion(matrix,pos):
    logger_cagada.debug("sacando mierda {}".format(pos))
    return matrix[pos[0]][pos[1]]

PV=1
PH=2
PDI=3
PDD=4
def pce_mult(matrix,pos,direccion):
    assert 1<=direccion<=4
    movs=None
    if direccion==PV:
        movs=map(lambda x:(x,0),range(4))
    if direccion==PH:
        movs=map(lambda y:(0,y),range(4))
    if direccion==PDD:
        movs=map(lambda d:(d,d),range(4))
    if direccion==PDI:
        movs=map(lambda d:(d,-d),range(4))
    
    posis=map(partial(posicion_suma,pos),movs)
    
    caca=reduce(mul,map(lambda pos:caca_comun_valor_en_posicion(matrix,pos),posis))
    logger_cagada.debug("d las pos {} dir {} el res es {}".format(list(posis),direccion,caca))
    return caca

def pce_core(matrix):
    maxi=0
    for i in range(0,20):
        for j in range(3,23):
            maxi_tmp=max(map(partial(pce_mult,matrix,(i,j)),[PV,PH,PDI,PDD]))
            if maxi_tmp>maxi:
                maxi=maxi_tmp
    return maxi

def pce_main():
  grid = []

  for grid_i in range(20):
     grid_t = [0]*3+[int(grid_temp) for grid_temp in input().strip().split(' ')]+[0]*3
     grid.append(grid_t)

  for _ in range(3):
     grid.append([0]*26)
#  logger_cagada.debug("mallaton\n{}".format(caca_comun_imprime_matrix(grid)))
  res=pce_core(grid)
  print("{}".format(res))


if __name__ == "__main__":
    FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
    logging.basicConfig(level=nivel_log, format=FORMAT)
    logger_cagada = logging.getLogger("asa")
    logger_cagada.setLevel(nivel_log)
    pce_main()
