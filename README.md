# Integrantes do grupo:
- Daniel Kabadayan Dias (TIA: 42110637, Turma: 04N11)

# O Problema do Jantar dos Filósofos
O problema do jantar dos filósofos é um problema clássico de sincronização que foi proposto pelo matemático Edsger Dijkstra em 1965. O problema foi concebido para ilustrar a necessidade de sincronização adequada para evitar impasses (deadlocks).

O problema descreve cinco filósofos que estão sentados em uma mesa redonda, cada um com um prato de comida e um garfo à esquerda e à direita. Entre cada par de filósofos há um garfo. Os filósofos passam o tempo pensando e comendo, mas só podem comer se estiverem segurando um garfo em cada mão. O problema é como garantir que cada filósofo tenha um garfo para comer sem que ocorram impasses.

# Explicação da Resolução
No programa, o problema de comunicação entre processos é resolvido usando pipes. O programa cria um pipe para cada filósofo, e cada pipe é usado para que um filósofo se comunique com os seus vizinhos à esquerda e à direita.

Quando um filósofo está com fome e tenta pegar os garfos, ele envia uma mensagem para o seu vizinho à esquerda dizendo que ele está faminto e espera uma resposta. Se o vizinho à direita estiver comendo, ele envia uma mensagem de volta dizendo que ele não pode entregar o garfo agora. Caso contrário, o filósofo recebe o garfo da direita e envia uma mensagem para o vizinho à esquerda. Se o vizinho à esquerda estiver comendo, ele envia uma mensagem de volta dizendo que ele não pode entregar o garfo agora. Ainda, caso contrário, o filósofo recebe o garfo da esquerda e pode começar a comer.

Por fim, quando um filósofo termina de comer, ele devolve os garfos aos seus vizinhos, enviando uma mensagem para cada um deles. As mensagens são trocadas usando os pipes.

# Arquivos
- DiningPhilosophers.c

# Bibliotecas Utilizadas
- <stdio.h>
- <stdlib.h>
- <stdbool.h>
- <unistd.h>
- <sys/wait.h>

# Instruções para a Compilação do Programa
Para compilar o arquivo "DiningPhilosophers.c" deste repositório, basta acessar o diretório que contém o arquivo utilizando o comando "cd" do CMD do Windows e digitar o seguinte código: "gcc <nome_do_arquivo.c> -o <DiningPhilosophers>", caso o seu compilador seja o GCC.

# Comprovação dos Resultados Propostos
Para comprovara os resultados do programa criado, basta compilá-lo conforme as instruções do tópico acima e, em sequencia, acessar o diretório onde se localiza o executável gerado utilizando o comando "cd" do CMD do Windows e, em seguida, digitar o nome do executável ("./DiningPhilosophers" - caso seu sistema seja Linux/MacOS).

Desta maneira, o programa será inicializado no próprio terminal e estará disponível para uso e teste.
