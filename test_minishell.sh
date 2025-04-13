# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 18:43:32 by arigonza          #+#    #+#              #
#    Updated: 2025/04/13 19:07:41 by arigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
# test_minishell.sh
# Script para testear la minishell.
# Se asume que la minishell se cierra con "exit"
# y que bash -c "$t" produce la salida deseada.

# Configuraciones:
MINISHELL=./minishell
TMP_MS_OUTPUT="ms_output.txt"
TMP_BASH_OUTPUT="bash_output.txt"

# Array de comandos de prueba (modifícalos o agrégalos a tu gusto)
tests=(
    "echo hola mundo"
    "ls"
    "pwd"
    "echo \"esto > no es una redireccion\""
    "cat < Makefile | head -n 1"
    "ls -l > prueba.txt"
    "cat < prueba.txt"
    "cd .. | pwd"
)

pass=0
fail=0
total=${#tests[@]}

echo "Running $total tests..."
for t in "${tests[@]}"; do
    # Ejecuta la minishell: se envía el comando y luego "exit" para forzar el cierre.
    printf "%s\nexit\n" "$t" | $MINISHELL > "$TMP_MS_OUTPUT" 2>&1
    # Ejecuta bash -c "$t" (no necesita "exit")
    bash -c "$t" > "$TMP_BASH_OUTPUT" 2>&1

    # Limpieza de salida de la minishell:
    # Eliminar todas las líneas que sean exactamente "exit"
    sed -i '/^exit$/d' "$TMP_MS_OUTPUT"
    
    # Si la primera línea es exactamente igual al comando, se elimina (esto puede ocurrir si la minishell lo ecoea)
    first_line=$(head -n 1 "$TMP_MS_OUTPUT")
    if [ "$first_line" = "$t" ]; then
        tail -n +2 "$TMP_MS_OUTPUT" > "${TMP_MS_OUTPUT}.tmp"
        mv "${TMP_MS_OUTPUT}.tmp" "$TMP_MS_OUTPUT"
    fi

    # Compara las salidas
    if diff -u "$TMP_MS_OUTPUT" "$TMP_BASH_OUTPUT" > /dev/null; then
        echo -e "[\033[0;32mPASS\033[0m] $t"
        ((pass++))
    else
        echo -e "[\033[0;31mFAIL\033[0m] $t"
        echo "→ Minishell output:"
        cat "$TMP_MS_OUTPUT"
        echo "→ Bash output:"
        cat "$TMP_BASH_OUTPUT"
        ((fail++))
    fi
done

echo ""
echo "Tests passed: $pass"
echo "Tests failed: $fail"

rm -f prueba.txt
rm -f "$TMP_MS_OUTPUT" "$TMP_BASH_OUTPUT"
