# MC7723-2
#####Titouan THIBAUD - RA : 180879

##Atividade

Eu escolhi a segunda opção de exercício : Simular 4 programas com um nível de cache e achar a melhor configuração (L1 de instruções e L1 de dados). .   
Escolhi os seguinte programas : swim_m2b, lucas_f2b, Vortex_m2b, gcc_f2b.   

Como foi aconselhado no sujeito, eu reduzi o tamanho dos traces de 101 para 20, usando um comando desse tipo :    
`dineroIV -informat s -trname vortex_m2b -maxtrace 20 -l1-isize 16K -l1-dsize 16K -l1-ibsize 32 -l1-dbsize 32`

###Processo 
O objetivo desse exercicio era achar a melhor configuração de cache para cada programa analizado.   
Para achar essa informação, usamos o software Dinero com traces de execução já coletados.   

Primeiro rodei o comando com os tamanhos de blocs fixos, para encontrar o melhor tamanho de cache.  
As caches de instruções e de dados são independentes, não precisa fixar um para analisar o outro.    

Em muitos casos, quanto maior o tamanho da cache, menor o cache rate. Isso é justamente o criterio que permite definir qual é a configuração ótima : é a configugração em que o rate miss é minimo. 
  
Só que tem que tomar em conta que uma cache muito grande é muito cara. Por isso, com informações que eu achei na literatura, decidi não usar tamanho de cache maior que 128K.
  
Uma vez o tamanho da cache encontrado, a gente pode procurar o tamanho de bloco ótimo.  
A gente fixa o tamanho da cache e varia o tamanho do bloco. Aumentendo o tamanho do bloco, o mich rate vai diminuir, até chegar num minimo, a partir do qual ele vai aumentar. 
O tamanho de bloco com qual temos o menor miss rate corresponde á configuração ótima.

###Resultados

####Swim_m2b

![resultados](https://github.com/titooan/MC723/blob/master/exercicio2/swim/table.png "resultados")
#####Instruction cache
No caso do programa Swim, podemos perceber que a configuração da cache de instruções não tem muita importancia, o miss rate é sempre muito pequeno. 
É possivel ter um miss rate de 0% (na verdade tem alguns miss mas a proporção é tão pequena que podemos dizer que é 0), com uma cache de 4K com blocos de 128.
Também é possivel ter o mesmo resultado com uma cache de 8K e blocos de 32, o uma cache de tamanho maior ou egual a 16K e qualquer tamanho de bloco. 

(Nesse caso não precisa de grafos)

#####Data cache
![resultados](https://github.com/titooan/MC723/blob/master/exercicio2/swim/dsize.png "resultados")
![resultados](https://github.com/titooan/MC723/blob/master/exercicio2/swim/dbsize.png "resultados")

Com esse grafos a gente pode ver que quanto melhor o tamanho da cache, melhor o restultado. 
Escolhi uma cache de 128K, e experimentei varios tamanhos de bloco para descobrir o melhor.

#####Melhor configuração
**Cache de Instruções :**
* Tamanho da cache : 4K
* Tamanho do bloco : 128
* 
**Cache de Dados :**
* Tamanho da cache : 128K
* Tamanho do bloco : 512
