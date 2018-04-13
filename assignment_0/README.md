# Trabalho 0 - Computação de Alto Desempenho

**Aluno:** Lucas Lopes Rolim
**Disciplina:** Computação de Alto Desempenho COC472

----------
## Contextualização

O objetivo desse trabalho é analisar a diferença em como a operação de multiplicação de uma matriz quadrada por um vetor se comporta conforme vamos alterando o tamanho dessa matriz e do referido vetor. Além disso, vamos investigar também as diferenças entre a implementação dessa operação na linguagem C e na linguagem FORTRAN, bem como as diferenças de tempo de processamento entre elas.


## Metodologia

Foi criado um arquivo `matrix-multiplication` tanto na linguagem ANSI C quanto na linguagem FORTRAN 90. Ambos os arquivos utilizaram apenas funções básicas das linguagens e bibliotecas padrões.

Para medir o tempo das operações foi utilizado, em ambos os casos, o tempo do ciclo de clock da máquina. É conhecido que isso pode gerar alguns problemas de divergência com o tempo real, entretanto o método mais prático e estável encontrado.  Foi experimentado usar a função `gettimeofday()` da linguagem C para medir o tempo real transcorrido, mas a mesma apresentou alguns bugs e contra recomendações de uso em fóruns da internet.

Outro aspecto que vale ser mencionado é que a partir do N = 25600 o FOTRAN apresentava erro de alocação de memória. Para resolver, foi necessário usar o argumento `-mcmodel=large` ao compilar. Esse comando aumenta a quantidade de memória que podemos alocar em nosso array para um valor maior que 2GB, que é o padrão. 

Ambos os arquivos se encontram no repositório: https://github.com/lucaslrolim/COC472-HighPerformanceComputing

## Resultados
| Tamanho | Implementação em C | Implementação Fotran (baseado em colunas) | Implementação Fotran (baseado em linhas) |
| ------- | ------------------ | ----------------------------------------- | ---------------------------------------- |
| 100     | 0,00024            | 0                                         | 0                                        |
| 200     | 0,000983           | 0                                         | 0                                        |
| 400     | 0,001123           | 0,001                                     | 0,001                                    |
| 800     | 0,0059720          | 0,003                                     | 0,003                                    |
| 1600    | 0,0112540          | 0,009                                     | 0,013                                    |
| 3200    | 0,0442630          | 0,037                                     | 0,123                                    |
| 6400    | 0,1771060          | 0,148                                     | 0,669                                    |
| 12800   | 0,699697           | 0,556                                     | 3,725                                    |
| 25600   | 2,614786           | 2,00500                                   | 17,169                                   |
| 51200   | 52,860985          | 47                                        | 425,781                                  |



![](https://d2mxuefqeaa7sj.cloudfront.net/s_DFCA5D0F5A5ADA0159F8704C3DB7275FB3CD9C21A13A86EDD5AE6CC560FA2F9C_1523589659053_graph1.png)



![](https://d2mxuefqeaa7sj.cloudfront.net/s_DFCA5D0F5A5ADA0159F8704C3DB7275FB3CD9C21A13A86EDD5AE6CC560FA2F9C_1523589665331_graph2.png)



## Conclusões

Ao observar os gráficos e as medições de tempo, somos capazes de notar que os tempos estão, de maneira geral, de acordo com o resultado teórico esperado. Os tempos crescem quadraticamente com N, ou seja, a cada linha aumentam em um fator de aproximadamente 4. A exceção foi a implementação FORTRAN baseada em linhas, que apresentou um crescimento anormal para valores de N muito altos.

Ambas as linguagem apresentaram comportamentos semelhantes no que se refere a proporção de crescimento. A maior diferença foi entre adotar uma abordagem orientada a seleção de linhas ou a seleção de colunas no FOTRAN. Percebemos que, nessa linguagem, obtemos um desempenho muito superior se selecionarmos uma coluna por vez e multiplicarmos suas linhas pelo elemento apropriado do vetor X do que se selecionarmos uma linha por vez e multiplicarmos os elementos de sua coluna.

Acreditamos que a diferença entre selecionar linhas ou colunas, que acontece no FORTRAN e não no ANSI C, deve se dar pela forma que os elementos são armazenados em arrays. Infelizmente, não foi encontrada nenhuma menção sobre esse aspecto na documentação oficial do FORTRAN 90.




