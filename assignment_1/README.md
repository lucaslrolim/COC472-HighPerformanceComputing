# Relatório 2 - Computação de Alto Desempenho
**Aluno:** Lucas Lopes Rolim 
**Disciplina:** Computação de Alto Desempenho  - COC472

----------
## Contextualização sobre perfilamento e Gprof

O Gprof é uma ferramenta de perfilamento do GNU que faz parte do conjunto de ferramentas binárias GNU Binutils. Ela permite a análise dinâmica do desempenho de códigos binários, identificando trechos de códigos a serem executados e seu desempenho.

A motivação para utilizar esse tipo de ferramenta é analisar a quantidade de métodos existentes no código, bem como a porcentagem de chamadas para cada método e o tempo despendido em cada um. A partir dessas analises é possível extrair a informação necessária para realizar um trabalho de otimização no código, visando melhorar a performance.

## Metodologia

O programa que definimos para realizar o perfilamento é um código desenvolvido na disciplina de Teoria dos Grafos, o qual utilizaremos para calcular o diâmetro *(distância máxima entre dois vértices)* de um grafo de 10 mil arestas. Nosso programa irá consumir a informação sobre os vértices de um arquivo *.txt* e depois exibir na tela o resultado e o tempo de execução do programa.

Para habilitar o Gprof vamos utilizar a flag `**-pg**` no nosso comando de compilação:


    g++ -pg -o main.out graphTools.cpp

Em seguida vamos utilizar o comando `**gprof**` para gerar o relatório de perfilamento. Com o objetivo de facilitar a leitura, iremos salvar esse relatório em um arquivo *.txt*. Ainda, poderíamos usar a flag `**-b**` para omitir as explicações sobre o significado das colunas do relatório gerado, mas optamos por deixá-las para fins didáticos.


    gprof ./main.out gmon.out > report.txt

No relatório gerado temos duas tabelas: **flat profile** e **call graph**. A tabela flat profile ****mostra informações sobre o tempo que o programa gastou em cada método ou rotina e quantas vezes aquela rotina foi executada. A tabela call graph, por sua vez, mostra informações no formato de um grafo direcionado acíclico. Para maiores informações sobre grafos direcionados acíclicos.

O grafo da call graph mostra, para cada método, as seguintes informações: quais métodos o invocaram, quais métodos invocou e quantas vezes foi executado. Há ainda uma estimativa de quanto tempo foi gasto nas sub rotinas de cada um desses métodos.

Por fim, iremos utilizar a biblioteca Gprof2Dot para criar uma representação gráfica do nosso relatório de perfilagem.


    ./gprof2dot.py report.txt > report.dot
    dot -Tpng -o profile.png report.dot

O resultado é a seguinte imagem:

![](https://d2mxuefqeaa7sj.cloudfront.net/s_D57B4A963495E1418B78FFE76595E054CF5545840BB3103950368B5B18C7ADA9_1524688211881_profile.png)



## Resultados e conclusões

Foram identificados 329 métodos em nosso programa, sendo boa parte deles integrantes das bibliotecas vector, queue e deque. Ainda, apenas 2% do tempo de execução foi usado para inicializar os dados,  tarefa que consiste em ler um *.txt* com a informação dos 10 mil vértices e inserir essa informação em uma classe de vetor de adjacência.

O maior tempo de execução geral foi dedicado a realização de operações com os vetores de informação dos vértices. As iterações, inserções e remoções de valor em estruturas do tipo **vector** consumiram cerca de 38% do tempo do programa. Isso é um indicativo que nosso programa pode melhorar drasticamente se conseguirmos realizar algumas operações que fazemos com a estrutura de dados da biblioteca vector do C++ em uma estrutura mais simples e rápida, como um array por exemplo. Além disso, mostra que uma possível otimização que não altera a estrutura do código básica seria investigar se existe uma implementação mais eficiente da estrutura de vetores no C++. Ainda, uma última opção seria analisar nosso código tentando imaginar formas de iterar menos vezes em nossas estruturas de vetor.

O método mais chamado, e que consequentemente também demandou mais tempo, foi o `getNeightbor()`, consumindo sozinho cerca de 20.27% do tempo de execução.  Isso não é de surpreender, uma vez que é necessário calcular a distância entre cada par possível de vértices e para isso se torna necessário identificar seus vizinhos. Essa função é chamada dentro dos principais, e maiores, loops do programa. As duas opções de otimização mais claras são otimizar a função getNeightbor() em si ou reduzir sua utilização dentro de loops, salvando a informação sobre os vizinhos de um vértice de uma outra forma *(até mesmo em um .txt pré processado)*.

Por último, uma otimização final que identificamos seria reduzir o número de chamadas da função `**getDegree(v)**`. Apesar dessa função ser extremamente simples, consistindo apenas na consulta em uma posição do array ¨degrees¨, ela consone 11% do tempo de processamento. O problema nesse caso é que essa função é usada como condicional em diversos ¨if`s¨ dentro de loops. Conseguir realizar esses desvios condiciais de outra forma seria um caminho interessante para a otimização do desempenho do código. 

