# Exercício 4 : Plataformas e Periféricos
#####Titouan THIBAUD - RA : 180879

##Atividade
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

