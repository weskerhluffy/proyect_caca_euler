import logging


# XXX: https://euler.stephan-brumme.com/17/

def unidades(n):
    assert 0 <= n < 10
    cads = ["Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"]
    return cads[n]


def decenas(n, u):
    assert 0 <= n < 10
    no = n
    cads = {2:"Twenty", 3:"Thirty", 4:"Forty", 5:"Fifty", 6:"Sixty", 7:"Seventy", 8:"Eighty", 9:"Ninety"}
    r = ""
    if n < 2:
        if n:
            cadsu = {"Zero":"Ten", "One":"Eleven", "Two":"Twelve", "Three":"Thirteen", "Four":"Fourteen", "Five":"Fifteen", "Six":"Sixteen", "Seven":"Seventeen", "Eight":"Eighteen", "Nine":"Nineteen"}   
#            logger.debug("cads {}".format(cadsu))
            r = cadsu[u]
        else:
            r = u
    else:
        if u == "Zero":
            r = cads[n]
        else:
            r = "{} {}".format(cads[n], u)
    logger.debug("n {} nombre {}".format(no, r))
    return r


def centenas(n, d):
    assert 0 <= n < 10
    r = ""
    no = n
    if n:
        if d == "Zero":
            r = "{} Hundred".format(unidades(n))
        else:
            r = "{} Hundred {}".format(unidades(n), d)
    else:
        r = d
    logger.debug("n {} d {} nombre {}".format(no, d, r))
    return r


def grupo_unidades(n):
    r = ""
    i = 0
    no = n
    logger.debug("n es {}".format(n))
    assert (0 <= n < 1000)
    while n:
        d = n % 10
        logger.debug("d es {}".format(d))
        if not i:
            r = unidades(d)
        if i == 1:
            r = decenas(d, r)
        if i == 2:
            r = centenas(d, r)
        n //= 10
        i += 1
    logger.debug("n {} nombre {}".format(no, r))
    return r

    
def numero_a_nombre(n):
    i = 0
    grupos = ["", " Thousand", " Million", " Billion", " Thrillion"]
    r = []
    while n:
        d = n % 1000
        logger.debug("d es {}".format(d))
        if d:
            r.append("{}{}".format(grupo_unidades(d), grupos[i]))
        logger.debug("i {} d {} n {} r {}".format(i, d, n, r))
        n //= 1000
        i += 1
    ret = " ".join(reversed(r))
    if not ret:
        ret = "Zero"
    return ret


logging.basicConfig(format='%(asctime)s  %(levelname)-10s %(processName)s [%(filename)s:%(lineno)s - %(funcName)20s() ] %(name)s %(message)s')
logger = logging.getLogger('main')
logger.setLevel(logging.DEBUG)
logger.setLevel(logging.ERROR)
t = int(input())
for _ in range(t):
#    n = 104382426112
    n = int(input())
    logger.debug("n es {}".format(n))
    r = numero_a_nombre(n)
    logger.debug("el nombre {}".format(r))
    print(r)
