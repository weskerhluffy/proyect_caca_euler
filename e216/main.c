//
//  main.c
//  e216
//
//  Created by ernesto alvarado on 21/06/19.
//  Copyright © 2019 ernesto alvarado. All rights reserved.
//
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

typedef enum BOOLEANOS {
    falso = 0, verdadero
} bool;

#define COMUN_TIPO_ASSERT COMUN_ASSERT_SUAVECITO
/*
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_DUROTE
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

void comun_log_debug_func(const char *format, ...);

#ifndef ONLINE_JUDGE
COMUN_FUNC_STATICA void comun_current_utc_time(struct timespec *ts) {
    
#ifdef __MACH__
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
#else
#ifdef COMUN_LOG
    clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif
    
}

COMUN_FUNC_STATICA void comun_timestamp(char *stime) {
    time_t ltime;
    long ms;
#ifndef ONLINE_JUDGE
    struct tm result;
    struct timespec spec;
#endif
    char parte_milisecundos[50];
    
    ltime = time(NULL);
    
#ifndef ONLINE_JUDGE
    localtime_r(&ltime, &result);
    asctime_r(&result, stime);
#endif
    
    *(stime + strlen(stime) - 1) = ' ';
    
#ifndef ONLINE_JUDGE
    comun_current_utc_time(&spec);
    ms = round(spec.tv_nsec / 1.0e3);
#endif
    sprintf(parte_milisecundos, "%ld", ms);
    strcat(stime, parte_milisecundos);
}

#endif
#ifdef COMUN_LOG
void comun_log_debug_func(const char *format, ...) {
    
    va_list arg;
    va_list arg2;
    const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
    const char *HEADER =
    "archivo: %s; funcion: %s; linea %d; nivel: %zd 8====D ";
    char formato[HEAG_LOG_MAX_TAM_CADENA + sizeof(HEADER)
                 + sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
    char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
    char cadena_timestamp[100] = {'\0'};
    
    comun_timestamp(cadena_timestamp);
    sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);
    
    strcpy(formato, pedazo_timestamp);
    strcat(formato, HEADER);
    strcat(formato, format);
    strcat(formato, "\n");
    
    va_start(arg, format);
    va_copy(arg2, arg);
    vprintf(formato, arg2);
    va_end(arg2);
    va_end(arg);
    setbuf(stdout, NULL);
}
#endif

#ifdef COMUN_LOG
COMUN_FUNC_STATICA char *comun_arreglo_a_cadena(tipo_dato *arreglo, natural tam_arreglo,
                                                char *buffer) {
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset(buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++) {
        characteres_escritos += sprintf(ap_buffer + characteres_escritos,
                                        "%1d", *(arreglo + i));
        if (i < tam_arreglo - 1) {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}

COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_natural(natural *arreglo,
                                                        natural tam_arreglo, char *buffer) {
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset(buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++) {
        characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
                                        *(arreglo + i));
        if (i < tam_arreglo - 1) {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}
char *comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
                            natural columas_tam, char *buffer) {
    int i;
    natural inicio_buffer_act = 0;
    for (i = 0; i < filas_tam; i++) {
        comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
                               buffer + inicio_buffer_act);
        inicio_buffer_act += strlen(buffer + inicio_buffer_act);
        buffer[inicio_buffer_act++] = '\n';
        /*        comun_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
    }
    return buffer;
}

COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_entero_largo_sin_signo(
                                                                       entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
                                                                       char *buffer) {
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset(buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++) {
        characteres_escritos += sprintf(ap_buffer + characteres_escritos,
                                        "%llu", *(arreglo + i));
        if (i < tam_arreglo - 1) {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}
#else
COMUN_FUNC_STATICA char *comun_arreglo_a_cadena(tipo_dato *arreglo,
                                                natural tam_arreglo, char *buffer) {
    return NULL;
}
COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_natural(natural *arreglo,
                                                        natural tam_arreglo, char *buffer) {
    return NULL;
}
char *comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
                            natural columas_tam, char *buffer) {
    return NULL;
}

COMUN_FUNC_STATICA char *comun_arreglo_a_cadena_entero_largo_sin_signo(
                                                                       entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
                                                                       char *buffer) {
    return NULL;
}
#endif

#define comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_buf_local(a,a_tam) comun_arreglo_a_cadena(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_natural_buf_local(a,a_tam) comun_arreglo_a_cadena_natural(a,a_tam,COMUN_BUF_STATICO)

COMUN_FUNC_STATICA void comun_strreplace(char s[], char chr, char repl_chr) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == chr) {
            s[i] = repl_chr;
        }
        i++;
    }
}

COMUN_FUNC_STATICA int comun_lee_matrix_long_stdin(tipo_dato *matrix,
                                                   int *num_filas, int *num_columnas, int num_max_filas,
                                                   int num_max_columnas) {
    int indice_filas = 0;
    int indice_columnas = 0;
    tipo_dato numero = 0;
    char *siguiente_cadena_numero = NULL;
    char *cadena_numero_actual = NULL;
    char *linea = NULL;
    
    linea = calloc(COMUN_TAM_MAX_LINEA, sizeof(char));
    
    while (indice_filas < num_max_filas
           && fgets(linea, COMUN_TAM_MAX_LINEA, stdin)) {
        indice_columnas = 0;
        cadena_numero_actual = linea;
        comun_strreplace(linea, '\n', '\0');
        if (!strlen(linea)) {
            comun_log_debug("weird, linea vacia");
            continue;
        }
        for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
             cadena_numero_actual) {
            numero = (tipo_dato)strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
            if (cadena_numero_actual == siguiente_cadena_numero) {
                break;
            }
            *(matrix + indice_filas * num_max_columnas + indice_columnas) =
            numero;
            indice_columnas++;
        }
        if (num_columnas) {
            num_columnas[indice_filas] = indice_columnas;
        }
        indice_filas++;
        comun_log_debug("las filas son %d, con clos %d", indice_filas,
                        indice_columnas);
    }
    
    *num_filas = indice_filas;
    free(linea);
    return 0;
}

COMUN_FUNC_STATICA natural comun_cuenta_bitchs(tipo_dato num) {
    natural bitch_cnt = 0;
    tipo_dato num_mod = 0;
    num_mod = num;
    while (num_mod) {
        num_mod &= ~(num_mod & (-num_mod));
        bitch_cnt++;
    }
    return bitch_cnt;
}

COMUN_FUNC_STATICA char comun_letra_a_valor_minuscula(char letra) {
    return letra - 'a';
}

COMUN_FUNC_STATICA natural comun_max_natural(natural *nums, natural nums_tam) {
    natural max = 0;
    int i = 0;
    
    for (i = 0; i < nums_tam; i++) {
        natural num_act = nums[i];
        if (num_act > max) {
            max = num_act;
        }
    }
    
    return max;
}

COMUN_FUNC_STATICA char *comun_trimea(char *cad, natural cad_tam) {
    char tmp = '\0';
    natural i = 0;
    natural j = 0;
    
    comun_log_debug("entrada %s cad_tam %u", cad, cad_tam);
    while (j < cad_tam && cad[j] != '\0') {
        comun_log_debug("en j %u car %c", j, cad[j]);
        while (j < cad_tam && !isalpha(cad[j])) {
            comun_log_debug("brincando j %u car %c", j, cad[j]);
            j++;
        }
        comun_log_debug("aora j %u car %c", j, cad[j]);
        if (j == cad_tam) {
            comun_log_debug("q ped");
            break;
        }
        tmp = cad[i];
        cad[i] = cad[j];
        cad[j] = tmp;
        i++;
        j++;
    }
    comun_log_debug("mierda '%c'", cad[j]);
    
    i = 0;
    while (isalpha(cad[i++]))
        ;
    comun_log_debug("salida %s", cad);
    cad[i - 1] = '\0';
    
    return cad;
}

#endif

#define COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

COMUN_FUNC_STATICA bool comun_es_digito(char c) {
    return c >= '0' && c <= '9';
}

COMUN_FUNC_STATICA byteme comun_caracter_a_num(char c) {
    return c - '0';
}

COMUN_FUNC_STATICA void comun_invierte_arreglo_byteme(byteme *a, natural a_tam) {
    natural i = 0;
    natural j = a_tam - 1;
    while (i < j) {
        byteme t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

COMUN_FUNC_STATICA void comun_invierte_arreglo_natural(natural *a,
                                                       natural a_tam) {
    natural i = 0;
    natural j = a_tam - 1;
    while (i < j) {
        natural t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

COMUN_FUNC_STATICA natural comun_encuentra_minimo_natural(natural *a,
                                                          natural a_tam) {
    natural min = COMUN_VALOR_INVALIDO;
    natural i;
    for (i = 0; i < a_tam; i++) {
        if (min > a[i]) {
            min = a[i];
        }
    }
    return min;
}

COMUN_FUNC_STATICA natural comun_mcd(natural a, natural b) {
    natural r = COMUN_VALOR_INVALIDO;
    while (a && b) {
        natural tmp = b;
        b = a % b;
        a = tmp;
    }
    
    if (!a) {
        r = b;
    }
    if (!b) {
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

comun_compara_tipo(natural)

COMUN_FUNC_STATICA natural comun_encuentra_divisores(natural n,
                                                     natural *divisores, natural divisores_tam) {
    natural divisores_cnt = 0;
    natural i = 0;
    for (i = 1; i * i < n; i++) {
        if (!(n % i)) {
            assert_timeout(divisores_cnt < divisores_tam);
            divisores[divisores_cnt++] = i;
            assert_timeout(divisores_cnt < divisores_tam);
            divisores[divisores_cnt++] = n / i;
        }
    }
    
    if (i * i == n) {
        assert_timeout(divisores_cnt < divisores_tam);
        divisores[divisores_cnt++] = n / i;
    }
    qsort(divisores, divisores_cnt, sizeof(natural), comun_compara_natural);
    return divisores_cnt;
}

#endif

#if 1
COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_mul_mod(
                                                             entero_largo_sin_signo a, entero_largo_sin_signo b,
                                                             entero_largo_sin_signo c) {
    entero_largo x = 0, y = a % c;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x + y) % c;
        }
        y = (y * 2) % c;
        b /= 2;
    }
    return x % c;
}

// TODO: Cambiar por iterativa
COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_exp_mod(
                                                             entero_largo_sin_signo a, entero_largo_sin_signo p,
                                                             entero_largo_sin_signo m) {
    if (!p) {
        return 1;
    }
    if (p & 1) {
        return primalidad_mul_mod(a, primalidad_exp_mod(a, p - 1, m), m);
    }
    entero_largo x = primalidad_exp_mod(a, p >> 1, m);
    return primalidad_mul_mod(x, x, m);
}

// XXX: https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_rand(
                                                          entero_largo_sin_signo max) {
    entero_largo_sin_signo x = (((entero_largo_sin_signo) rand()) << 32)
    | rand();
    //        comun_log_debug("num rand %llu - defec %llu = %llu y x %llu", num_rand, defect, num_rand-defect, x);
    return x % max;
}

COMUN_FUNC_STATICA entero_largo_sin_signo primalidad_rand_intervalo(
                                                                    entero_largo_sin_signo min, entero_largo_sin_signo max) {
    //    comun_log_debug("rand intervalo min %llu max %llu", min, max);
    return (entero_largo_sin_signo) min + primalidad_rand(max - min);
}

COMUN_FUNC_STATICA bool primalidad_prueba_miller_rabbit(
                                                        entero_largo_sin_signo n) {
    entero_largo_sin_signo a = primalidad_rand_intervalo(2, n - 2);
    //    comun_log_debug("rand a %llu inter %llu-%llu", a, 2, n-2);
    entero_largo_sin_signo d = n - 1;
    while (!(d & 1)) {
        d >>= 1;
    }
    //    comun_log_debug("d %llu", d);
    entero_largo_sin_signo x = primalidad_exp_mod(a, d, n);
    //    comun_log_debug("x %llu", x);
    
    if (x == 1 || x == (n - 1)) {
        return verdadero;
    }
    while (d != (n - 1)) {
        x = primalidad_mul_mod(x, x, n);
        d <<= 1;
        if (x == 1) {
            return falso;
        }
        if (x == (n - 1)) {
            return verdadero;
        }
    }
    return falso;
}

COMUN_FUNC_STATICA bool primalidad_es_primo(entero_largo_sin_signo n, natural k) {
    if (n <= 1 || n == 4) {
        return falso;
    }
    if (n <= 3) {
        return verdadero;
    }
    
    while (k--) {
        if (!primalidad_prueba_miller_rabbit(n)) {
            return falso;
        }
    }
    comun_log_debug("%llu es primo", n);
    return verdadero;
}

#endif

#if 1

#define PRIMOS_NUM_MAX ((int)1E6)
//#define PRIMOS_NUM_MAX 11
typedef struct primos_datos {
    natural primos_criba_tam;
    natural primos_criba[PRIMOS_NUM_MAX + 1];
    bool primos_criba_es_primo[PRIMOS_NUM_MAX + 1];
    
} primos_datos;

typedef void (*primos_criba_primo_encontrado_cb)(natural primo,
natural idx_primo, void *cb_ctx);
typedef void (*primos_criba_compuesto_encontrado_cb)(natural primo,
natural idx_primo, natural compuesto_origen, void *cb_ctx);

typedef void (*primos_criba_divisible_encontrado_cb)(natural primo,
natural idx_primo, natural compuesto, void *cb_ctx);

typedef void (*primos_criba_no_divisible_encontrado_cb)(natural primo,
natural idx_primo, natural compuesto, void *cb_ctx);

COMUN_FUNC_STATICA natural primos_criba_criba(natural limite,
                                              primos_criba_primo_encontrado_cb primo_cb,
                                              primos_criba_compuesto_encontrado_cb compuesto_cb,
                                              primos_criba_divisible_encontrado_cb divisible_encontrado_cb,
                                              primos_criba_no_divisible_encontrado_cb no_divisible_encontrado_cb,
                                              void *cb_ctx, primos_datos *pd) {
    bool *primos_criba_es_primo = pd->primos_criba_es_primo;
    natural *primos_criba = pd->primos_criba;
    comun_log_debug("primos asta %u", limite);
    assert_timeout(limite<=PRIMOS_NUM_MAX);
    natural i, j;
    for (i = 2; i <= limite; i++) {
        primos_criba_es_primo[i] = verdadero;
    }
    for (i = 2; i <= limite; i++) {
        if (primos_criba_es_primo[i]) {
            primos_criba[pd->primos_criba_tam++] = i;
            if (primo_cb) {
                primo_cb(i, pd->primos_criba_tam - 1, cb_ctx);
            }
        }
        for (j = 0; j < pd->primos_criba_tam && primos_criba[j] * i <= limite;
             j++) {
            primos_criba_es_primo[primos_criba[j] * i] = falso;
            if (compuesto_cb) {
                compuesto_cb(primos_criba[j], j, i, cb_ctx);
            }
            if (!(i % primos_criba[j])) {
                if (divisible_encontrado_cb) {
                    divisible_encontrado_cb(primos_criba[j], j, i, cb_ctx);
                }
                break;
            } else {
                if (no_divisible_encontrado_cb) {
                    no_divisible_encontrado_cb(primos_criba[j], j, i, cb_ctx);
                }
            }
        }
    }
    comun_log_debug("generados %u primos", pd->primos_criba_tam);
    return pd->primos_criba_tam;
}

#endif

#if 1
#define HASH_SET_VALOR_NULO LLONG_MAX
#define HASH_SET_VALOR_BORRADO (LLONG_MAX-1)


struct hashset_st {
    size_t nbits;
    size_t mask;
    
    size_t capacity;
    size_t *items;
    size_t nitems;
    size_t n_deleted_items;
};

typedef struct hashset_st *hashset_t;

struct hashset_itr_st {
    hashset_t set;
    size_t index;
};

typedef struct hashset_itr_st *hashset_itr_t;

bool hashset_iterator_has_next(hashset_itr_t itr)
{
    size_t index;
    
    /* empty or end of the set */
    if (itr->set->nitems == 0 || itr->index == itr->set->capacity )
        return 0;
    
    /* peek to find another entry */
    index = itr->index;
    while(index <= itr->set->capacity -1)
    {
        size_t value = itr->set->items[index];
        if(value != HASH_SET_VALOR_NULO && value != HASH_SET_VALOR_BORRADO)
        {
            return 1;
        }
        index++;
    }
    itr->index=index;
    /* Otherwise */
    return 0;
    
}

