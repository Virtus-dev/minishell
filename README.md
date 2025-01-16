#

En tokenize_command, primer bucle while, dentro del if,
hay que hacer una funcion que identifique el tipo de metacaracter.

modificar estructura s_token, para añadir el tipo de metacaracter que sea.



heredoc


cd | pwd| wc hola.txt >> output.txt
ls > out.txt | wc


el padre solo ejecuta built-ins

ejemplo : ls | cat | wc
el padre aqui no puede ejecutar nada,
hijo ejecuta ls en stdin

la idea seria hacer un bucle y cada vez que terminemos el proceso hijo, mandamos a stdin padre, y luego el siguiente hijo lee del stin del padre para extrar la info del comando ejecutado anteriormente

> esto sobreescribe
>> esto es añadir a un archivo
heredoc:es solo << y un delimitador, que despliega un dquote que te permite escribir hasta el del, en la linea solo puede estar el del



parseo:

1. si linea no es \n ni ""(vacio), se trimea y se anade al historial
2.si la linea no existe(proteccion al malloc del trim).
3.si la linea esta vacia despues de todo, vuelves a leer.

