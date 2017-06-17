# Simulador de memória Cache

Esse projeto tem como objetivo representar uma simulação entre uma **memória cache L1** e a **memória principal**.
Determinadas ações no procesador requerem informações (intruções ou dados) que estão armazenadas na memória. 

```
Entenda memória como uma hierarquia de memórias e podemos imaginar elas dispostas uma 
sobre a outra como uma pirâmide, onde quanto mais alta, mais rápida e mais cara ela será. 
Nessa hierarquia, a cache está acima da memória principal, o que torna evidente sua velocidade 
maior diante da outra.
```
Os passos são os seguintes:

1. O processador requisita a informação para a memória cache;
2. Se estiver alocada, passa a informação para o processador, caso contrário, procura na memória principal;
  * Nesse caso estamos usando apenas a *cache L1*. Mas se houvesse a L2 ou L3, os passos seriam análogos, seguiriamos o fluxo da hierarquia até atingir a memória principal.
3. Se estiver na memória principal, aloca a informação na memória cache e repete o passo **1**. Caso não esteja alocado, estará nos dispositivos de E/S (disco magnético, por exemplo), e o acesso é controlado por software (sistema operacional). *[esse processo de encontrar nos dispositivos de E/S não é realizado pelo simulador!]*

+ Essas alocações geram substituições de outras informações, e tudo isso não é feito de qualquer forma. Existem maneiras de se alocar (descobrir onde a informação vai entrar *[mapeamento]*) e substituir (qual informação vai sair *[algoritmo de substituição]*) alguma informação na memória cache.

Quanto o mapeamento, existem os seguintes:

| Mapeamento               |
|:------------------------:|
| Direto                   |
| Totalmente associativa   |
| Associativa por conjunto |

E quanto aos algoritmos de substituição:

| Algoritmos   |
|:------------:|
| Aleatório    |
| LFU          |
| LRU          |
| FIFO         |

Além disse, também há o tipo de escrita. Que será fundamental para definir a forma de escrever informações nos endereços de memória informado:

| Escrita        |
|:--------------:|
[| WRITE-BACK     |](https://en.wikipedia.org/wiki/Cache_(computing)#WRITE-BACK)
| WRITE-THROUGH  |

## Começando

Assim que adquirir o repositório do projeto, você deverá acessar a pasta raiz do mesmo e executar o arquivo *compile.sh* para compilar. Um arquivo binário com o nome *cache* será gerado no diretório *build*. Então, ainda da pasta raiz, digite o seguinte comando:

```
$ ./build/cache data/config.txt
```

**MUITA ATENÇÃO** nessa hora, você deverá passar um arquivo *config.txt* que contém todas as informações necessárias para que o simulador possa funcionar. Tais informações como:
  * Tamanho dos blocos;
  * Quantidade de linhas da cache;
  * Quantidade de blocos na memória principal;
  * Tipo do mapeamento escolhido *[1,3]*;
  * Número de conjuntos na cache (essa informação será utilizada apenas se o tipo de mapeamento for associativo por conjunto, mas por padrão, é obrigatório que esse dado esteja incluso no arquivo);
  * Tipo de algoritmo de substituição *[1,4]*;
  * Tipo de escrita escolhida *[1,2]*.

**A sequencia das informações deve ser dada nessa EXATA sequência no arquivo, sendo um número para cada.** Veja o [arquivo posto como exemplo.](https://github.com/FranklinMatheus/cache-simulator/blob/master/data/config.dat)
*[OBS: algumas informações podem ser corrigidas durante a execução do simulador caso sejam inválidas!]*


## Utilizando

Assim que executar, você irá se deparar com um diálogo onde poderá interagir com o simulador por meio de comandos. Esses comandos são os seguintes:
 * **read [address]**: esse comando possui um parâmetro *address* que corresponde ao endereço de memória que você quer ler. Ele retornará HIT se o endereço estiver alocado na cache, ou MISS se não estiver. Nesse último caso, se ela estiver na memória principal, então será alocado na cache de acordo com o mapeamento e o algoritmo de substituição;
 * **write [address] [content]**: esse comando possui dois parâmetros: *content* que é o conteúdo que você quer escrever e  *address* que é o endereço de memória onde o conteúdo será escrito. Ele retornará HIT se o endereço estiver alocado na cache e escreve normalmente de acordo com o método de escrita, ou MISS se não estiver. Nesse último caso, se ela estiver na memória principal, então será alocado na cache de acordo com o mapeamento e o algoritmo de substituição e só assim o conteúdo será escrito no endereço, claro, de acordo com o método de escrita;
 * **show**: mostra na tela o estado atual da cache e da memória principal;
 * **help**: informa os comandos disponíveis que o usuário pode inserir;
 * **details**: retorna todas as informações que foram definidas pelas usuário quanto ao tamanho do bloco, quantidade de linhas na cache e blocos na memória, tipo do mapeamento, número de conjuntos, tipo do algoritmo de substituição e escrita.
 * **quit**: sai do simulador.

## Autor

* **Franklin Matheus da Costa Lima** - Aluno do Bacharelado em Tecnologia da Informação na Universidade Federal do Rio Grande do Norte (UFRN) - [Franklin Matheus](https://github.com/FranklinMatheus)