size_t hashset_iterator_next(hashset_itr_t itr)
{
    
    if(hashset_iterator_has_next(itr) == 0)
        return -1; /* Can't advance */
    
    itr->index++;
    
    while ((itr->set->items[(itr->index)] == HASH_SET_VALOR_NULO || itr->set->items[(itr->index)]==HASH_SET_VALOR_BORRADO) && itr->index < itr->set->capacity) {
        itr->index++;
    }
    
    return itr->index;
}

hashset_itr_t hashset_iterator(hashset_t set)
{
    hashset_itr_t itr = calloc(1, sizeof(struct hashset_itr_st));
    if (itr == NULL)
        return NULL;
    
    itr->set = set;
    itr->index = 0;
    
    /* advance to the first item if one is present */
    if (set->nitems > 0)
        hashset_iterator_next(itr);
    
    return itr;
}

size_t hashset_iterator_value(hashset_itr_t itr) {
    
    /* Check to verify we're not at a null value, this can happen if an iterator is created
     * before items are added to the set.
     */
    if(itr->set->items[itr->index] == HASH_SET_VALOR_NULO)
    {
        hashset_iterator_next(itr);
    }
    
    return itr->set->items[itr->index];
}



/* create hashset instance */
hashset_t hashset_create(void);

static const unsigned int prime_1 = 73;
static const unsigned int prime_2 = 5009;

