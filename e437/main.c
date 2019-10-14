//
//  main.c
//  e437
//
//  Created by ernesto alvarado on 13/10/19.
//  Copyright © 2019 ernesto alvarado. All rights reserved.
//

//
//  main.c
//  codechef_fibonacci_number
//
//  Created by ernesto alvarado on 28/08/19.
//  Copyright © 2019 ernesto alvarado. All rights reserved.
//

// XXX: https://cp-algorithms.com/algebra/phi-function.html
// XXX: https://roosephu.github.io/2013/09/23/PE-437/
// XXX: https://www.johannesbader.ch/2013/09/project-euler-problem-437-fibonacci-primitive-roots/
// XXX: https://www.fq.math.ca/Scanned/10-2/shanks-a.pdf
// XXX: https://sahandsaba.com/fibonacci-primitive-roots-project-euler.html

#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#include <sys/time.h>
#endif
#include <math.h>
#include <stdint.h>
#include <ctype.h>

#ifdef COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULONG_MAX
#endif

#define COMUN_TAM_MAX_LINEA (16*200000)
#define HEAG_LOG_MAX_TAM_CADENA 2000

#define COMUN_BUF_STATICO_TAM 1000
#define COMUN_BUF_STATICO (char[COMUN_BUF_STATICO_TAM] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define COMUN_ASSERT_DUROTE 0
#define COMUN_ASSERT_SUAVECITO 1
#define COMUN_ASSERT_NIMADRES 2

#define COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define COMUN_IDX_INVALIDO ((natural)COMUN_VALOR_INVALIDO)
#define COMUN_FUNC_STATICA static

typedef char byteme;
typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;

typedef enum BOOLEANOS
{
    falso = 0, verdadero
} bool;

#define COMUN_TIPO_ASSERT COMUN_ASSERT_DUROTE
/*
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_SUAVECITO
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_NIMADRES
 */

#define assert_timeout_dummy(condition) 0;

#if COMUN_TIPO_ASSERT == COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if COMUN_TIPO_ASSERT == COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if COMUN_TIPO_ASSERT == COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef COMUN_LOG
#define comun_log_debug(formato, args...) \
do \
{ \
size_t profundidad = 0; \
void *array[HEAG_LOG_MAX_TAM_CADENA]; \
profundidad = backtrace(array, HEAG_LOG_MAX_TAM_CADENA); \
comun_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
} \
while(0);
#else
#define comun_log_debug(formato, args...) 0
#endif

#define comun_max(x,y) ((x) < (y) ? (y) : (x))
#define comun_min(x,y) ((x) < (y) ? (x) : (y))

#define comun_calloc_local(tipo) (&(tipo){0})

void comun_log_debug_func (const char *format, ...);

