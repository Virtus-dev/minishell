# Minishell

Una shell mínima escrita en C, que replica muchas de las características de Bash:  
- **Built‑ins**: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`  
- **Pipelines** (`|`)  
- **Redirecciones** (`>`, `>>`, `<`, `<<` (heredoc))  
- **Gestión de señales** (`Ctrl‑C`, `Ctrl‑\`)  
- **Manejo de entorno** con estructuras de tipo _map_ para `env` y `export`  
- **Lectura interactiva** con GNU Readline

---

## 📋 Características

- **Prompt interactivo** sin terminarse al pulsar `Ctrl‑C`.  
- **Fork + Exec** para comandos externos y pipelines, con restauración de señales en hijos.  
- **Built‑ins** que modifican el entorno en el proceso padre (p.ej. `cd`, `unset`, `export`).  
- **Soporte heredoc**: `<< DELIM … DELIM`.  
- **Tests unitarios** en C para tokenización y `cd` (`test_tokenizer.c`, `test_cd.c`).  
- **Script de integración** para ejecutar comparativas con Bash (`test_minishell.sh`).  
- **Makefile** con objetivos:  
  - `all` / `minishell`  
  - `clean` / `fclean` / `re`  
  - `sanitize` / `sanitize_mem`

---

## 🛠️ Requisitos

- GCC (o clang) compatible con C99  
- Make  
- GNU Readline  
- Linux / macOS (POSIX compliant)  

---

## 🚀 Compilación

```bash
# Compila libft y la minishell
make

# Compila con sanitizers (thread)
make sanitize

# Compila con AddressSanitizer
make sanitize_mem

# Limpia objetos
make clean

# Elimina ejecutables y libft
make fclean

# Reconstruye todo
make re

🎮 Uso
$ ./minishell
minishell$ echo "Hola, mundo"
Hola, mundo
minishell$ pwd
/home/usuario/proyecto/minishell
minishell$ ls | grep src > archivos.txt
minishell$ cat <<EOF
> línea 1
> línea 2
> EOF
línea 1
línea 2
minishell$ exit

Pipelines: cada segmento se ejecuta en un proceso hijo.

Redirecciones:

> sobreescribe

>> añade

< lee de archivo

<< DELIM heredoc

⚙️ Señales
Shell principal:

SIGINT (Ctrl‑C) → limpia la línea con Readline, no cierra la shell

SIGQUIT (Ctrl‑\) → ignorada

Procesos hijos:

Restablecen SIGINT y SIGQUIT a DEFAULT antes de execve, para que se puedan interrumpir normalmente.

🧪 Pruebas
Tokenización:

make MAIN=test_tokenizer.c

Built-in cd:

make MAIN=test_cd.c

Batería de integración frente a Bash:

chmod +x test_minishell.sh
./test_minishell.sh

📂 Estructura de directorios
bash
Copiar
.
├── includes/              # Cabeceras (.h)
├── libft/                 # Submódulo libft
├── obj/                   # Objetos compilados
├── src/
│   ├── built-ins/         # cd, echo, env, exit, export, pwd, unset
│   ├── exec/              # fork/exec, señales
│   ├── parsing/           # split, tokens, metacaracteres
│   ├── tokens/            # tokenizer y agrupación
│   ├── utils/             # mapas, listas, redirecciones, heredoc
│   ├── validations/       # comprobaciones de sintaxis
│   └── main.c
├── test_tokenizer.c       # Test de tokenización
├── test_cd.c              # Test de cd
├── test_minishell.sh      # Script de integración
├── Makefile
└── README.md