void hashset_destroy(hashset_t set)
{
    if (set) {
        free(set->items);
    }
    free(set);
}

hashset_t hashset_create()
{
    hashset_t set = calloc(1, sizeof(struct hashset_st));
    
    if (set == NULL) {
        return NULL;
    }
    set->nbits = 3;
    set->capacity = (size_t)(1 << set->nbits);
    set->mask = set->capacity - 1;
    set->items = calloc(set->capacity, sizeof(size_t));
    for(natural i=0;i<set->capacity;i++){
        set->items[i]=HASH_SET_VALOR_NULO;
    }
    if (set->items == NULL) {
        hashset_destroy(set);
        return NULL;
    }
    set->nitems = 0;
    set->n_deleted_items = 0;
    return set;
}

size_t hashset_num_items(hashset_t set)
{
    return set->nitems;
}


static int hashset_add_member(hashset_t set, void *item)
{
    size_t value = (size_t)item;
    size_t ii;
    
    if (value == HASH_SET_VALOR_NULO || value == HASH_SET_VALOR_BORRADO) {
        return -1;
    }
    
    ii = set->mask & (prime_1 * value);
    
    while (set->items[ii] != HASH_SET_VALOR_NULO && set->items[ii] != HASH_SET_VALOR_BORRADO) {
        if (set->items[ii] == value) {
            return 0;
        } else {
            /* search free slot */
            ii = set->mask & (ii + prime_2);
        }
    }
    set->nitems++;
    if (set->items[ii] == HASH_SET_VALOR_BORRADO) {
        set->n_deleted_items--;
    }
    set->items[ii] = value;
    return 1;
}

