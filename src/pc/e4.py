#!/programas/python3.5/bin/python3
'''
Created on 08/10/2017
@author: ernesto
'''

import sys
import logging

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
        self.previo_palo()

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
        if not self.son_circulos_palo():
            logger_cagada.debug("no era palo")
            circs=self.circulos
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
            digis=self.digitos_palo
            for idx_digi in range(len(digis)-1,-1,-1):
                if not idx_digi and digis[idx_digi] ==1:
                    break
                if digis[idx_digi]:
                    digis[idx_digi]-=1
                    break
        logger_cagada.debug("el palo es {}".format(self.digitos_palo))

def pce_core(numero):
    caca=numero_palote(numero)

def pce_main():
    t = int(input().strip())
    for a0 in range(t):
        n = input().strip()
        pce_core(n)

if __name__ == "__main__":
    FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
    logging.basicConfig(level=nivel_log, format=FORMAT)
    logger_cagada = logging.getLogger("asa")
    logger_cagada.setLevel(nivel_log)
    pce_main()
