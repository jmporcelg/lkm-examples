#!/bin/sh
#----------------------------------------------------------------------
# Script que compila todos los ejemplos de LKM para la serie 2.2 y 2.4
# El codigo .c debe estar en el mismo directorio que este script
#
# Ejecutar:
#
#                          root# sh compilar.sh 
# TESTS en: 2.4.20 OK!
#----------------------------------------------------------------------
echo 'Creando ENLACE SIMBOLICO si no existe !'
cd /usr/src && ln -s /usr/src/linux-$(uname -r)  linux 
cd -
echo 'ok! detectada version:'$(uname -r)
echo '> Compilando ejemplo 1...'
gcc -O3 -w listado1.c -o listado1
echo '> Compilando ejemplo 2...'
gcc -c -O3 -w listado2.c 
echo '> Compilando ejemplo 3...'
gcc -c -O2 -w listado3.c -I /usr/src/linux/include
echo '> Compilando ejemplo 4...'
gcc -c -O2 -w listado4.c -I /usr/src/linux/include
echo '> Compilando ejemplo 5...'
gcc -c -O2 -w listado5.c -I /usr/src/linux/include
echo '> Compilando ejemplo 5-B...'
gcc -c -O2 -w listado5-B.c -I /usr/src/linux/include
echo '> Compilando ejemplo 6 (backdoor)'
gcc -c -O2 -w backdoor1.c -I /usr/src/linux/include
echo '...ok!'
echo 'Listo para ejecutar ./listado1 e insertar (root# INSMOD) listadoX.o'
# se generan los ficheros objeto a insertar con 'insmod' listadoX.o
# el LISTADO 1 * NO * es un LKM se compila normal y se ejecuta con
# linux$ ./listado1 ;-)
