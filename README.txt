O programa pode ser compilado com o comando:

gcc ./src/* -o atari_binary_tree.out

A execução do arquivo de saída pode ser realizada com argumentos opcionais, sendo o primeiro argumento o path para o arquivo com as informações extraídas da tabela da wikipédia e o segundo argumento o path para o arquivo contendo os links das imagens dos jogos.
Portanto, o código de execução usando o executável criado pelo comando acima seria:

./atari_binary_tree.out file.csv image_links.csv

Alguns jogos já possuem imagens listadas no arquivo csv que se encontram na pasta images.