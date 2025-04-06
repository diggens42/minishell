# Minishell

> As beautiful as a shell

## 🌀 Overview

**Minishell** is a functional UNIX-like shell written in C. It mimics the behavior of `bash` for a selected set of features and built-ins.
Commands are parsed and executed through a **recursive descent parser** that builds an **Abstract Syntax Tree (AST)** — enabling structured evaluation and execution of complex command inputs.

## 🔑 Key Features

### 🖥️ Core Shell Behavior
- Interactive prompt with command history (using `readline`)
- Executes commands from:
  - Relative paths (e.g. `./a.out`)
  - Absolute paths (e.g. `/bin/ls`)
  - `$PATH` environment variable lookup
- Signal handling:
  - `Ctrl-C`
  - `Ctrl-D`
  - `Ctrl-\`

### 🧙 Built-in Commands

| Command  | Description                            |
|----------|----------------------------------------|
| `echo`   | Prints arguments, supports `-n` option |
| `cd`     | Changes directory (absolute or relative path) |
| `pwd`    | Prints the current working directory   |
| `export` | Sets environment variables             |
| `unset`  | Removes environment variables          |
| `env`    | Displays the environment               |
| `exit`   | Exits the shell                        |

### 📦 Redirections
- `<` — redirect input from file
- `>` — redirect output (truncate)
- `>>` — redirect output (append)
- `<<` — here-document (until delimiter, no history update)

### 🧙 Quotes
- `'single quotes'` — treat all enclosed characters literally
- `"double quotes"` — allow `$VAR` expansion, but treat other metacharacters literally

### 🌍 Environment Handling
- `$VAR` — expands to the value of an environment variable
- `$?` — expands to the exit status of the last executed pipeline

### ✨ Bonus Features
- `&&` and `||` — logical AND / OR operators
- `()` — command grouping with precedence
- `*` — wildcard expansion in the current directory

---

## 🧠 How It Works

- Input is parsed into an **Abstract Syntax Tree (AST)** using **recursion**
- Each node in the tree represents a command, pipe, or logical operator
- Execution walks the AST and launches processes accordingly

---

## 🛠️ Build & Run

```bash
make
./minishell
