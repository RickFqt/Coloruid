# Coloruid
Heurística utilizada para resolver os níveis de Coloruid 2.

Todos os casos de teste para o jogo Coloruid2 podem ser encontrados na pasta de niveis. Para cada nível, foi selecionada uma numeração para cada área colorida e, com base nisso, foi criado um arquivo de entrada para o algoritmo. A numeração das áreas dos níveis utilizados pode ser encontrada em "niveis/imagens", e seus respectivos arquivos de entrada em "niveis/entradas".

Para rodar o algoritmo em algum caso de teste, primeiro compile utilizando o comando:

`g++ coloruid.cpp`

Em seguida, execute com:

`<caminho_para_executavel> <caminho_para_entrada>`

Exemplo:

`g++ coloruid.cpp`

`./a.out niveis/entrada/a.txt`
