'''
Created on 28 abr 2019

@author: 
'''
# XXX: https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
# XXX: http://technojeeves.com/index.php/20-zellers-congruence
import logging


def normalizar_ano_mes(ano, mes):
    if mes < 3:
        mes += 12
        ano -= 1
    return ano, mes


def calcula_domingos(ano_inicial, mes_inicial, dia_inicial, ano_final, mes_final, dia_final):
    logger.debug("ano inicial {}-{}-{} ano final {}-{}-{}".format(ano_inicial, mes_inicial, dia_inicial, ano_final, mes_final, dia_final))
    if dia_inicial != 1:
        mes_inicial += 1
        if mes_inicial > 12:
            mes_inicial = 1
            ano_inicial += 1
    ano_inicial, mes_inicial = normalizar_ano_mes(ano_inicial, mes_inicial)
    siglo_inicial = ano_inicial // 100
    logger.debug("ano final {}-{}".format(ano_final, mes_final))
    ano_final, mes_final = normalizar_ano_mes(ano_final, mes_final)
    logger.debug("ano final des {}-{}".format(ano_final, mes_final))
    siglo_final = ano_final // 100
    logger.debug("siglo {}:{}".format(siglo_inicial, siglo_final))
    r = 0
    for siglo in range(siglo_inicial, siglo_final + 1):
        k_inicial = 0
        if siglo == siglo_inicial:
            k_inicial = ano_inicial % 100
        k_final = 99
        if siglo == siglo_final:
            k_final = ano_final % 100
        clase_esperada = (1 - 1 - siglo // 4 + 2 * siglo) % 7
        logger.debug("siglo {} k {}:{} clase mod 7 {}".format(siglo, k_inicial, k_final, clase_esperada))
        for k in range(k_inicial, k_final + 1):
            m_inicial = 3
            if siglo == siglo_inicial and k == k_inicial:
                m_inicial = mes_inicial
            m_final = 14
            if siglo == siglo_final and k == k_final:
                m_final = mes_final
            logger.debug("siglo {} k {} m {}:{}".format(siglo, k, m_inicial, m_final))
            for m in range(m_inicial, m_final + 1):
                clase = ((13 * (m + 1) // 5) + k + k // 4) % 7
                logger.debug("m {} clase {} clase esp {}".format(m, clase, clase_esperada))
                if clase == clase_esperada:
                    r += 1
                
    return r

            
logging.basicConfig(format='%(asctime)s  %(levelname)-10s %(processName)s [%(filename)s:%(lineno)s - %(funcName)20s() ] %(name)s %(message)s')
logger = logging.getLogger('main')
logger.setLevel(logging.DEBUG)
# logger.setLevel(logging.ERROR)
t = int(input())
for _ in range(t):
    ano_inicial, mes_inicial, dia_inicial = [int(x) for x in input().strip().split(" ")]
    ano_final, mes_final, dia_final = [int(x) for x in input().strip().split(" ")]
    r = calcula_domingos(ano_inicial, mes_inicial, dia_inicial, ano_final, mes_final, dia_final)
    logger.debug("res {}".format(r))
    print(r)
