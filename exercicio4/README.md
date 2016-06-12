# Exercício 4 : Plataformas e Periféricos
#####Titouan THIBAUD - RA : 180879

##Implementação do periférico básico
Para começar a atividade, modificamos o codigo da plataforma para criar um periferico que implemente a funcionalidade load-and-increment.

Por isso, modifiquei o arquivo `ac_tlm_preipheral.cpp` para ter o seguinte comportamento : toda leitura retorna o valor armazenado e muda o valor para 1. 
Toda escrita grava o valor solicitado.

Aqui está o codigo :
```C++
uint32_t v = 0;

/** Internal Write
  * Note: Always write 32 bits
  * @param a is the address to write
  * @param d id the data being write
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status ac_tlm_peripheral::writem( const uint32_t &a , const uint32_t &d )
{
  v = d;
  //cout << "addr: " <<  std::hex  << a << " data: " << d << endl;
  
  return SUCCESS;
}

/** Internal Read
  * Note: Always read 32 bits
  * @param a is the address to read
  * @param d id the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  d = v;
  v = 1;
  return SUCCESS;
}

```

O periférico assim implementado pode ser usado para criar um lock, muito útil num programa multiprocessador.

Para testar o periférico, podemos usar o codigo seguinte :
```C++
#include<stdio.h>

main()
{
	volatile int* address = (int*) (100*1024*1024);
	*address = 0;

	printf("%d\n", *address); 
	printf("%d\n", *address); 
	printf("%d\n", *address); 
}
```

Podemos assim verificar que o valor escrito na tela é o valor armazenado na primeira linha, e depois o valor "1".

##Plataforma multicore

Agora temos que modificar o arquivo `main.cpp` da plataforma para conetar dois processadores no roteador. 
Aqui está o novo codigo : 

```C++
int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  mips mips_proc1("mips1");

  //ADDED
  mips mips_proc2("mips2");


  ac_tlm_mem mem("mem", 100*1024*1024);
  ac_tlm_router router("router");
  ac_tlm_peripheral peripheral("peripheral"); 

  router.MEM_port(mem.target_export);
  router.PERIPHERAL_port(peripheral.target_export); 

  mips_proc1.DM_port(router.target_export);

  //ADDED
  mips_proc2.DM_port(router.target_export);


#ifdef AC_DEBUG
  ac_trace("mips_proc1.trace");
#endif 

  //ADDED
  char *av1[3];
  char ac1 = ac;
  char *av2[3];
  int ac2 = ac;
 
  memcpy(av1, av, ac * sizeof *av);
  memcpy(av2, av, ac * sizeof *av);

  mips_proc1.init(ac1, av1);
  mips_proc2.init(ac2, av2);
  mips_proc1.set_instr_batch_size(1);
  mips_proc2.set_instr_batch_size(1);

  cerr << endl;

  sc_start();

  mips_proc1.PrintStat();
  mips_proc2.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  ac_stats_base::print_all_stats(std::cerr);
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return mips_proc1.ac_exit_status;
}
```

Podemos depois usar essa plataforma para executar una aplicação que faça uso efetivo da plataforma multicore. 
Para gerenciar o controle de concorrência, implementamos as seguinte funções : 

```C++
#define LOCK_ADDRESS (100*1024*1024);
volatile int *gLock = ( volatile int *) LOCK_ADDRESS;

void AcquireGlobalLock(){
	while(*gLock);
}

void ReleaseGlobalLock(){
	*gLock = 0;
}
```

O LocalLock pode ser implementado assim :

```C++
void AcquireLocalLock(volatile int* lock){
	AcquireGlobalLock();
	while(*lock){
		ReleaseGlobalLock();
   	for(int i=0; i < 15; i++) {}
   	AcquireGlobalLock();
   }
	*lock = 1;
	ReleaseGlobalLock();
}

void ReleaseLocalLock(volatile int* lock){
	AcquireGlobalLock();
	*lock = 0;
	ReleaseGlobalLock();
}
```

A applicação pode usar essas funções para accessar uma memoria compartilhada.

Eu tentei implementar um programa que calcule o número de números primos menores que MAX. 
Eu encontrei problemas que eu não consegui resolver, então não consegui comparar os tempos de execução da versão single core 
e da versão multicore do programa. 
O programa está no arquivo [application.cpp](https://github.com/titooan/MC723/blob/master/exercicio4/mips-tlm/application.cpp).

