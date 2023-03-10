# matriz_recursividade
 EP (exercício-programa) da matéria de análise de algoritmos utilizando a linguagem C
 
Desenvolvi um programa que implementa um algoritmo
com recursão e divisão e conquista para efetuar a contagem de quadrantes
maximais totalmente da cor branca e totalmente da cor preta em uma imagem
digital em preto e branco.

O intuito é praticar o conceito de divisão e conquista, utilizando a recursividade.

Para isso, gero um arquivo txt informando quantos quadrados de diversas dimensões possuem na informada matriz


O arquivo de saída contém em cada linha:
➔ campo1: as dimensões do quadrante, na forma “NxN” (x minúsculo, sem
espaços), ordenado pela dimensão decrescente;
➔ <espaço>
➔ campo2: número de quadrantes maximais daquela dimensão (tamanho)
totalmente branco;
➔ <espaço>
➔ campo3: número de quadrantes maximais daquela dimensão (tamanho)
totalmente preto.




Compilar:
ep1_13728941.c -o ep1_13728941

e quando for executar:

.\ep1_13728941 "n" "entrada.txt"

onde "n" seria a ordem da matriz (exemplo: se você digitar 4, será uma matriz 4x4)
e "entrada.txt" o arquivo txt

Obrigado
