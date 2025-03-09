CC = gcc
CFLAGS = -Wall -I external/cJSON # Sau -I src, depinzand de locul unde se afla cJSON.h.

SRCS = src/main.c external/cJSON/cJSON.c # Adapteaza locatia surselor
OBJS = $(SRCS:.c=.o)
EXEC = output

all: $(EXEC)

$(EXEC): $(OBJS)
    $(CC) $(OBJS) -o $(EXEC)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(EXEC)