static void maybe_rehash(hashset_t set)
{
    size_t *old_items;
    size_t old_capacity, ii;
    
    
    if (set->nitems + set->n_deleted_items >= (double)set->capacity * 0.85) {
        old_items = set->items;
        old_capacity = set->capacity;
        set->nbits++;
        set->capacity = (size_t)(1 << set->nbits);
        set->mask = set->capacity - 1;
        set->items = calloc(set->capacity, sizeof(size_t));
        set->nitems = 0;
        set->n_deleted_items = 0;
        assert(set->items);
        for(natural i=0;i<set->capacity;i++){
            set->items[i]=HASH_SET_VALOR_NULO;
        }
        for (ii = 0; ii < old_capacity; ii++) {
            hashset_add_member(set, (void *)old_items[ii]);
        }
        free(old_items);
    }
}

int hashset_add(hashset_t set, void *item)
{
    int rv = hashset_add_member(set, item);
    maybe_rehash(set);
    return rv;
}

int hashset_remove(hashset_t set, void *item)
{
    size_t value = (size_t)item;
    size_t ii = set->mask & (prime_1 * value);
    
    while (set->items[ii] != HASH_SET_VALOR_NULO) {
        if (set->items[ii] == value) {
            set->items[ii] = HASH_SET_VALOR_BORRADO;
            set->nitems--;
            set->n_deleted_items++;
            return 1;
        } else {
            ii = set->mask & (ii + prime_2);
        }
    }
    return 0;
}

