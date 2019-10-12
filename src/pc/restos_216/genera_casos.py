'''
Created on 6 jul 2019

@author: ernestoalvarado
'''

if __name__ == '__main__':
    maxn=int(1E7)
    q=int(1E1)
    i=21
    for a in [1,2]:
        for b in [-100,0,100]:
            for c in [-maxn,0,maxn]:
                l="{} {} {}\n".format(a,b,c)
                f=open("in{}.txt".format(i),'w')
                f.write(l)
                f.write("{}\n".format(q))
                for n in range(maxn,maxn-(q>>1),-1):
                    f.write("{}\n".format(n))
                for n in range(0,(q>>1)):
                    f.write("{}\n".format(n))
                f.close()
                i+=1