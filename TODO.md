# TODO

## FALLO CRiTCO

Por alguna razon a apareido un problema que antes no existia, que consiste en que cuando realizas un comando bloqueante, como por ejemplo `cat` y realizas CNTRL+C te saca a una subshell (porque?, ni idea) y si despues realizas CNTRL+D te lanza un error core dumped. Estoy trabajando en ello actualmente para averiguar porque, y asi poder arreglarlo. (Gracias por estos momentos minishell).

## HEREDOC

Ya entra en HEREDOC, si usas `cat <<EOF` ,pero en cuanto haces un enter sale directamente del cat.

`cat <<EOF`

no entra en heredoc, y actualmente estoy trabajando en ello para solucionarlo.

## Comando echo

Aún falta replicar el comportamiento exacto de este comando.

## Expansion de $?

Debe devolver el codigo de estatus del comando anterior.

## Parser

Al realizar comandos como `rm test.txt` si detecta un espacio al final de test.txt lo interpreta como otro argumento y ejecuta rm sobre una cadena vacia lo que devuelve `/usr/bin/rm: cannot remove '': No such file or directory`.

Habria que revisar que hace el parser, podria ser que no esta haciendo bien el split por espacios.

## Comandos bloqueantes **[SOLUCIONADO]**

Comandos como:

**cat** sin argumentos:

`cat`

Espera entrada desde stdin indefinidamente hasta que reciba Ctrl+D (EOF) o una señal.

**sleep**, que duerme durante `n` segundos:

`sleep  10`

Puedes interrumpirlo con Ctrl+C.

**read**:

`read var`

Se desbloquea tras escribir y presionar Enter.

## cd .. | pwd **[SOLUCIONADO]**

Al ejecutarse cd en una subshell no debe afectar al pwd, con lo que:

`cd .. | pwd`

Debe imprimir el directorio actual sin modificarse.

## Multiple redirección **[SOLUCIONADO]**

En el caso de:

`ls -l > test1.txt > test2.txt > test3.txt`

Debe de crear los 3 archivos pero escribir tan solo en el ultimo.
Es decir, que `cat test3.txt` deberia imprimir lo que devolvia `ls -l`.