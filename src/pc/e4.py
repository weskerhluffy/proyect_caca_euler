#!/programas/python3.5/bin/python3
'''
Created on 08/10/2017
@author: ernesto
'''

import sys
import logging
from bisect import bisect_left

nivel_log = logging.ERROR
nivel_log = logging.DEBUG
logger_cagada = None

class numero_palote():
    def __init__(self,cadena_num):
        assert len(cadena_num)==6
        assert cadena_num[0]!='0'
        assert int(cadena_num.strip())>101101
        self.cadena_num=cadena_num.strip()
        self.circulos=[]
        self.digitos_palo=None
        self._inicializar()
        
    def _inicializar(self):
        self._init_circulos()
#        if not self.son_circulos_palo():
        self.previo_palo()
#        else:
#        self.digitos_palo=list(map(lambda circ:circ[0], self.circulos))

    def _init_circulos(self):
        cadena=list(map(int,self.cadena_num))
        cadena_cnt=len(cadena)
        offset_contraparte=cadena_cnt-1
        for i in range(cadena_cnt>>1):
            self.circulos.append([cadena[i], cadena[i+offset_contraparte]])
            offset_contraparte-=2

    def son_circulos_palo(self):
        es=True
        for circulo in self.circulos:
            if circulo[0]!=circulo[1]:
                es=False
                break
        return es

    def previo_palo(self):
        se_pudo=True
        circs=self.circulos
        if not self.son_circulos_palo():
            logger_cagada.debug("no era palo")
            circs_tam=len(circs)
            idx_circulo_modificado=-1

            for idx_circ in range(0,circs_tam):
                if circs[idx_circ][0]!=circs[idx_circ][1]:
                    idx_circulo_modificado = idx_circ
            
            if idx_circulo_modificado!=-1:
                assert circs[idx_circulo_modificado][0]!=circs[idx_circulo_modificado][1]
                if circs[idx_circulo_modificado][0]<circs[idx_circulo_modificado][1]:
                    circs[idx_circulo_modificado][1]=circs[idx_circulo_modificado][0]
                if circs[idx_circulo_modificado][0]>circs[idx_circulo_modificado][1]:
                    if not idx_circulo_modificado and circs[idx_circulo_modificado][0]==1:
                        idx_circulo_modificado+=1
                        while not circs[idx_circulo_modificado][0] and idx_circulo_modificado<circs_tam:
                            idx_circulo_modificado+=1
                    assert idx_circulo_modificado<circs_tam
                    assert idx_circulo_modificado or circs[idx_circulo_modificado][0]>1
                    circs[idx_circulo_modificado][0]-=1
                    circs[idx_circulo_modificado][1]=circs[idx_circulo_modificado][0]
                    for idx_circ in range(idx_circulo_modificado+1,circs_tam):
                        circs[idx_circ][1]=circs[idx_circ][0]=9
                for idx_circ in range(0,idx_circulo_modificado):
                    circs[idx_circ][1]=circs[idx_circ][0]

            assert self.son_circulos_palo()
            self.digitos_palo=list(map(lambda circ:circ[0], circs))
        else:
            logger_cagada.debug("s palo")
            digis=self.digitos_palo
            if not digis:
                digis=self.digitos_palo=list(map(lambda circ:circ[0], circs))
            for idx_digi in range(len(digis)-1,-1,-1):
                if not idx_digi and digis[idx_digi] ==1:
                    break
                if digis[idx_digi]:
                    digis[idx_digi]-=1
                    for i in range(idx_digi+1,len(digis)):
                        digis[i]=9
                    break
        logger_cagada.debug("el palo es {}".format(self.digitos_palo))

    @property
    def como_numero(self):
#        logger_cagada.debug("el palo cini es {}".format(self.digitos_palo))
        return int("".join(map(str,self.digitos_palo+self.digitos_palo[::-1])))

def pce_divisible_entre_centena(num_palo):
    for divi in range(100,1000):
        if not (num_palo.como_numero%divi):
            if 100<=(num_palo.como_numero/divi)<=999:
                return True
    return False

def checa_fuck(a):
    lim=len(a)>>1
    if not(len(a)&1):
        lim+=1
    offset=len(a)-1
#    print("chacando {}".format(a))
    for i in range(0,lim):
        if a[i]!=a[i+offset]:
#            print("no es en {}".format(i))
            return False
        offset-=2
    return True

mierda=[]
def genera_cagada():
    global mierda
    for x in range(100,1000):
        for y in range(x,1000):
            num=x*y
            digis=[int(i) for i in str(num)]
            if checa_fuck(digis) and len(digis)==6:
#                print("si es {}".format(num))
                mierda.append(num)
    mierda=list(sorted(list(set(mierda))))

def encuentra_caca(num):
    global mierda
    logger_cagada.debug("mierda es {}".format(len(mierda)))
    i=bisect_left(mierda,num-1)
    logger_cagada.debug("idx enc {}".format(min(len(mierda)-1,i+1)))
    logger_cagada.debug("el num es {}, a la izq {} a la der {} medias {}".format(num,mierda[max(i-1,0)],mierda[min(len(mierda)-1,i+1)],mierda[min(len(mierda)-1,i)]))
#    print("idx enx {}".format(i))
    mierda_enc=mierda[max(i,0)]
    return mierda_enc if mierda_enc==num-1 else mierda[max(i-1,0)]

def pce_core(numero):
    logger_cagada.debug("el num es {}".format(numero))
    if int(numero)>999999:
        numero="999999"
    caca=numero_palote(numero)
    logger_cagada.debug("wtf {}".format(caca.como_numero))
    while not pce_divisible_entre_centena(caca) and caca.como_numero>101101:
        logger_cagada.debug("m ieva {}".format(caca.como_numero))
        caca.previo_palo()
    logger_cagada.debug("la mieda es es {}".format(caca.como_numero))
    assert pce_divisible_entre_centena(caca)
    assert caca.como_numero==encuentra_caca(int(numero)), "lo q c tiene {} se enc {}".format(caca.como_numero,encuentra_caca(int(numero)))
    return caca.como_numero

def pce_main():
    t = int(input().strip())
    for a0 in range(t):
        n = input().strip()
#        ass=pce_core(n)
#        print(ass)
    for i in range(101102,1000000):
        ass=pce_core(str(i))

if __name__ == "__main__":
    FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
    logging.basicConfig(level=nivel_log, format=FORMAT)
    logger_cagada = logging.getLogger("asa")
    logger_cagada.setLevel(nivel_log)
    genera_cagada()
    pce_main()
