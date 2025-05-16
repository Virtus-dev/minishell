# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 18:43:32 by arigonza          #+#    #+#              #
#    Updated: 2025/05/16 13:14:06 by arigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
# test_minishell.sh

MINISHELL=./minishell
TMP_MS=ms_output.txt
TMP_BASH=bash_output.txt

tests=(
  'echo hola mundo'
  'ls'
  'pwd'
  'echo "esto > no es una redireccion"'
  'cat < Makefile | head -n 1'
  'ls -l > prueba.txt'
  'cat < prueba.txt'
  'cd .. | pwd'
  'ls | grep "minishell" >> prueba.txt'
  'export a'
  'export a=b'
  'unset a'
  '$PWD'
  '$PWD$HOME'
  'echo $HOME'
  'echo $HOME$PWD'
  'echo $HOME $PWD'
)

pass=0; fail=0
total=${#tests[@]}

echo "Running $total tests..."
for t in "${tests[@]}"; do
  # Ejecuta en minishell
  printf "%s\nexit\n" "$t" | $MINISHELL > "$TMP_MS" 2>&1

  # 2) Ejecutar en bash
  case "$t" in
    env)        bash -c "env" > "$TMP_BASH" 2>&1 ;;
    export)     bash -c "export -p" > "$TMP_BASH" 2>&1 ;;
    unset\ *)   bash -c "$t" > "$TMP_BASH" 2>&1 ;; # unset no imprime
    *)          bash -c "$t" > "$TMP_BASH" 2>&1 ;;
  esac

  # Limpia minishell output
  sed -i '/^exit$/d' "$TMP_MS"
  sed -i '/^\$minishell>/d' "$TMP_MS"
  # Quita línea exacta que coincida con el comando
  sed -i "\|^$t\$|d" "$TMP_MS"


  # Compara salidas
  if diff -u "$TMP_MS" "$TMP_BASH" >/dev/null; then
    echo -e "[\033[0;32mPASS\033[0m] $t"
    ((pass++))
  else
    echo -e "[\033[0;31mFAIL\033[0m] $t"
    echo "→ Minishell output:"; cat "$TMP_MS"
    echo "→ Bash output:"; cat "$TMP_BASH"
    ((fail++))
  fi
done

echo
echo "Tests passed: $pass"
echo "Tests failed: $fail"

# Limpieza
rm -f prueba.txt "$TMP_MS" "$TMP_BASH"
