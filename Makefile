CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = pkg-sync

# Source files
SRC = src/main.c \
      src/modules/utils.c \
      src/modules/pacconf.c \
      src/modules/news.c \
      src/modules/services.c \
      src/modules/interactive.c \
      src/modules/score.c \
      src/modules/forensics.c

# Object files
OBJ = $(SRC:.c=.o)

# Main target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

install:
	mkdir -p $(DESTDIR)/usr/bin
	install -Dm755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

.PHONY: all clean install