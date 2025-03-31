# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:13:12 by arigonza          #+#    #+#              #
#    Updated: 2025/03/31 16:28:17 by arigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

MINISHELL=./minishell
TMP_MINISHELL_OUTPUT=output_minishell.txt
TMP_BASH_OUTPUT=output_bash.txt

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

tests=(
    "ls"
    "pwd"
    "echo Hello, world!"
    "cat ./test_file"
    "env"
    'export TEST_VAR=42 && echo $TEST_VAR'
    'unset TEST_VAR && echo $TEST_VAR'
    "cd .. && pwd"
    "ls | grep test || true"
    "cat nonexistent_file"
)

run_test() {
    local cmd="$1"

    # Ejecuta en minishell
    $MINISHELL <<EOF > $TMP_MINISHELL_OUTPUT 2>&1
$cmd
EOF
    minishell_exit_code=$?

    # Ejecuta en bash
    bash <<EOF > $TMP_BASH_OUTPUT 2>&1
$cmd
EOF
    bash_exit_code=$?

    # Comparación de salida y códigos de salida
    if diff -Z $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT >/dev/null && [ $minishell_exit_code -eq $bash_exit_code ]; then
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

for test in "${tests[@]}"; do
    run_test "$test"
done

rm -f $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT
