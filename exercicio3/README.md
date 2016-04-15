# MC7723-3
#####Titouan THIBAUD - RA : 180879

##Atividade

Depois de ter configurado as ferramentas, a gente avaliou o desempenho de 3 programas.
Como os programas são executados num simulador, o tempo de execução não necesariamente faz sentido para avaliar o desempenho deles. 
A gente achou outra medida : o numero de ciclos executados. 

Para calcular ele, uma ferramenta nos permite medir o numero de execução de cada tipo de instrução. 
Com a informação da seguinte tablela, a gente consegue calcular o numero total de ciclos necesarios para executar o programa :

|Categoria   | CPI Médio   |
|---|---|
| Acesso à memória  |  	10 | 
|  Controle (branch/jump) |  3 |   
|  Outras | 1  | 

Eu coloquei os resultados obtidos com o simulador nessa planilha :
<https://docs.google.com/spreadsheets/d/193f8sUFWtHERxrQR6SQRT2dqKh0t1GnIV4-OFAxkxAw/edit?usp=sharing>    

Aqui estão meus resultados : 

|Programma  | Numero de ciclos   |
|---|---|
| Dijkstra small |  196784071 | 
| FTT small | 1878273201 |   
|  bitcount large | 1024884155| 
