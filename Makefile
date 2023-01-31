CC := gcc
CFLAGS := -Wall -pedantic-errors

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))


# Erstellt das Programm
$(BINDIR)/solvelsoe: $(OBJ) | $(OBJDIR) $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Erstellt eine Objektdatei, wenn eine Headerdatei gefunden wurde.
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Erstellt ggf. fehlende Verzeichnisse.
$(OBJDIR):
	mkdir -p obj

$(BINDIR):
	mkdir -p bin

# Löscht alle Objektdateien und die Binärdatei.
clean:
	rm -R $(OBJDIR) $(BINDIR)

.PHONY: clean
