# TO_DO

Hay que tener cuidado con pipeprocessing use la 1era version que teniamos de pipeproccesing y se arreglaron los problemas de señales y del exit, asi que hay que mirar bien eso para que no rompa lo demas

## Exit

Algo de lo que has modificado ha roto la funcion exit, y ya no sale de minishell, tan solo muestra el mensaje "Exit".

## PROBLEMON

echo hola >> output.txt no funciona **[SOLUCIONADO]**
ls | grep "minishell" >> output.txt no funciona -> PARECE SER QUE EL PROBLEMA VIENE DE LA GESTION DE LOS FD, SEGURAMENTE POR LA DIFERENCIA QUE HACEMOS ENTRE PROCESOS HIJOS Y PADRE, HE INTENTADO CAMBIAR LA FORMA EN QUE PIPEPROCESING SE COMPORTA, USANDOLO COMO UN MERO ORQUESTADOR PERO SIGUE DANDO EL MISMO PROBLEMA.
cd .. | pwd funciona correcto

Hay problemas en las pipes y en la redirecciones motivo ni idea.

Cuando ejecutas ./minishell y haces un ps, en los procesos abiertos se pueden ver que se estan ejecutando 2 minishell. Motivo, no se?

## Redirecciones

Cuando hacemos uso de las redirecciones sin usar un comando antes, por ejemplo ` > prueba.txt` no genera el archivo, dberia de generar el archivo aunque este estuviese vacio.
De igual manera no funciona para las redirecciones de entrada `<` o heredoc `<<`, por ejemplo `<< EOF`.

Aqui podemos ver perfectamente el fallo, y uno añadido que no habiamos detectado y es que al no poner un espacio antes de la redirección tokenizer no funciona correctamente y da el token como nulo.

````
$minishell>> prueba.txt -> esto debe ser tema de parseo, si no recuerdo mal, no permito que la linea empieze por >>, > o < u <<
Token NULL
: Success
$minishell> > prueba.txt
cmd = >
data->argv[1] = prueba.txt
bash: /home/arigonza/.vscode-server/bin/17baf841131aa23349f217ca7c570c76ee87b957/bin/remote-cli/: command not found
````

## FALLO CRITICO **[SOLUCIONADO]**

Por alguna razon a apareido un problema que antes no existia, que consiste en que cuando realizas un comando bloqueante, como por ejemplo `cat` y realizas CNTRL+C te saca a una subshell (porque?, ni idea) y si despues realizas CNTRL+D te lanza un error core dumped. Estoy trabajando en ello actualmente para averiguar porque, y asi poder arreglarlo. (Gracias por estos momentos minishell).

Hay que controlar cuando estamos ejecutando con execve, si estamos en execve, flag global= 1 y hacer redisplay, cualquier otra cosa no hacer redisplay.

## HEREDOC **[SOLUCIONADO]**

Ya entra en HEREDOC, si usas `cat <<EOF` ,pero en cuanto haces un enter sale directamente del cat, esta parte esta arreglada, ahora necesitamos usar una variable global(la unica permitida en el proyecto), para que cuando ejecutemos ctrl+C, salga el prompt de la minishell actualmente al hacer ctrl+C directamente en minishell sale el ^C, pero se queda esperando a que escribas algo por teclado cuando deberia devolverte el control a minishell.

`cat <<EOF`

**Actualización**: Si realizas `cat <<EOF` salta un `SIGSEV` mientras que si realizas `cat << EOF` se comporta exactamente como se detalla mas arriba.

no entra en heredoc, y actualmente estoy trabajando en ello para solucionarlo.

**Actualzacion** he conseguido que se detecte `<< EOF` pero no abre el heredoc

## Comando echo **[SOLUCIONADO]**

Aún falta replicar el comportamiento exacto de este comando.

## Expansion directa en minishell **[ARREGLAR]**

Todas estas expansiones se deben tratar tambien directamente desde minishell.
$PWD,$HOME, export a=hola $a, todo este tipo de expansiones debe poder ejecutarse
directamente desde minishell, sin necesidad de usar echo.

`cd $HOME` debe funcionar(no funciona)

## Expansion de $? **[SOLUCIONADO]**

Debe devolver el codigo de estatus del comando anterior.

## Parser **[SOLUCIONADO]**

Al realizar comandos como `rm test.txt` si detecta un espacio al final de test.txt lo interpreta como otro argumento y ejecuta rm sobre una cadena vacia lo que devuelve `/usr/bin/rm: cannot remove '': No such file or directory`.

Habria que revisar que hace el parser, podria ser que no esta haciendo bien el split por espacios.

antes de tokenizer, depurar espacios para que solo haya 1 entre palabras, luego reservar memoria de manera dinamica, para que no de leaks!!

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

## EJECUCION **[SOLUCIONADO]**

Actualmente no podemos ejecutar ./minishell cuando ya estamos dentro de una minishell
(revisar exec_utils.c y exec)

## LEAKS

1. `cat | cat | ls` -> leaks
2. `export a="ls -la" | ls` ->leaks
Conclusion: leaks en pipes (revisar)

## NORMINETTE

Revisar archivos y cumplir norma42!

## Compilacion_con_supresion_de_readline

valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

To "ignore" leaks related to the readline and add_history functions, create a file called readline.supp with the following content:

 {
     leak readline
     Memcheck:Leak
     ...
     fun:readline
 }
 {
     leak add_history
     Memcheck:Leak
     ...
     fun:add_history
 }