![logo](/NoPineappleShell.gif")

<p align="center">
  <img src="NoPineappleShell.gif" alt="minishell demo" width="600">
</p>

# minishell

A small Unix shell written in C, inspired by Bash. Built as a pair project at
[42 Madrid](https://www.42madrid.com/) with [@TU_COMPAÑERO/A](https://github.com/USUARIO).

## Features

- Interactive prompt with command history (GNU readline)
- Command execution via `fork`, `execve` and `wait`, resolving binaries through `PATH`
- Pipes (`|`) and redirections (`<`, `>`, `>>`, `<<` heredoc)
- Environment variable expansion (`$VAR`, `$?`) and single/double quote handling
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- <!-- TODO: bonus (&&, ||, wildcards) y builtins propios, si aplican -->

## How it works

Input goes through a pipeline: **tokenizer → state-machine parser → expansion →
executor**. The parsing stage is built around a finite-state machine that
handles quotes, operators and word boundaries.

![State machine](automata_graph.jpeg)

## Build and run

Requires a C compiler and the readline library.

```bash
git clone https://github.com/anfipatica/minishell.git
cd minishell
make
./minishell
```

`make clean`, `make fclean` and `make re` are also available.

## What I learned

- Process management and file descriptor plumbing (pipes, redirections, heredocs)
- Signal handling in an interactive program
- Parsing with a state machine and managing memory without leaks
- Working in a pair: splitting the parser and the executor, and reviewing each other's code

## Authors

- [Yolanda Muñoz](https://github.com/anfipatica)
- <!-- compañero/a -->
