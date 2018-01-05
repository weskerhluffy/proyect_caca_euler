#!/bin/python3

import sys

# XXX: https://www.w3resource.com/euler-project/euler-problem3.php
def caca(n):
    i = 3  
    while not(n&1) and n:
        n>>=1
        ##logger_cagada.debug("shit n es {}".format(n))
    if (n==1):
        return 2

    mierda=0
    while i * i <= n:  
        while not(n% i):  
            mierda=n
            n= n// i  
        if(n==1):
            n=mierda
            break
        i = i + 1  
    return n

t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    print(caca(n))
