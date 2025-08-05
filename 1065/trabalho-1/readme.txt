nar20 - GRR20206152 bpr21 - GRR20214329
O trabalho foi implementado utilizando a estrutura de lista de adjacências por criarmos vértices e arestas sequencialmente, ao invés de receber tudo pronto.
Além disso a maior parte dos algoritmos são implementados mais facilmente com listas (guardar informações como grau do vertice, qual componente ele pertence).

Do jeito que o programa foi feito são aceitos no máximo 100 linhas de entrada entre vértices com e sem arestas.

A struct utilizada foi um grafo g com uma lista de struct vertices onde cada vertice é a cabeça da sua própria lista de struct adjacências.
Dentro da struct grafo tem informações de nome, lista de vértices, quantidade de vértices, arestas e componentes.
Dentro da struct vértice tem informações de grau, nome do vértice, ponteiro pra cabeça da lista de adjacência, cor (para saber se é bipartido), estado e pai (para busca em grafo), componente (para buscar apenas dentro do componente).
Dentro da struct adjacência apenas o peso da aresta e um ponteiro para o próximo item da lista.

Retornar o nome do grafo é imediato pela definição da struct do grafo.
Contar vértices e arestas é imediato pela definição da struct do grafo.
Contar componentes é imediato pela struct mas para organizar quais os componentes e seus vértices e arestas é utilizado um algoritmo de Busca em Largura.
Para saber se o vértice é bipartido foi utilizado um algoritmo de 2-colorir, onde se ele não consegue 2-colorir o grafo então retorna que o grafo não é bipartido.
Para calcular o diâmetro dos componentes foi utilizado o algoritmo de Djikstra para cada vértice do componente. Salvando apenas o maior de cada componente.
Para calcular as arestas e vértices de corte foi utilizado o algoritmo de Busca em Profundidade.

Destroi grafo está completo, ao rodar com valgrind --leak-check=full não foi apontado nenhum vazamento de memória.

Ao rodar um diff dos exemplos.out com os resultados obtidos por ./teste < exemplo.in, não foi apontado nenhuma diferença.

Ao compicar rodando mas máquinas mumm, macalan, cpu1 e i22 não houve um warning.