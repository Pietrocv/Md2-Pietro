#include <stdio.h>
#include <math.h>

// Vetores e variáveis globais usadas em vários cálculos
int restosCalc[100], divs[100], numeradores[100], denominadores[100], g;
int h, zn, alfa, expoente, nBase, reduzidoExpoente, cociente, restoFinal, potIntermediaria, resultado1, resultado2, valorCongruente;

/*
 * Função: calcularMDC
 * --------------------
 * Calcula o Máximo Divisor Comum (MDC) entre dois números usando o Algoritmo de Euclides recursivo.
 */
int calcularMDC(int a, int b) {
    int restoAtual = a % b;
    printf("Executando o MDC: resto de %d por %d = %d\n", a, b, restoAtual);
    if (restoAtual == 0) {
        return b;
    } else {
        return calcularMDC(b, restoAtual);
    }
}

/*
 * Função: calcularInverso
 * -------------------------
 * Encontra o inverso multiplicativo de um número 'valor' módulo 'modulo'
 * utilizando o Algoritmo Estendido de Euclides.
 */
int calcularInverso(int valor, int modulo) {
    int resto = 1, atual = modulo, idx = 0, limite = 0;

    while (resto != 0) {
        resto = valor % atual;
        numeradores[idx] = valor;
        denominadores[idx] = atual;
        restosCalc[idx] = resto;
        divs[idx] = valor / atual;
        valor = atual;
        atual = resto;
        limite = idx;
        idx++;
    }

    int x = 0, y = 1, tempVar;
    // Backtracking para encontrar o inverso
    for (int i = limite - 1; i >= 0; i--) {
        tempVar = x;
        x = y;
        y = tempVar - divs[i] * y;
    }

    return (x % modulo + modulo) % modulo; // Garante que o resultado seja positivo
}

/*
 * Função: multiplicacaoModular
 * ------------------------------
 * Retorna o resultado da multiplicação de 'a' e 'b' módulo 'modulo'.
 */
int multiplicacaoModular(int a, int b, int modulo) {
    printf("\nMultiplicando modularmente: %d vezes %d mod %d\nInverso usado: %d.\n\n", a, b, modulo, b);
    return (a * b) % modulo;
}

/*
 * Função: verificarPrimo
 * ------------------------
 * Verifica se um número é primo usando divisores até a raiz quadrada do número.
 */
int verificarPrimo(int numero) {
    if (numero <= 3) return 1;
    if (numero <= 1 || numero % 2 == 0 || numero % 3 == 0) return 0;
    for (int i = 5; i * i <= numero; i += 6) {
        if (numero % i == 0 || numero % (i + 2) == 0) {
            printf("\n%d e divisivel por %d, entao nao e primo.\n\n", numero, i);
            return 0;
        }
    }
    printf("\n%d e considerado primo, pois nao tem divisores alem de 1 e ele mesmo.\n\n", numero);
    return 1;
}

/*
 * Função: totienteEuler
 * -----------------------
 * Calcula a função totiente de Euler φ(n), ou seja, quantos números menores que n são coprimos de n.
 */
int totienteEuler(int numero) {
    int total = 0;
    for (int i = 1; i <= numero; i++) {
        if (calcularMDC(numero, i) == 1) {
            total++;
            printf("Coprimo encontrado: mdc(%d, %d) = 1\n", numero, i);
        }
    }
    printf("\nQuantidade de coprimos com %d: %d\n", numero, total);
    return total;
}

/*
 * Função: exponenciacaoRapida
 * -----------------------------
 * Calcula (base^expoente) % modulo de forma eficiente usando exponenciação rápida (também conhecida como Square-and-Multiply).
 */
int exponenciacaoRapida(int base, int expoente, int modulo) {
    int resultado = 1;
    base = base % modulo;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % modulo;
        expoente = expoente / 2;
        base = (base * base) % modulo;
    }
    return resultado;
}

/*
 * Função: main
 * --------------
 * Executa uma sequência de cálculos modulares:
 * 1. Recebe entradas do usuário para resolver uma congruência.
 * 2. Calcula inverso modular.
 * 3. Aplica Fermat ou Euler para reduzir o expoente.
 * 4. Resolve a exponenciação modular.
 */
int main() {
    printf("Informe os dados no formato:\n");
    printf("h = g^x (mod zn)\nE depois: a^x mod nBase\n\n");

    // Leitura das variáveis principais
    printf("Digite h: ");
    scanf("%d", &h);

    printf("Digite g: ");
    scanf("%d", &g);

    printf("Digite zn: ");
    scanf("%d", &zn);

    printf("Digite o valor de x: ");
    scanf("%d", &expoente);

    printf("Digite nBase: ");
    scanf("%d", &nBase);
    printf("\n");

    // Verifica se o inverso existe
    if (calcularMDC(g, zn) != 1) {
        printf("Nao ha inverso, pois mdc(%d, %d) = %d\n", g, zn, calcularMDC(g, zn));
        return 0;
    }

    int inverso = calcularInverso(g, zn);
    printf("Inverso modular de %d em relacao a %d: %d\n", g, zn, inverso);

    alfa = multiplicacaoModular(h, inverso, zn);

    // Determina qual teorema aplicar para reduzir o expoente
    if (calcularMDC(alfa, nBase) == 1) {
        if (verificarPrimo(nBase)) {
            printf("Aplicando o Pequeno Teorema de Fermat.\n");
            reduzidoExpoente = nBase - 1;
        } else {
            printf("Aplicando o Teorema de Euler.\n");
            reduzidoExpoente = totienteEuler(nBase);
        }
    } else {
        printf("Nao e possivel aplicar os teoremas: %d e %d nao sao coprimos.\n", alfa, nBase);
        return 0;
    }

    // Redução do expoente via propriedades modulares
    cociente = expoente / reduzidoExpoente;
    restoFinal = expoente % reduzidoExpoente;

    printf("\nReescrevendo a potencia modular:\n");
    printf("%d^%d ≡ ((%d^%d)^%d * %d^%d) mod %d\n", alfa, expoente, alfa, reduzidoExpoente, cociente, alfa, restoFinal, nBase);

    // Cálculo final da potência modular
    potIntermediaria = exponenciacaoRapida(alfa, reduzidoExpoente, nBase);
    resultado1 = exponenciacaoRapida(potIntermediaria, cociente, nBase);
    resultado2 = exponenciacaoRapida(alfa, restoFinal, nBase);

    valorCongruente = (resultado1 * resultado2) % nBase;

    printf("\nValor congruente final: %d\n", valorCongruente);
    return valorCongruente;
}