int hashset_is_member(hashset_t set, void *item)
{
    size_t value = (size_t)item;
    size_t ii = set->mask & (prime_1 * value);
    
    while (set->items[ii] != HASH_SET_VALOR_BORRADO) {
        if (set->items[ii] == value) {
            return 1;
        } else {
            ii = set->mask & (ii + prime_2);
        }
    }
    return 0;
}



#endif

#if 1
COMUN_FUNC_STATICA void e216_algoritmo_euclidiano_extendido(entero_largo a,entero_largo b, entero_largo *gp,entero_largo *xp,entero_largo *yp){
    entero_largo x=0,y=1,u=1,v=0;
    while(a){
        entero_largo q=b/a;
        entero_largo r=b%a;
        entero_largo m=x-u*q;
        entero_largo n=y-v*q;
        b=a;
        a=r;
        x=u;
        y=v;
        u=m;
        v=n;
    }
    *gp=b;
    *xp=x;
    *yp=y;
}

COMUN_FUNC_STATICA natural e216_inverso_multiplicativo_modular(entero_largo a,natural m){
    entero_largo r=0;
    entero_largo g=0;
    entero_largo x=0;
    e216_algoritmo_euclidiano_extendido(a, m, (entero_largo *)&g, &x, comun_calloc_local(entero_largo));
    if(g==1){
        r=x%m;
    }
    return (natural)r;
}

