CC 		 	:= clang
CFLAGS	:= -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra -O3 -g
SRC			:= src
BIN     := tsk
LIBS		:= -lm
OBJS		:=
TARGET	:= prod
ENTITIES:= src/entities.h
OBJDIR	:= obj

ifeq ($(TARGET), dev)
	OBJS :=$(addprefix $(OBJDIR)/,hash.o table.o)
else
	OBJS :=$(addprefix $(OBJDIR)/,hash.o table.o tsk.o)
endif

$(BIN): directories $(OBJS) $(SRC)/$(BIN).c
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJDIR) $(OBJDIR)/%.o: $(SRC)/%.c $(SRC)/%.h $(ENTITIES)
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p $(OBJDIR)

clean:
	rm -f *~ *.o $(TARGET)
	rm -rf obj

all: clean $(BIN)