#ifndef ONLINE_JUDGE
COMUN_FUNC_STATICA void
comun_current_utc_time (struct timespec *ts)
{
    
#ifdef __MACH__
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service (mach_host_self (), CALENDAR_CLOCK, &cclock);
    clock_get_time (cclock, &mts);
    mach_port_deallocate (mach_task_self (), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
#else
#ifdef COMUN_LOG
    clock_gettime (CLOCK_REALTIME, ts);
#endif
#endif
    
}

COMUN_FUNC_STATICA char *
comun_timestamp (char *stime)
{
    time_t ltime;
    long ms;
#ifndef ONLINE_JUDGE
    struct tm result;
    struct timespec spec;
#endif
    char parte_milisecundos[50];
    
    ltime = time (NULL);
    
#ifndef ONLINE_JUDGE
    localtime_r (&ltime, &result);
    asctime_r (&result, stime);
#endif
    
    *(stime + strlen (stime) - 1) = ' ';
    
#ifndef ONLINE_JUDGE
    comun_current_utc_time (&spec);
    ms = round (spec.tv_nsec / 1.0e3);
#endif
    sprintf (parte_milisecundos, "%ld", ms);
    strcat (stime, parte_milisecundos);
    return stime;
}

#endif
#ifdef COMUN_LOG
void
comun_log_debug_func (const char *format, ...)
{
    
    va_list arg;
    va_list arg2;
    const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
    const char *HEADER = "archivo: %s; funcion: %s; linea %d; nivel: %zd 8====D ";
    char formato[HEAG_LOG_MAX_TAM_CADENA + sizeof (HEADER)
                 + sizeof (PEDAZO_TIMESTAMP_HEADER)] = { '\0' };
    char pedazo_timestamp[sizeof (PEDAZO_TIMESTAMP_HEADER) + 100] = { '\0' };
    char cadena_timestamp[100] = { '\0' };
    
    comun_timestamp (cadena_timestamp);
    sprintf (pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);
    
    strcpy (formato, pedazo_timestamp);
    strcat (formato, HEADER);
    strcat (formato, format);
    strcat (formato, "\n");
    
    va_start (arg, format);
    va_copy (arg2, arg);
    vprintf (formato, arg2);
    va_end (arg2);
    va_end (arg);
    setbuf (stdout, NULL);
}
#endif

#ifdef COMUN_LOG
COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena (tipo_dato * arreglo, natural tam_arreglo, char *buffer)
{
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset (buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++)
    {
        characteres_escritos += sprintf (ap_buffer + characteres_escritos,
                                         "%1d", *(arreglo + i));
        if (i < tam_arreglo - 1)
        {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_natural (natural * arreglo,
                                natural tam_arreglo, char *buffer)
{
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset (buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++)
    {
        characteres_escritos +=
        sprintf (ap_buffer + characteres_escritos, "%2u", *(arreglo + i));
        if (i < tam_arreglo - 1)
        {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}

char *
comun_matrix_a_cadena (tipo_dato * matrix, natural filas_tam,
                       natural columas_tam, char *buffer)
{
    int i;
    natural inicio_buffer_act = 0;
    for (i = 0; i < filas_tam; i++)
    {
        comun_arreglo_a_cadena (matrix + i * columas_tam, columas_tam,
                                buffer + inicio_buffer_act);
        inicio_buffer_act += strlen (buffer + inicio_buffer_act);
        buffer[inicio_buffer_act++] = '\n';
        /*        comun_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer); */
    }
    return buffer;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_entero_largo_sin_signo (entero_largo_sin_signo *
                                               arreglo,
                                               entero_largo_sin_signo
                                               tam_arreglo, char *buffer)
{
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset (buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++)
    {
        characteres_escritos += sprintf (ap_buffer + characteres_escritos,
                                         "%llu", *(arreglo + i));
        if (i < tam_arreglo - 1)
        {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}
#else
COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena (tipo_dato * arreglo, natural tam_arreglo, char *buffer)
{
    return NULL;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_natural (natural * arreglo,
                                natural tam_arreglo, char *buffer)
{
    return NULL;
}

char *
comun_matrix_a_cadena (tipo_dato * matrix, natural filas_tam,
                       natural columas_tam, char *buffer)
{
    return NULL;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_entero_largo_sin_signo (entero_largo_sin_signo *
                                               arreglo,
                                               entero_largo_sin_signo
                                               tam_arreglo, char *buffer)
{
    return NULL;
}
#endif

#define comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_buf_local(a,a_tam) comun_arreglo_a_cadena(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_natural_buf_local(a,a_tam) comun_arreglo_a_cadena_natural(a,a_tam,COMUN_BUF_STATICO)

COMUN_FUNC_STATICA void
comun_strreplace (char s[], char chr, char repl_chr)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == chr)
        {
            s[i] = repl_chr;
        }
        i++;
    }
}

COMUN_FUNC_STATICA int
comun_lee_matrix_long_stdin (tipo_dato * matrix,
                             int *num_filas, int *num_columnas,
                             int num_max_filas, int num_max_columnas)
{
    int indice_filas = 0;
    int indice_columnas = 0;
    tipo_dato numero = 0;
    char *siguiente_cadena_numero = NULL;
    char *cadena_numero_actual = NULL;
    char *linea = NULL;
    
    linea = calloc (COMUN_TAM_MAX_LINEA, sizeof (char));
    
    while (indice_filas < num_max_filas
           && fgets (linea, COMUN_TAM_MAX_LINEA, stdin))
    {
        indice_columnas = 0;
        cadena_numero_actual = linea;
        comun_strreplace (linea, '\n', '\0');
        if (!strlen (linea))
        {
            comun_log_debug ("weird, linea vacia");
            continue;
        }
        for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
             cadena_numero_actual)
        {
            numero =
            (tipo_dato) strtol (siguiente_cadena_numero, &cadena_numero_actual, 10);
            if (cadena_numero_actual == siguiente_cadena_numero)
            {
                break;
            }
            *(matrix + indice_filas * num_max_columnas + indice_columnas) = numero;
            indice_columnas++;
        }
        if (num_columnas)
        {
            num_columnas[indice_filas] = indice_columnas;
        }
        indice_filas++;
        comun_log_debug ("las filas son %d, con clos %d", indice_filas,
                         indice_columnas);
    }
    
    *num_filas = indice_filas;
    free (linea);
    return 0;
}

COMUN_FUNC_STATICA natural
comun_cuenta_bitchs (tipo_dato num)
{
    natural bitch_cnt = 0;
    tipo_dato num_mod = 0;
    num_mod = num;
    while (num_mod)
    {
        num_mod &= ~(num_mod & (-num_mod));
        bitch_cnt++;
    }
    return bitch_cnt;
}

COMUN_FUNC_STATICA char
comun_letra_a_valor_minuscula (char letra)
{
    return letra - 'a';
}

COMUN_FUNC_STATICA natural
comun_max_natural (natural * nums, natural nums_tam)
{
    natural max = 0;
    int i = 0;
    
    for (i = 0; i < nums_tam; i++)
    {
        natural num_act = nums[i];
        if (num_act > max)
        {
            max = num_act;
        }
    }
    
    return max;
}

COMUN_FUNC_STATICA char *
comun_trimea (char *cad, natural cad_tam)
{
    char tmp = '\0';
    natural i = 0;
    natural j = 0;
    
    comun_log_debug ("entrada %s cad_tam %u", cad, cad_tam);
    while (j < cad_tam && cad[j] != '\0')
    {
        comun_log_debug ("en j %u car %c", j, cad[j]);
        while (j < cad_tam && !isalpha (cad[j]))
        {
            comun_log_debug ("brincando j %u car %c", j, cad[j]);
            j++;
        }
        comun_log_debug ("aora j %u car %c", j, cad[j]);
        if (j == cad_tam)
        {
            comun_log_debug ("q ped");
            break;
        }
        tmp = cad[i];
        cad[i] = cad[j];
        cad[j] = tmp;
        i++;
        j++;
    }
    comun_log_debug ("mierda '%c'", cad[j]);
    
    i = 0;
    while (isalpha (cad[i++]))
        ;
    comun_log_debug ("salida %s", cad);
    cad[i - 1] = '\0';
    
    return cad;
}

#endif

#define COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

COMUN_FUNC_STATICA bool
comun_es_digito (char c)
{
    return c >= '0' && c <= '9';
}

COMUN_FUNC_STATICA byteme
comun_caracter_a_num (char c)
{
    return c - '0';
}

COMUN_FUNC_STATICA void
comun_invierte_arreglo_byteme (byteme * a, natural a_tam)
{
    natural i = 0;
    natural j = a_tam - 1;
    while (i < j)
    {
        byteme t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

COMUN_FUNC_STATICA void
comun_invierte_arreglo_natural (natural * a, natural a_tam)
{
    natural i = 0;
    natural j = a_tam - 1;
    while (i < j)
    {
        natural t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

COMUN_FUNC_STATICA natural
comun_encuentra_minimo_natural (natural * a, natural a_tam)
{
    natural min = COMUN_VALOR_INVALIDO;
    natural i;
    for (i = 0; i < a_tam; i++)
    {
        if (min > a[i])
        {
            min = a[i];
        }
    }
    return min;
}

COMUN_FUNC_STATICA entero_largo
comun_mcd (entero_largo a, entero_largo b)
{
    entero_largo r = COMUN_VALOR_INVALIDO;
    while (a && b)
    {
        entero_largo tmp = b;
        b = a % b;
        a = tmp;
    }
    
    if (!a)
    {
        r = b;
    }
    if (!b)
    {
        r = a;
    }
    return r;
}

#define comun_compara_tipo(tipo) COMUN_FUNC_STATICA int comun_compara_##tipo(const void *pa, const void *pb) { \
int r = 0; \
tipo a = *(tipo *)pa; \
tipo b = *(tipo *)pb; \
if (a < b) { \
r = -1; \
} else { \
if (a > b) { \
r = 1; \
} \
} \
return r; \
}

comun_compara_tipo (natural) comun_compara_tipo (entero_largo)
COMUN_FUNC_STATICA natural
comun_encuentra_divisores (natural n,
                           natural * divisores, natural divisores_tam)
{
    natural divisores_cnt = 0;
    natural i = 0;
    for (i = 1; i * i < n; i++)
    {
        if (!(n % i))
        {
            assert_timeout (divisores_cnt < divisores_tam);
            divisores[divisores_cnt++] = i;
            assert_timeout (divisores_cnt < divisores_tam);
            divisores[divisores_cnt++] = n / i;
        }
    }
    
    if (i * i == n)
    {
        assert_timeout (divisores_cnt < divisores_tam);
        divisores[divisores_cnt++] = n / i;
    }
    qsort (divisores, divisores_cnt, sizeof (natural), comun_compara_natural);
    return divisores_cnt;
}

#endif

#if 1

#define PRIMALIDAD_LIMITE_MULTIPLICACION_NATIVA 4294967296

COMUN_FUNC_STATICA entero_largo_sin_signo
primalidad_normalizar_a_minimo (entero_largo n, entero_largo min,
                                entero_largo m)
{
    /*
     if(n!=min){
     entero_largo dif=n-min;
     entero_largo fac=dif/llabs(dif);
     n+=(((dif-fac)/m)+((dif&0x8000000000000000)>>63))*m;
     }
     */
    return ((min - (!!min)) / m) * m + (m + (n % m)) % m;
}

COMUN_FUNC_STATICA entero_largo_sin_signo
primalidad_normalizar_signo_modulo (entero_largo n, entero_largo m)
{
    if (n < 0)
    {
        n %= m;
        n += m;
    }
    if (n > m)
    {
        n %= m;
    }
    return n;
}

#if 1
COMUN_FUNC_STATICA entero_largo_sin_signo
primalidad_mul_mod (entero_largo_sin_signo a, entero_largo_sin_signo b,
                    entero_largo_sin_signo c)
{
    entero_largo_sin_signo r;
    
    if (a <= PRIMALIDAD_LIMITE_MULTIPLICACION_NATIVA
        && b <= PRIMALIDAD_LIMITE_MULTIPLICACION_NATIVA)
    {
        r = (a * b) % c;
    }
    else
    {
        entero_largo_sin_signo x = 0, y = a % c;
        while (b)
        {
            if (b & 1)
            {
                x = (x + y) % c;
            }
            y = (y << 1) % c;
            b >>= 1;
        }
        r = x % c;
    }
    return r;
}
#else
#define primalidad_mul_mod(a,b,c) ((a*b)%c)
#endif

COMUN_FUNC_STATICA entero_largo_sin_signo
primalidad_exp_mod (entero_largo_sin_signo a, entero_largo_sin_signo p,
                    entero_largo_sin_signo m)
{
    entero_largo_sin_signo acum_res = 1;
    while (p)
    {
        if (p & 1)
        {
            acum_res = primalidad_mul_mod (acum_res, a, m);
        }
        a = primalidad_mul_mod (a, a, m);
        p >>= 1;
    }
    comun_log_debug ("pot lenta %llu a la %llu mod %llu es %llu", a, p, m,
                     acum_res);
    return acum_res;
}

// XXX: https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
COMUN_FUNC_STATICA entero_largo_sin_signo
primalidad_rand (entero_largo_sin_signo max)
{
    entero_largo_sin_signo x = (((entero_largo_sin_signo) rand ()) << 32)
    | rand ();
    //        comun_log_debug("num rand %llu - defec %llu = %llu y x %llu", num_rand, defect, num_rand-defect, x);
    return x % max;
}

COMUN_FUNC_STATICA entero_largo_sin_signo
primalidad_rand_intervalo (entero_largo_sin_signo min,
                           entero_largo_sin_signo max)
{
    //    comun_log_debug("rand intervalo min %llu max %llu", min, max);
    return (entero_largo_sin_signo) min + primalidad_rand (max - min);
}

COMUN_FUNC_STATICA bool
primalidad_prueba_miller_rabbit (entero_largo_sin_signo n)
{
    entero_largo_sin_signo a = primalidad_rand_intervalo (2, n - 2);
    entero_largo_sin_signo d = n - 1;
    while (!(d & 1LL))
    {
        d >>= 1;
    }
    entero_largo_sin_signo x = primalidad_exp_mod (a, d, n);
    
    if (x == 1 || x == (n - 1))
    {
        return verdadero;
    }
    while (d != (n - 1))
    {
        x = primalidad_mul_mod (x, x, n);
        d <<= 1;
        if (x == 1)
        {
            return falso;
        }
        if (x == (n - 1))
        {
            return verdadero;
        }
    }
    return falso;
}

COMUN_FUNC_STATICA bool
primalidad_es_primo (entero_largo_sin_signo n, natural k)
{
    if (n <= 1 || n == 4)
    {
        return falso;
    }
    if (n <= 3)
    {
        return verdadero;
    }
    
    while (k--)
    {
        if (!primalidad_prueba_miller_rabbit (n))
        {
            return falso;
        }
    }
    comun_log_debug ("%llu es primo", n);
    return verdadero;
}

#endif

#if 1

#define PRIMOS_NUM_MAX ((int)1E8)
//#define PRIMOS_NUM_MAX 10000
typedef struct primos_datos
{
    natural primos_criba_tam;
    natural primos_criba[PRIMOS_NUM_MAX + 1];
    bool primos_criba_es_primo[PRIMOS_NUM_MAX + 1];
    
} primos_datos;

typedef void (*primos_criba_primo_encontrado_cb) (natural primo,
natural idx_primo,
void *cb_ctx);
typedef void (*primos_criba_compuesto_encontrado_cb) (natural primo,
natural idx_primo,
natural
compuesto_origen,
void *cb_ctx);

typedef void (*primos_criba_divisible_encontrado_cb) (natural primo,
natural idx_primo,
natural compuesto,
void *cb_ctx);

typedef void (*primos_criba_no_divisible_encontrado_cb) (natural primo,
natural idx_primo,
natural compuesto,
void *cb_ctx);

//#define PRIMOS_CRIBA_USA_CALLBACKS
COMUN_FUNC_STATICA natural
primos_criba_init(natural limite,
                    primos_criba_primo_encontrado_cb primo_cb,
                    primos_criba_compuesto_encontrado_cb compuesto_cb,
                    primos_criba_divisible_encontrado_cb
                    divisible_encontrado_cb,
                    primos_criba_no_divisible_encontrado_cb
                    no_divisible_encontrado_cb, void *cb_ctx, primos_datos * pd)
{
    bool *primos_criba_es_primo = pd->primos_criba_es_primo;
    natural *primos_criba = pd->primos_criba;
    natural primos_criba_tam = 0;
    comun_log_debug ("primos asta %u", limite);
    assert_timeout (limite <= PRIMOS_NUM_MAX);
    natural i, j;
    for (i = 2; i <= limite; i++)
    {
        primos_criba_es_primo[i] = verdadero;
    }
    for (i = 2; i <= limite; i++)
    {
        if (primos_criba_es_primo[i])
        {
            primos_criba[primos_criba_tam++] = i;
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
            if (primo_cb)
            {
                primo_cb (i, primos_criba_tam - 1, cb_ctx);
            }
#endif
        }
        for (j = 0; j < primos_criba_tam && primos_criba[j] * i <= limite; j++)
        {
            primos_criba_es_primo[primos_criba[j] * i] = falso;
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
            if (compuesto_cb)
            {
                compuesto_cb (primos_criba[j], j, i, cb_ctx);
            }
#endif
            if (!(i % primos_criba[j]))
            {
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
                if (divisible_encontrado_cb)
                {
                    divisible_encontrado_cb (primos_criba[j], j, i, cb_ctx);
                }
#endif
                break;
            }
            else
            {
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
                if (no_divisible_encontrado_cb)
                {
                    no_divisible_encontrado_cb (primos_criba[j], j, i, cb_ctx);
                }
#endif
            }
        }
    }
    comun_log_debug ("generados %u primos", primos_criba_tam);
    pd->primos_criba_tam = primos_criba_tam;
    return primos_criba_tam;
}

#endif


#if 1
COMUN_FUNC_STATICA entero_largo
gcd_algoritmo_euclidiano_extendido (entero_largo a, entero_largo b,
                                     entero_largo * xp, entero_largo * yp)
{
    entero_largo x = 0, y = 1, u = 1, v = 0;
    while (a)
    {
        entero_largo q = b / a;
        entero_largo r = b % a;
        entero_largo m = x - u * q;
        entero_largo n = y - v * q;
        b = a;
        a = r;
        x = u;
        y = v;
        u = m;
        v = n;
    }
    *xp = x;
    *yp = y;
    return b;
}

COMUN_FUNC_STATICA natural
mod_inverso_multiplicativo_modular (entero_largo a, entero_largo m)
{
    entero_largo r = 0;
    entero_largo x;
    entero_largo g = gcd_algoritmo_euclidiano_extendido (a, m, &x,
                                                          comun_calloc_local
                                                          (entero_largo));
    if (g == 1)
    {
        r = x % m;
        if (r < 0)
        {
            r += m;
        }
    }
    return (natural) r;
}

#endif
#if 1
COMUN_FUNC_STATICA entero_largo
shanks_tonelli_simbolo_legendre (entero_largo a, entero_largo p)
{
    entero_largo r = (entero_largo) primalidad_exp_mod (a, ((p - 1) >> 1), p);
    return r;
}

COMUN_FUNC_STATICA entero_largo
shanks_tonelli_calcula_z (entero_largo p, primos_datos * pd)
{
    entero_largo z = 0;
    entero_largo p_menos_1_entre_2 = (p - 1) >> 1;
    for (natural i = 1; i < pd->primos_criba_tam && z < 70; i++)
    {
        z = pd->primos_criba[i];
        entero_largo z_menos_1 = z - 1;
        entero_largo z_menos_1_entre_2 = z_menos_1 >> 1;
        entero_largo p_res_cuad_z;
        if (primalidad_exp_mod (p, z_menos_1_entre_2, z) == z_menos_1)
        {
            p_res_cuad_z = -1;
        }
        else
        {
            p_res_cuad_z = 1;
        }
        entero_largo signo =
        ((p_menos_1_entre_2 * z_menos_1_entre_2) & 1LL) ? -1 : 1;
        if (signo * p_res_cuad_z == -1)
        {
            break;
        }
    }
    return z;
}

COMUN_FUNC_STATICA entero_largo
shanks_tonelli_conguencia_residuo_cuadratico (entero_largo n, entero_largo p,
                                              primos_datos * pd)
{
    entero_largo p_menos_1 = p - 1;
    entero_largo S = 0;
    while (!(p_menos_1 & 1))
    {
        p_menos_1 >>= 1;
        S++;
    }
    entero_largo Z = shanks_tonelli_calcula_z (p, pd);
    entero_largo Q = p_menos_1;
    entero_largo c = (entero_largo) primalidad_exp_mod (Z, Q, p);
    entero_largo R = (entero_largo) primalidad_exp_mod (n,
                                                        (entero_largo_sin_signo)
                                                        ((Q + 1) >> 1),
                                                        p);
    entero_largo t = (entero_largo) primalidad_exp_mod (n, Q, p);
    entero_largo M = S;
    comun_log_debug ("p %lld t %lld R %lld M %lld", p, t, R, M);
    while (t % p != 1)
    {
        entero_largo i;
        for (i = 1; i < M; i++)
        {
            if (primalidad_exp_mod (t, 1ULL << i, p) == 1)
            {
                break;
            }
        }
        comun_log_debug ("pot %lld", 1 << (M - i - 1));
        entero_largo b =
        (entero_largo) primalidad_exp_mod (c, 1ULL << (M - i - 1), p);
        comun_log_debug ("b %lld R %lld t %lld c %lld M %lld i %lld", b, R, t,
                         c, M, i);
        //        R=primalidad_mul_mod(R, b, p);
        R = (R * b) % p;
        c = primalidad_exp_mod (b, 2, p);
        //        t=primalidad_mul_mod(t, c, p);
        t = (t * c) % p;
        M = i;
    }
    return R;
}


COMUN_FUNC_STATICA entero_largo
shanks_tonelli_simbolo_jacobi (entero_largo a, entero_largo n)
{
    assert_timeout (n & 1);
    entero_largo t = 1;
    
    while (a)
    {
        while (!(a & 1))
        {
            a >>= 1;
            natural r = n % 8;
            if (r == 3 || r == 5)
            {
                t = -t;
            }
        }
        entero_largo tmp = a;
        a = n;
        n = tmp;
        if (a % 4 == 3 && n % 4 == 3)
        {
            t = -t;
        }
        a %= n;
    }
    if (n == 1)
    {
        return t;
    }
    else
    {
        return 0;
    }
}
#endif


#define MAX_NUM PRIMOS_NUM_MAX

COMUN_FUNC_STATICA natural e437_encuentra_factores_primos(entero_largo a, primos_datos *pd, entero_largo *factores_primos){
    natural factores_primos_tam=0;
    for(natural i=0;i<pd->primos_criba_tam;i++){
        entero_largo p=pd->primos_criba[i];
        if(!(a%p)){
            factores_primos[factores_primos_tam++]=p;
            while(!(a%p)){
                a/=p;
            }
        }
        if(a==1){
            break;
        }
    }
    if(a>1){
        factores_primos[factores_primos_tam++]=a;
    }
    return factores_primos_tam;
}

entero_largo factores_primos[MAX_NUM]={0};
COMUN_FUNC_STATICA bool e437_es_raiz_primitiva(entero_largo a,entero_largo p,primos_datos *pd){
    entero_largo p_menos_1=p-1;

    natural factores_primos_tam=e437_encuentra_factores_primos(p_menos_1, pd, factores_primos);

    for(natural i=0;i<factores_primos_tam;i++){
        entero_largo fp=factores_primos[i];
        if(primalidad_exp_mod(a, p_menos_1/fp, p)==1){
            return falso;
        }
    }
    
    return verdadero;
}

COMUN_FUNC_STATICA bool e437_es_raiz_primitiva_fibonacci(entero_largo p, primos_datos *pd){
    entero_largo p_mod_5=p%5;
    entero_largo simbolo_jacobi=shanks_tonelli_simbolo_jacobi(5, p);
    if((p_mod_5==1 || p_mod_5==4) && simbolo_jacobi==1){
        entero_largo raiz_5=shanks_tonelli_conguencia_residuo_cuadratico(5, p, pd);
        entero_largo dos_inv=mod_inverso_multiplicativo_modular(2, p);
        entero_largo raiz_potencial_1=primalidad_mul_mod(1+raiz_5, dos_inv, p);
        entero_largo raiz_potencial_2=primalidad_mul_mod(primalidad_normalizar_signo_modulo(1-raiz_5,p), dos_inv, p);

        if(e437_es_raiz_primitiva(raiz_potencial_1, p, pd)|| e437_es_raiz_primitiva(raiz_potencial_2, p, pd)){
            assert_timeout((primalidad_exp_mod(raiz_potencial_1, 2, p)==(raiz_potencial_1+1)) ||(primalidad_exp_mod(raiz_potencial_2, 2, p)==(raiz_potencial_2+1)));
            return verdadero;
        }
    }
    return falso;
}

COMUN_FUNC_STATICA void
e437_main ()
{
    primos_datos *pd=NULL;
    pd=calloc(1, sizeof(primos_datos));
    assert_timeout(pd);
    natural primos_tam=primos_criba_init(MAX_NUM, NULL, NULL, NULL, NULL, NULL, pd);
    entero_largo r=0;
    natural r_cnt=0;
    
    for(natural i=3;i<primos_tam;i++){
        entero_largo p=pd->primos_criba[i];
        if(e437_es_raiz_primitiva_fibonacci(p, pd)){
            r+=p;
            r_cnt++;
        }
    }
    printf("%lld\n",r+5);
}


int
main (int argc, const char *argv[])
{
    e437_main();
    return 0;
}
