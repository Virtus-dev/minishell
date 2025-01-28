# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:13:12 by arigonza          #+#    #+#              #
#    Updated: 2025/01/28 16:13:16 by arigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Ruta a tu minishell
MINISHELL=./minishell

# Archivo temporal para guardar las salidas
TMP_MINISHELL_OUTPUT=output_minishell.txt
TMP_BASH_OUTPUT=output_bash.txt

# Colores para mejorar la salida
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # Sin color

# Lista de pruebas
tests=(
    "ls"
    "pwd"
    "echo Hello, world!"
    "cat ./test_file"
    "env"
    "export TEST_VAR=42 && echo \$TEST_VAR"
    "unset TEST_VAR && echo \$TEST_VAR"
    "cd .. && pwd"
    "ls | grep test"
    "cat nonexistent_file"
)

# Función para ejecutar una prueba y compararla con bash
run_test() {
    local cmd="$1"

    # Ejecuta el comando en minishell y guarda la salida
    echo -e "$cmd" | $MINISHELL > $TMP_MINISHELL_OUTPUT 2>&1
    minishell_exit_code=$?

    # Ejecuta el comando en bash y guarda la salida
    echo -e "$cmd" | bash > $TMP_BASH_OUTPUT 2>&1
    bash_exit_code=$?

    # Compara las salidas
    if diff $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT >/dev/null && [ $minishell_exit_code -eq $bash_exit_code ]; then
        echo -e "${GREEN}[PASSED]${NC} Command: $cmd"
    else
        echo -e "${RED}[FAILED]${NC} Command: $cmd"
        echo "Minishell Output:"
        cat $TMP_MINISHELL_OUTPUT
        echo "Bash Output:"
        cat $TMP_BASH_OUTPUT
        echo "Minishell Exit Code: $minishell_exit_code"
        echo "Bash Exit Code: $bash_exit_code"
    fi
}

# Ejecuta todas las pruebas
for test in "${tests[@]}"; do
    run_test "$test"
done

# Limpia archivos temporales
rm -f $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT
