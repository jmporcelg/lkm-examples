
#include<stdio.h>
#define A 34
#define B 40
/* puntero a una func. */
int (*ptr_f) (int, int);
/* func. sumar dos enteros  */
int
f_test (int a, int b)
{ return (a + b);}
/* empezamos :) */
int
main (void)
{
  int suma = 0;
  /* puntero a un int */
  int *suma_ptr = NULL;
  printf ("f_test en:0x%x\n", f_test);
  printf ("ptr_f apunta a:0x%x\n", ptr_f);
  /* apuntamos a f_test(int,int) */
  ptr_f = f_test;
  printf ("ptr_f apunta a @f_test()");
  printf ("...ejecutando *ptr_f()!\n");
  /* call @ptr_f -> f_test */
  suma = (*ptr_f) (A, B);
  /* suma_ptr -> @suma */
  suma_ptr = &suma;
  printf ("la variable 'suma' se encuentra en (@0x%x)\n", &suma);
  /* contenido de @suma_ptr ? */	
  printf ("...contiene el valor:%d\n", *suma_ptr);
  return 0;
}
