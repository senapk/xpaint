# Comando do compilador
CC = gcc
# Opções de compilação
CFLAGS = -Wall -Wextra -g

# Diretório dos arquivos .c
SRCDIR = .
# Diretório dos arquivos .o
OBJDIR =.obj

# Lista de todos os arquivos .c na pasta src
SRCS = $(wildcard $(SRCDIR)/*.c)
# Lista de todos os arquivos .o correspondentes
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Nome do executável
EXEC = main

# Regra padrão para compilar todos os arquivos .c em .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para o alvo principal, que depende de todos os arquivos .o
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para limpar os arquivos .o e o executável
clean:
	rm -f $(OBJDIR)/*.o $(EXEC)

$(shell mkdir -p $(OBJDIR))

# Indica que "clean" e "run" não são os nomes de arquivos a serem gerados
.PHONY: clean run