COMUN_FUNC_STATICA entero_largo e216_simbolo_jacobi(entero_largo a, entero_largo n){
    assert_timeout(n&1);
    entero_largo t=1;
    if (a < 0 || a > n)
    {
        a = a % n;
        if( a < 0)
        {
            a = -a;
            if( n % 4 == 3){
                t = -t;
            }
        }
    }
    
    while( a != 0){
        while( !(a&1) )
        {
            a >>= 1;
            natural r = n % 8;
            if( r == 3 || r == 5){
                t = -t;
            }
        }
        entero_largo tmp=a;
        a=n;
        n=tmp;
        if(a % 4 == 3 && n % 4 == 3){
            t = -t;
        }
        a %= n;
    }
    if( n == 1){
        return t;
    }
    else{
        return 1;
    }
}

#endif
#if 1
COMUN_FUNC_STATICA entero_largo shanks_tonelli_simbolo_legendre(entero_largo a, entero_largo p){
    entero_largo r=(entero_largo)primalidad_exp_mod(a, ((p - 1) >> 1), p);
    return r;
}
COMUN_FUNC_STATICA entero_largo shanks_tonelli_calcula_z(entero_largo p){
    entero_largo z=0;
    for(z=2;z<p;z++){
        if (p-1==shanks_tonelli_simbolo_legendre(z, p)){
            break;
        }
    }
    return z;
}
COMUN_FUNC_STATICA void shanks_tonelli_conguencia_residuo_cuadratico(entero_largo n,entero_largo p, entero_largo *r1, entero_largo *r2){
    entero_largo p_menos_1=p-1;
    entero_largo S=0;
    while(!(p_menos_1&1)){
        p_menos_1>>=1;
        S++;
    }
    entero_largo Z=shanks_tonelli_calcula_z(p);
    entero_largo Q=p_menos_1;
    entero_largo c = (entero_largo)primalidad_exp_mod(Z, Q, p);
    entero_largo R = (entero_largo)primalidad_exp_mod(n,((Q + 1) >> 1) , p);
    entero_largo t = (entero_largo)primalidad_exp_mod(n, Q, p);
    entero_largo M = S;
    while(t%p!=1){
        entero_largo i=0;
        for(i=1;i<M;i++){
            if(primalidad_exp_mod(t, 1<<i, p)==1){
                break;
            }
        }
        entero_largo b=(entero_largo)primalidad_exp_mod(c, 1 << (M - i - 1), p);
        R=(entero_largo)primalidad_mul_mod(R, b, p);
        c=(entero_largo)primalidad_exp_mod(b, 2, p);
        t=(entero_largo)primalidad_mul_mod(t, c, p);
        M=i;
    }
    *r1=R;
    *r2=p-R;
}
#endif


#define E216_MAX_ABCISA ((natural)1E7)
//#define E216_MAX_ABCISA 101
COMUN_FUNC_STATICA entero_largo e216_f(entero_largo a,entero_largo b, entero_largo c, entero_largo x){
    return a*x*x+b*x+c;
}

