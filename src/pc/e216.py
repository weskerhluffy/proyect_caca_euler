#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3
from array import array
from math import exp, log, ceil
import logging
from sys import maxsize
import os
#from eulerlib.prime_numbers import is_prime
#from sympy.ntheory import legendre_symbol, is_quad_residue, quadratic_residues
#from gmpy2 import divm, invert, is_prime


# XXX: https://www.johndcook.com/blog/2008/12/10/solving-linear-congruences/
# XXX: http://wrean.ca/cazelais/linear_congruence.pdf
# XXX: https://stackoverflow.com/questions/16044553/solving-a-modular-equation-python
def iterative_egcd(a, b):
	x, y, u, v = 0, 1, 1, 0
	while a != 0:
		q, r = b // a, b % a
		m, n = x - u * q, y - v * q  # use x//y for floor "floor division"
		b, a, x, y, u, v = a, r, u, v, m, n
	return b, x, y


def modinv(a, m):
	g, x, _ = iterative_egcd(a, m) 
	if g != 1:
		return None
	else:
		return x % m


class QuadraticSieve():

	def __init__(self, max_numero):
		self.max_numero = max_numero
		self.primos = array('I')
		self._inicializa_criba()

	def _inicializa_criba(self):
		# XXX: https://stackoverflow.com/questions/521674/initializing-a-list-to-a-known-number-of-elements-in-python
		bandera_primos = array('B', (1,) * (self.max_numero + 1))
		for i in range(2, self.max_numero + 1):
			if bandera_primos[i]:
				self.primos.append(i)
			
			for primo in self.primos:
				compuesto = primo * i
				if compuesto > self.max_numero:
					break
				bandera_primos[compuesto] = 0
				if not (i % primo):
					break
				
	def simbolo_legendre(self, a, p):
		s = (a ** ((p - 1) >> 1)) % p
		return s

	# XXX: https://www.johndcook.com/blog/2019/02/12/computing-jacobi-symbols/
	def simbolo_jacobi(self, a, n):
		logger.debug("a {} n {}".format(a, n))
		assert(n % 2 == 1)
		t = 1
		if a < 0 or a > n:
			a = a % n
			if a < 0:
				a = -a
				if n % 4 == 3:
					t = -t
			
		while a != 0:
			while a % 2 == 0:
				a /= 2
				r = n % 8
				if r == 3 or r == 5:
					t = -t
			a, n = n, a
			if a % 4 == n % 4 == 3:
				t = -t
			a %= n
		if n == 1:
			return t
		else:
			return 0
	
	def _encuentra_base_de_factores(self, n, b):
		rc = array("I")
		for p in self.primos:
			if p > b:
				break
			if self.simbolo_legendre(n, p) == 1:
				rc.append(p)
		return rc
	
	def _calcula_limite_b_suave(self, n):
		b = ceil(exp(((log(n) * log(log(n))) / 2) / 2))
		return int(b)
	
	# XXX: https://rosettacode.org/wiki/Tonelli-Shanks_algorithm#Python
	def _calcula_z_shanks_tonelli(self, p):
		for z in range(2, p):
			if p - 1 == self.simbolo_legendre(z, p):
				break
		return z

	def calcula_conguencia_residuo_cuadratico(self, n, p):
		logger.debug("calculando n {} p {}".format(n, p))
		p_menos_1 = p - 1
		S = 0
		while not (p_menos_1 & 1):
			p_menos_1 >>= 1
			S += 1
		logger.debug("S {} Q {}".format(S, p_menos_1))
		Z = self._calcula_z_shanks_tonelli(p)
		logger.debug("Z {}".format(Z))
		Q = p_menos_1
		c = (Z ** Q) % p
		R = (n ** ((Q + 1) >> 1)) % p
		t = (n ** Q) % p
		M = S
		logger.debug("t {} R {}".format(t,R))
		while (t % p) != 1:
			i = 0
			logger.debug("M {}".format(M))
			for i in range(1, M):
# 				logger.debug("t mod {}".format((t ** (i << 1)) % p))
# 				if ((t ** (i << 1)) % p) == 1:
				if ((t ** (2 ** i)) % p) == 1:
					break
			b = (c ** (1 << (M - i - 1))) % p
			logger.debug("b {} R {} t {} c {} M {} i {}".format(b, R, t, c, M, i))
			R = (R * b) % p
			# XXX: https://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python
			t = (t * (b ** 2)) % p
			c = (b ** 2) % p
			M = i
		return R, p - R


def _try_composite(a, d, n, s):
	if pow(a, d, n) == 1:
		return False
	for i in range(s):
		if pow(a, 2 ** i * d, n) == n - 1:
			return False
	return True  # n  is definitely composite


def es_primo(n, _precision_for_huge_n=16):
	_known_primes = [2, 3]
# 	logger.debug("checando primalidad {}".format(n))
# 	logger.debug("checando primalidad a {}".format(any((not (n % p)) and n != p for p in _known_primes)))
	if any((not (n % p)) and n != p for p in _known_primes) or n in (0, 1):
