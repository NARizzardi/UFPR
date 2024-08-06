Nicolas Andre Rizzardi - GRR20206152

### Estratégias
A estratégia adotada foi começar pelas coisas mais simples, então fiz primeiro o `setup_brk`, seguido do `dismiss_brk` e uma versão básica do `memory_free`.

O que mais senti dificuldade foi abstrair o suficiente pra saber como percorrer a memória, como organizar tudo de forma clara e coesa.

Para fazer a implementação do `memory_alloc`, segui também começando pelo simples, fiz uma versão inicial de alocação com a heap não inicializada, depois fiz a expansão da heap.

Percebi que a lógica era exatamente a mesma então reduzi a heap não inicializada junto da expansão da heap, o que deu certo logo de começo.
O passo seguinte foi alocar memória num espaço que não houvesse repartição do bloco. Fechando então fazendo a alocação com repartição.

Com tudo isso funcionando foquei no tratamento de erros da liberação de memória, fazendo primeiro a verificação para saber se o endereço passado estava dentro do espaço delimitado pela heap. Fechando o trabalho com uma verificação se o endereço realmente é o de um bloco de memória.

**O `memory_free` necessita que o endereço passado seja o começo da seção de dados, se for o começo da header ele vai alegar erro.**

### Sobre o código
Para esse trabalho utilizei 16 bytes de header e todas as operações com quadword para manter tudo padronizado e em potência de 2.

Toda função possui um cabeçalho indicando quais os registradores usados, tentando manter um padrão de quais os registradores são usados para que em cada função

Sobre a escolha dos registradores, utlizei eles com amplitude visando separar bem qual está sendo usado para que, para evitar confusão na hora de implementar.

Além disso como assembly não é tão legível tentei colocar um comentário sucinto à direita para não atrapalhar a leitura do código e para que seja possível acompanhar o que está acontecendo linha a linha