COMUN_FUNC_STATICA void e216_core(natural a, natural b, int c, natural *Ns, natural *conteo_acumulado_primos){
    natural x=0;
    hashset_t abcisas_primos_set = hashset_create();
    entero_largo *ordenadas=NULL;
    bool *abcisas_primos=NULL;
    primos_datos *pd = NULL;
    
    pd = calloc(1, sizeof(primos_datos));
    assert_timeout(pd);
    
    ordenadas=calloc(E216_MAX_ABCISA+1, sizeof(entero_largo));
    assert_timeout(ordenadas);
    abcisas_primos=calloc(E216_MAX_ABCISA, sizeof(bool));
    assert_timeout(abcisas_primos);
    
    
    natural primos_tam=primos_criba_criba(PRIMOS_NUM_MAX, NULL, NULL, NULL, NULL, NULL, pd);
    comun_log_debug("primos gen");
    printf("primos gen\n");
    
    for(x=0;x<=E216_MAX_ABCISA;x++){
        entero_largo y=e216_f(a, b, c, x);
        bool primo=falso;
        if(y>0){
            hashset_add(abcisas_primos_set, (void *)(entero_largo)x);
            primo=verdadero;
        }else{
            y=COMUN_VALOR_INVALIDO;
            primo=falso;
        }
        ordenadas[x]=y;
        comun_log_debug("guardando y %lld de x %u", y,x);
        abcisas_primos[x]=primo;
    }
    printf("abcisas guardads \n");
    hashset_itr_t iter = hashset_iterator(abcisas_primos_set);
    
    /*
    while(hashset_iterator_has_next(iter))
    {
        entero_largo x=hashset_iterator_value(iter);
        entero_largo y=ordenadas[x];
        comun_log_debug("aaa de y %lld q viene de x %lld", y,x);
        assert_timeout(y);
        assert_timeout(y!=COMUN_VALOR_INVALIDO);
        hashset_iterator_next(iter);
    }
     */
    
    free(iter);
    entero_largo discriminante=b*b-4*a*c;
    comun_log_debug("discr %lld", discriminante);
    
    for(natural x=0;x<2;x++){
        entero_largo y=e216_f(a, b, c, x);
        natural p=2;
        if(!(y&1)){
            for(entero_largo xi=x;xi<=E216_MAX_ABCISA;xi+=p){
                entero_largo yi=ordenadas[xi];
                if(yi!=p){
                    hashset_remove(abcisas_primos_set, (void *)(entero_largo)xi);
                    abcisas_primos[xi]=falso;
                }
            }
        }
    }
    
    for (natural i = 1; i < primos_tam; i++) {
        natural p = pd->primos_criba[i];
        comun_log_debug("primo %u", p);
        printf("primo %u\n", p);
    setbuf(stdout, NULL);
        entero_largo ys[2]={0};
        natural y_cnt=0;
        entero_largo ls=e216_simbolo_jacobi(discriminante, p);
        comun_log_debug("sim jaco %lld", ls);
        if(ls==-1){
            continue;
        }
        if(!discriminante || !ls){
            ys[y_cnt++]=0;
        }else{
            shanks_tonelli_conguencia_residuo_cuadratico(discriminante, p, ys, ys+1);
            y_cnt=2;
        }
        for(natural j=0;j<y_cnt;j++){
            entero_largo x=e216_inverso_multiplicativo_modular(a<<1, p);
            assert_timeout(x);
            x*=ys[j]-b;
            comun_log_debug("primo %u y %lld x %lld", p,ys[j],x);
            for(entero_largo xi=x;xi<=E216_MAX_ABCISA;xi+=p){
                entero_largo yi=ordenadas[xi];
                if(yi!=p){
                    hashset_remove(abcisas_primos_set, (void *)(entero_largo)xi);
                    abcisas_primos[xi]=falso;
                }
            }
        }
    }
    
    comun_log_debug("esho");
    printf("esho\n");
    
    setbuf(stdout, NULL);
    iter = hashset_iterator(abcisas_primos_set);

    entero_largo *xs_invalidos=calloc(E216_MAX_ABCISA+1, sizeof(entero_largo));
    assert_timeout(xs_invalidos);
    natural xs_invalidos_cnt=0;
    while(hashset_iterator_has_next(iter))
    {
        entero_largo x=hashset_iterator_value(iter);
        entero_largo y=ordenadas[x];
        comun_log_debug("checando primalidad de y %lld q viene de x %lld", y,x);
        assert_timeout(y);
        assert_timeout(y!=COMUN_VALOR_INVALIDO);
        if(!primalidad_es_primo(y,5)){
            comun_log_debug("y %lld q viene de x %lld no es primo", y,x);
            xs_invalidos[xs_invalidos_cnt++]=x;
        }
        hashset_iterator_next(iter);
    }
    
    for(natural i=0;i<xs_invalidos_cnt;i++){
        entero_largo x=xs_invalidos[i];
        hashset_remove(abcisas_primos_set, (void *)(entero_largo)x);
        abcisas_primos[x]=falso;
    }
    
    for(natural i=1;i<=E216_MAX_ABCISA;i++){
        conteo_acumulado_primos[i]=conteo_acumulado_primos[i-1]+(abcisas_primos[i]?1:0);
        comun_log_debug("hasta %u hay %u", i,conteo_acumulado_primos[i]);
    }
    
    free(iter);
    hashset_destroy(abcisas_primos_set);
    free(ordenadas);
    free(abcisas_primos);
    free(pd);
}
/*

static void test_iterating(void)
{
    hashset_t set = hashset_create();
    hashset_itr_t iter = hashset_iterator(set);
    int step;
    
    printf("adding\n");
    hashset_add(set, (void *)"Bob");
    hashset_add(set, (void *)"Steve");
    hashset_add(set, (void *)"Karen");
    hashset_add(set, (void *)"Ellen");
    
    printf("added\n");
    step = 0;
    
    while(hashset_iterator_has_next(iter))
    {
        printf("step %d\n",step);
        printf("value %s\n",(char*)hashset_iterator_value(iter));
        if(step == 0)
        {
            assert(strncmp((char *)hashset_iterator_value(iter), "Bob", 3) == 0);
        }
        if(step == 1)
        {
            assert(strncmp((char *)hashset_iterator_value(iter), "Ellen", 5) == 0);
        }
        if(step == 2)
        {
            assert(strncmp((char *)hashset_iterator_value(iter), "Karen", 5) == 0);
        }
        if(step == 3)
        {
            assert(strncmp((char *)hashset_iterator_value(iter), "Steve", 5) == 0);
        }
        hashset_iterator_next(iter);
        step++;
    }
    assert(hashset_iterator_has_next(iter) == 0);
    assert(hashset_iterator_next(iter) == -1);
}
*/

