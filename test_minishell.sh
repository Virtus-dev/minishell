# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:13:12 by arigonza          #+#    #+#              #
#    Updated: 2025/04/08 23:42:49 by arigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

MINISHELL=./minishell
TMP_MINISHELL_OUTPUT=".minishell_output"
TMP_BASH_OUTPUT=".bash_output"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

tests=(
    "echo hola mundo"
    "ls"
    "pwd"
    "env"
    "export VAR=42 && echo \$VAR"
    "unset VAR && echo \$VAR"
    "cd /tmp && pwd"
    "echo \"test | pipe\""
    "echo hola > out.txt"
    "cat < out.txt"
)

total=${#tests[@]}
passed=0

run_test() {
    local cmd="$1"

    echo "$cmd" | $MINISHELL > $TMP_MINISHELL_OUTPUT 2>&1
    echo "$cmd" | bash > $TMP_BASH_OUTPUT 2>&1

    if diff $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT > /dev/null; then
        echo -e "${GREEN}[OK]${NC} $cmd"
        ((passed++))
    else
        echo -e "${RED}[FAIL]${NC} $cmd"
        echo "→ Minishell output:"
        cat $TMP_MINISHELL_OUTPUT
        echo "→ Bash output:"
        cat $TMP_BASH_OUTPUT
    fi
}

echo "Running $total tests..."
for t in "${tests[@]}"; do
    run_test "$t"
done

rm -f $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT out.txt

echo
echo "Passed $passed/$total tests."
