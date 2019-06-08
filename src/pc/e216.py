from array import array
from math import exp, log, ceil
from sympy.ntheory import legendre_symbol, is_quad_residue
from gmpy2 import divm, invert


# XXX: https://www.johndcook.com/blog/2008/12/10/solving-linear-congruences/
# XXX: http://wrean.ca/cazelais/linear_congruence.pdf
# XXX: https://stackoverflow.com/questions/16044553/solving-a-modular-equation-python
def iterative_egcd(a, b):
	x, y, u, v = 0, 1, 1, 0
	while a != 0:
		q, r = b // a, b % a; m, n = x - u * q, y - v * q  # use x//y for floor "floor division"
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
		assert(n > a > 0 and n % 2 == 1)
		t = 1
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
			if self._simbolo_legendre(n, p) == 1:
				rc.append(p)
		return rc
	
	def _calcula_limite_b_suave(self, n):
		b = ceil(exp(((log(n) * log(log(n))) / 2) / 2))
		return int(b)
	
	# XXX: https://rosettacode.org/wiki/Tonelli-Shanks_algorithm#Python
	def _calcula_z_shanks_tonelli(self, p):
		for z in range(2, p):
			if p - 1 == self._simbolo_legendre(z, p):
				break
		return z

	def calcula_conguencia_residuo_cuadratico(self, n, p):
		p_menos_1 = p - 1
		S = 0
		while not (p_menos_1 & 1):
			p_menos_1 >>= 1
			S += 1
		Z = self._calcula_z_shanks_tonelli(p)
		Q = p_menos_1
		c = (Z ** Q) % p
		R = (n ** ((Q + 1) >> 1)) % p
		t = (n ** Q) % p
		M = S
		while (t % p) != 1:
			i = 0
			for i in range(1, M):
				if ((t ** (i << 1)) % p) == 1:
					break
			b = (c ** (1 << (M - i - 1))) % p
			R = R * b
			t = t * (b ** 2)
			c = b ** 2
			M = i
		return R, p - R


MAX_PRIMOS = int(1E7)
qs = QuadraticSieve(MAX_PRIMOS)

a, b, c = [int(x) for x in input().strip().split(" ")]
q = int(input())
f = lambda x:a * x * x + b * x + c
valores_funcion_primos = set()
for i in range(MAX_PRIMOS + 1):
	valores_funcion_primos.add(f(i))

discriminante = b * b - 4 * a * c
for p in qs.primos:
	# XXX: https://math.stackexchange.com/questions/551700/when-is-the-quadratic-congruence-ax2-bx-c-equiv-0-pmod-p-solvable
	# XXX: https://rkm0959.tistory.com/20
	# XXX: http://pipilupe.blogspot.com/2013/06/project-euler-problem-216.html
	if p == 2:
		continue
	ls = qs.simbolo_jacobi(discriminante, p)
	assert ls == legendre_symbol(discriminante, p)
	yt = is_quad_residue(discriminante, p) 
	y = []
	x = []
	if ls == -1:
		continue
	if not discriminante or not ls:
			y.append(0)
	else:
		assert ls == 1
		y1 = qs.calcula_conguencia_residuo_cuadratico(discriminante, p)
		y2 = p - y1
		assert yt in [y1, y2]
		y.append(y1, y2)
	
	# XXX: https://stackoverflow.com/questions/4798654/modular-multiplicative-inverse-function-in-python
	for yi in y:
		xi = modinv(a << 1, p) 
		assert xi and xi == invert(a << 1, p)
		xi *= (yi - b)
		assert xi and divm(a << 1, yi - b, p)
		x.append(xi)

while q:
	N = int(input())
	q -= 1
