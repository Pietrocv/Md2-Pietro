📎 Autor
Nome: Pietro Calegari Visentin
Matrícula: 232014754
Curso: Engenharia de Software 

# 🔐 Verificação Modular com Teoremas Aritméticos

## 📚 Descrição

Este projeto implementa, em linguagem **C**, uma simulação de sistema de segurança baseado em **congruência modular**, utilizando conceitos fundamentais da Teoria dos Números:

- Divisão modular
- Primalidade e coprimalidade
- Pequeno Teorema de Fermat
- Teorema de Euler
- Exponenciação modular eficiente
- Função totiente de Euler φ(n)

O programa realiza a validação de acessos por meio do cálculo da expressão modular:


Sendo que a base `a` é definida pela **divisão modular**:


## 🧮 Etapas do Algoritmo

1. **Entrada do usuário:**
   - Três inteiros positivos `H`, `G`, `Zn`
   - Expoente `x`
   - Módulo `n1`

2. **Verificação de coprimalidade entre G e Zn** usando o **Algoritmo de Euclides**.

3. **Cálculo do inverso de G em Zn**, via algoritmo de Euclides estendido.

4. **Divisão modular**: `a = H * G⁻¹ mod Zn`.

5. **Verificação se `a` e `n1` são coprimos**.

6. **Teste de primalidade** em `n1`.

7. Se `n1` for primo, aplicar **Fermat**: `x1 = n1 - 1`

8. Caso contrário, aplicar o **Teorema de Euler**:
   - Calcular φ(n1) com base em **fatores primos** (sem bibliotecas externas).

9. **Decomposição de expoente**: `x = x1 * q + r`

10. **Reescrita da potência modular**:


11. **Cálculos finais com exponenciação modular eficiente** e impressão do **resultado da congruência**.

## 🖥️ Execução

### 🔧 Requisitos

- Compilador C (GCC, Clang, MinGW, etc.)
- Ambiente como:
  - [OneCompiler (C)](https://onecompiler.com/c)
  - Code::Blocks, Dev-C++, ou terminal

### ▶️ Como compilar

No terminal:

```bash
gcc main.c -o modulo
./modulo
