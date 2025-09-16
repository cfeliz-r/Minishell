# 🐚 Minishell - Babuterm

<div align="center">

[![42](https://img.shields.io/badge/42-Madrid-000000?style=for-the-badge&logo=42&logoColor=white)](https://42madrid.com/)
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://www.linux.org/)
[![Readline](https://img.shields.io/badge/GNU_Readline-A42E2B?style=for-the-badge&logo=gnu&logoColor=white)](https://tiswww.case.edu/php/chet/readline/rltop.html)

*A comprehensive Unix shell implementation recreating bash functionality*

[Features](#features) • [Installation](#installation) • [Usage](#usage) • [Built-ins](#built-in-commands) • [Architecture](#architecture)

</div>

---

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Advanced Features](#advanced-features)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Memory Management](#memory-management)
- [Signal Handling](#signal-handling)
- [Testing](#testing)
- [Authors](#authors)
- [License](#license)

## 🎯 About

**Minishell** is a simplified shell implementation written in C as part of the 42 School curriculum. This project recreates the core functionality of bash, providing users with a command-line interface capable of executing commands, managing processes, handling I/O redirection, and implementing essential built-in commands.

The shell handles complex parsing, process management, signal handling, and memory management while maintaining compatibility with standard Unix shell behavior.

## ✨ Features

### Core Shell Functionality
- 🔄 **Interactive Command Execution** - Execute system commands and built-ins
- 📝 **Command History** - Navigate through command history using arrow keys
- 🎨 **Colored Prompt** - Beautiful, informative prompt with color coding
- 🔍 **Path Resolution** - Automatic command path discovery
- 🧠 **Memory Safe** - Comprehensive memory management with no leaks

### Advanced Parsing
- 🎭 **Quote Handling** - Support for single (`'`) and double (`"`) quotes
- 🔗 **Pipe Operations** - Chain commands with pipes (`|`)
- 📊 **Variable Expansion** - Environment variable substitution (`$VAR`)
- 🚫 **Syntax Validation** - Comprehensive input validation and error handling

### I/O Redirection
- 📥 **Input Redirection** (`<`) - Redirect stdin from files
- 📤 **Output Redirection** (`>`) - Redirect stdout to files  
- 📋 **Append Mode** (`>>`) - Append output to files
- 📄 **Here Documents** (`<<`) - Multi-line input with delimiters

### Process Management
- 🔄 **Pipeline Execution** - Multi-command pipelines
- ⚡ **Signal Handling** - Proper `SIGINT` and `SIGQUIT` management
- 🎯 **Exit Status** - Accurate exit code handling
- 🧵 **Fork Management** - Efficient process creation and cleanup

## 🚀 Installation

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential libreadline-dev

# macOS
brew install readline
```

### Build from Source

```bash
# Clone the repository
git clone [repository-url]
cd Babuterm

# Compile the project
make

# Run the shell
./minishell
```

### Makefile Targets

```bash
make           # Build the project
make clean     # Remove object files
make fclean    # Remove object files and executable
make re        # Rebuild everything
```

## 💻 Usage

### Basic Command Execution

```bash
# Start the shell
./minishell

# Execute commands
babuterm$ ls -la
babuterm$ echo "Hello, World!"
babuterm$ cat file.txt
```

### Pipe Operations

```bash
# Chain commands with pipes
babuterm$ ls -la | grep ".c" | wc -l
babuterm$ cat file.txt | head -10 | tail -5
```

### I/O Redirection

```bash
# Input redirection
babuterm$ wc -l < input.txt

# Output redirection
babuterm$ echo "Hello" > output.txt
babuterm$ ls -la >> log.txt

# Here documents
babuterm$ cat << EOF
This is a multi-line
input example
EOF
```

### Variable Expansion

```bash
# Environment variables
babuterm$ echo $HOME
babuterm$ echo "User: $USER"
babuterm$ echo 'Literal: $HOME'  # No expansion in single quotes
```

## 🛠 Built-in Commands

| Command | Description | Example |
|---------|-------------|---------|
| `echo` | Display text with optional `-n` flag | `echo -n "Hello World"` |
| `cd` | Change directory | `cd /path/to/directory` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variables | `export VAR=value` |
| `unset` | Remove environment variables | `unset VAR` |
| `env` | Display environment variables | `env` |
| `exit` | Exit the shell | `exit [code]` |

### Built-in Command Details

#### `echo`
```bash
babuterm$ echo "Hello World"           # Basic output
babuterm$ echo -n "No newline"         # Suppress newline
babuterm$ echo -n -n -n "Multiple -n"  # Multiple -n flags
```

#### `cd`
```bash
babuterm$ cd /home/user      # Absolute path
babuterm$ cd ..              # Parent directory
babuterm$ cd                 # Home directory
babuterm$ cd -               # Previous directory
```

#### `export`
```bash
babuterm$ export NAME=value     # Set variable
babuterm$ export PATH=$PATH:/new/path  # Modify PATH
babuterm$ export               # List all exported variables
```

## 🔧 Advanced Features

### Quote Handling
- **Single Quotes**: Preserve literal values
- **Double Quotes**: Allow variable expansion
- **Quote Removal**: Automatic quote stripping in arguments

### Error Handling
- Comprehensive syntax error detection
- Graceful handling of invalid commands
- Proper exit status propagation
- Memory cleanup on errors

### Signal Management
- `Ctrl+C` (SIGINT): Interrupt current command
- `Ctrl+\` (SIGQUIT): Ignored in interactive mode
- `Ctrl+D` (EOF): Exit shell gracefully

## 🏗 Architecture

### Core Components

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Input Parser  │───▶│  Command Parser │───▶│   Executor      │
│   (Lexical)     │    │   (Syntax)      │    │  (Execution)    │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│ Quote Handler   │    │ Variable Expand │    │ Process Manager │
│ Error Validator │    │ Path Resolution │    │ Signal Handler  │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### Data Structures

#### Command Structure
```c
typedef struct s_command {
    int is_correct;        // Validation flag
    char **args;           // Command arguments
    char *cmd_cpt;         // Command name
    char *path;            // Command path
    char *inredir;         // Input redirection
    char **delimiters;     // Here-doc delimiters
    char **outredirs;      // Output redirections
    int appd_out;          // Append flag
    int error;             // Error status
} t_command;
```

#### Environment List
```c
typedef struct s_list_envp {
    char *envp_content;           // Environment variable
    struct s_list_envp *next;     // Next node
} t_list_env;
```

## 📁 Project Structure

```
Babuterm/
├── 📄 Makefile              # Build configuration
├── 📄 minishell.h           # Main header file
├── 📄 structs.h             # Data structures
├── 📁 src/                  # Source code
│   ├── 📄 main.c            # Entry point
│   ├── 📄 minishell.c       # Core shell logic
│   ├── 📁 builtin/          # Built-in commands
│   │   ├── 📄 ft_echo.c     # Echo implementation
│   │   ├── 📄 ft_cd.c       # CD implementation
│   │   ├── 📄 ft_export.c   # Export implementation
│   │   └── 📄 ...           # Other built-ins
│   ├── 📁 parsing/          # Input parsing
│   │   ├── 📄 parse_commands.c
│   │   └── 📄 ...
│   ├── 📁 commands/         # Command execution
│   ├── 📁 redirection/      # I/O redirection
│   ├── 📁 signals/          # Signal handling
│   ├── 📁 utils/            # Utility functions
│   └── 📁 errors/           # Error handling
├── 📁 libft/                # Custom C library
│   ├── 📄 libft.h
│   ├── 📄 ft_*.c            # Library functions
│   └── 📁 get_next_line/    # GNL implementation
└── 📁 obj/                  # Compiled objects
```

## 🧠 Memory Management

### Safe Memory Practices
- **Automatic Cleanup**: All allocated memory is properly freed
- **Error Handling**: Memory cleanup on all error paths
- **Leak Prevention**: Comprehensive testing for memory leaks
- **Resource Management**: Proper file descriptor and process cleanup

### Memory Testing
```bash
# Test for memory leaks
valgrind --leak-check=full --track-origins=yes ./minishell

# Test with specific commands
echo "command" | valgrind ./minishell
```

## 📡 Signal Handling

### Interactive Mode
- **SIGINT** (`Ctrl+C`): Display new prompt
- **SIGQUIT** (`Ctrl+\`): Ignored
- **EOF** (`Ctrl+D`): Exit shell

### Command Execution
- **SIGINT**: Interrupt running command
- **SIGQUIT**: Send quit signal to command
- **Child Processes**: Proper signal propagation

## 🧪 Testing

### Manual Testing
```bash
# Basic functionality
echo "test" | ./minishell
echo "ls | wc -l" | ./minishell
echo "export TEST=value && echo \$TEST" | ./minishell

# Edge cases
echo "ls |" | ./minishell           # Syntax error
echo "echo \"unclosed quote" | ./minishell  # Quote error
```

### Automated Testing
```bash
# Create test suite
bash test_suite.sh

# Compare with bash
echo "command" | bash > expected.txt
echo "command" | ./minishell > result.txt
diff expected.txt result.txt
```

## 👥 Authors

<div align="center">

| Author | GitHub | Email |
|--------|--------|-------|
| **manufern** | [@manufern](https://github.com/manufern) | manufern@student.42.fr |
| **cfeliz-r** | [@cfeliz-r](https://github.com/cfeliz-r) | cfeliz-r@student.42.fr |

</div>

## 📊 Project Statistics

- **Lines of Code**: ~2,750
- **Files**: 45+ source files
- **Functions**: 100+ custom functions
- **Development Time**: 3+ months
- **Language**: C (C99 standard)

## 🤝 Contributing

While this is an educational project, contributions and suggestions are welcome:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is part of the 42 School curriculum. It's shared for educational purposes.

---

<div align="center">

**Made with ❤️ at 42 Madrid**

*"The shell is the ultimate power tool"*

</div>