natural qs[100000]={0};
natural conteo_acumulado_primos[E216_MAX_ABCISA+1]={0};
COMUN_FUNC_STATICA void e126_main(){
    int a=0;
    int b=0;
    int c=0;
    natural q=0;
    // XXX: https://gitlab.eecs.umich.edu/eecs281/wiki/wikis/xcode-file-redirection
#ifdef __APPLE__
    if (getenv("STDIN")) {
        if (!freopen(getenv("STDIN"), "r", stdin)) {
            printf("no se pudo stdin con %s",getenv("STDIN"));
            exit (1);
        }
    }
    if (getenv("STDOUT")) {
        if (!freopen(getenv("STDOUT"), "w", stdout)) {
            printf("no se pudo stdin con %s",getenv("STDOUT"));
            exit (1);
        }
    }
    if (getenv("STDERR")) {
        if (!freopen(getenv("STDERR"), "w", stderr)) {
            printf("no se pudo stdin con %s",getenv("STDERR"));
            exit (1);
        }
    }
#endif

    scanf("%d %d %d\n",&a,&b,&c);
    comun_log_debug("a %d b %d c %d", a,b,c);
    scanf("%u\n",&q);
    comun_log_debug("q %d", q);
    for(natural i=0;i<q;i++){
        scanf("%u\n",qs+i);
    }
    e216_core(a, b, c, qs, conteo_acumulado_primos);
    for(natural i=0;i<q;i++){
        printf("%u\n",conteo_acumulado_primos[qs[i]]);
    }
}

int main(void){
    e126_main();
    return EXIT_SUCCESS;
}