# 		logger.debug("no primoo {} {} {}".format(n, any((not (n % p)) and n != p for p in _known_primes), n in (0, 1)))
# 		logger.debug("no pprimo {}".format(n))
		return False
	if n in _known_primes:
		return True
	d, s = n - 1, 0
	while not d % 2:
		d, s = d >> 1, s + 1
	# Returns exact according to http://primes.utm.edu/prove/prove2_3.html
	if n < 1373653: 
		return not any(_try_composite(a, d, n, s) for a in (2, 3))
	if n < 25326001: 
		return not any(_try_composite(a, d, n, s) for a in (2, 3, 5))
	if n < 118670087467: 
		if n == 3215031751: 
			return False
		return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7))
	if n < 2152302898747: 
		return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11))
	if n < 3474749660383: 
		return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13))
	if n < 341550071728321: 
		return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17))
	# otherwise
	return not any(_try_composite(a, d, n, s) 
				   for a in _known_primes[:_precision_for_huge_n])

			
logging.basicConfig(format='%(asctime)s  %(levelname)-10s %(processName)s [%(filename)s:%(lineno)s - %(funcName)20s() ] %(name)s %(message)s')
logger = logging.getLogger('main')
logger.setLevel(logging.DEBUG)
#logger.setLevel(logging.INFO)
logger.setLevel(logging.ERROR)

MAX_PRIMOS = int(1E6)
MAX_ABCISA = int(1E6)

if "STDIN" in os.environ:
	f = open(os.environ["STDIN"], "r")
	input_fn=f.readline
else:
	input_fn=input
a, b, c = [int(x) for x in input_fn().strip().split(" ")]
logger.debug("a {} b {} c {}".format(a, b, c))
q = int(input_fn())
f = lambda x:a * x * x + b * x + c
abcisas_set = set()
abcisas_primos_array = array("B")
ordenadas_array = array("Q")
abcisas_suma_primos_acumulada = array("I")

Ns = []
while q:
	N = int(input_fn())
	Ns.append(N)
# 	logger.info("res {}".format(abcisas_suma_primos_acumulada[N]))
	q -= 1

maxn = max(Ns)
qs = QuadraticSieve(maxn)

for xi in range(maxn + 1):
	y = f(xi)
	primo = None
	if y > 0:
		abcisas_set.add(xi)
		primo = True
	else:
		y = maxsize
		primo = False
	ordenadas_array.append(y)
	abcisas_primos_array.append(primo)
	abcisas_suma_primos_acumulada.append(0)

discriminante = b * b - 4 * a * c
logger.info("discriminante {}".format(discriminante))

for p in qs.primos:
	x = []
	# XXX: https://math.stackexchange.com/questions/551700/when-is-the-quadratic-congruence-ax2-bx-c-equiv-0-pmod-p-solvable
	# XXX: https://rkm0959.tistory.com/20
	# XXX: http://pipilupe.blogspot.com/2013/06/project-euler-problem-216.html
	logger.info("p es {}".format(p))
	if p == 2:
		for xi in range(0, 2):
			yi = f(xi)
			if not (yi & 1):
				x.append(xi)
	else:
		ls = qs.simbolo_jacobi(discriminante, p)
#		assert ls == legendre_symbol(discriminante, p), "legendre symbol de {}:{} es incorrecto obtenido {} esperado {}".format(discriminante, p, ls, legendre_symbol(discriminante, p))
		logger.debug("legendre {}".format(ls))
		y = []
		if ls == -1:
			continue
# 		assert is_quad_residue(discriminante, p) 
		if not discriminante or not ls:
				y.append(0)
		else:
# 			assert ls == 1
			y1, y2 = qs.calcula_conguencia_residuo_cuadratico(discriminante, p)
			y.extend([y1, y2])
			logger.debug("ys {}".format(y))
		
		# XXX: https://stackoverflow.com/questions/4798654/modular-multiplicative-inverse-function-in-python
		for yi in y:
# 			assert ((yi * yi) % p) == discriminante % p, "fallo sol y {} disc {} p {}".format(yi, discriminante, p)
			xi = modinv(a << 1, p) 
# 			assert xi and xi == invert(a << 1, p)
			xi *= (yi - b)
# 			assert xi and divm(a << 1, yi - b, p)
			x.append(xi)
# 			assert not (f(xi) % p)
	
	for xi in x:
		logger.debug("primer no primo {} com p {}".format(xi, p))
		if xi<0:
			fc=abs(xi//p)*p
			xi+=fc
			logger.debug("corregido a {} fc {}".format(xi,fc))
		if xi>p:
			xi%=p
		for xii in range(xi, maxn + 1, p):
			yi = ordenadas_array[xii]
			logger.debug("no es primo x {} y {}".format(xii, yi))
# 			assert not yi % p
			if yi != p:
				abcisas_primos_array[xii] = False
				abcisas_set.discard(xii)
for x in list(abcisas_set):
	y = ordenadas_array[x]
	logger.debug("checando primalidad x {} y {}".format(x, y))
	if not es_primo(y):
		logger.debug("no primo {}".format(y))
# 		assert not is_prime(y)
		abcisas_set.discard(x)
		abcisas_primos_array[x] = False

# primos_debug = set([x for x in range(MAX_ABCISA + 1) if ordenadas_array[x] > 0 and es_primo(ordenadas_array[x])])
# assert abcisas_set.difference(primos_debug) == set(), "abcisas set {} real {} diff {}".format(abcisas_set, primos_debug, abcisas_set.difference(primos_debug))

logger.info("calculados {} primos hasta {}".format(len(abcisas_set), MAX_ABCISA))

for i in range(1, maxn + 1):
	abcisas_suma_primos_acumulada[i] = abcisas_suma_primos_acumulada[i - 1] + (1 if abcisas_primos_array[i] else 0)

logger.info("suma corriente calc")

for N in Ns:
	logger.info("res {}".format(abcisas_suma_primos_acumulada[N]))
	print("{}".format(abcisas_suma_primos_acumulada[N]))
