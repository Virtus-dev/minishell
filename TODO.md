# TODO

## HEREDOC

Heredoc no esta funcionando correctamente, parece ser que las funciones que comprueban si es una doble redireccion "<<" o una simple "<" o estan funcionando correctamente.

`cat <<EOF`

no entra en heredoc, y actualmente estoy trabajando en ello para solucionarlo.

## Comando echo

Aún falta replicar el comportamiento exacto de este comando.

## Expansion de $?

Debe devolver el codigo de estatus del comando anterior.

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