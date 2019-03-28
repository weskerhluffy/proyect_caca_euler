import logging


def calcula_ruta(m):
    r = []
    m_tam = len(m)
    for i in range(m_tam):
        r.append([0] * len(m[i]))
    r[-1] = m[-1]
#    logger.debug("r ini es {}".format(r))
    for i in range(m_tam - 2, -1, -1):
        for j in range(i + 1):
            logger.debug("en i {} j {}".format(i, j))
            r[i][j] = m[i][j] + max(r[i + 1][j], r[i + 1][j + 1])
#    logger.debug("r fini es {}".format(r))
    return r[0][0]

            
logging.basicConfig(format='%(asctime)s  %(levelname)-10s %(processName)s [%(filename)s:%(lineno)s - %(funcName)20s() ] %(name)s %(message)s')
logger = logging.getLogger('main')
logger.setLevel(logging.DEBUG)
logger.setLevel(logging.ERROR)
t = int(input())
for _ in range(t):
#    n = 104382426112
    n = int(input())
    m = []
    for _ in range(n):
        m.append([int(x) for x in input().strip().split(" ")])
#    logger.debug("m es {}".format(m))
    r = calcula_ruta(m)
    print(r)
