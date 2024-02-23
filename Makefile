## This file is part of The Lorentz Project. All rights are reserved.
#
## Copyright (C) 2023 rhuibertsjr.
# 

#
## Output 
#
PROJECT_PATH = "/Users/renehuiberts/Documentations/projects/project-lorentz/"

OUT          = Lorentz-engine 
BIN          = ./bin

TARGET       = $(BIN)/$(OUT)
PLATFORM     = $(shell uname -s)

#
## Structure 
#
SRC   = ./src

SRCS  = $(shell find $(SRC) -name "*.c")
OBJS  = $(SRCS:.c=.o)

DEFINES  = -DASSERT #-DNDEBUG

#
## Configurations 
#
CC = gcc 

# Flags
CFLAGS   = -std=gnu99 -Wall -Wextra -Wpedantic -Wno-nullability-completeness
CFLAGS  += -Wno-gnu-zero-variadic-macro-arguments
CFLAGS  += -g -O0 -I$(PROJECT_PATH)/$(SRC) $(DEFINES)

LDFLAGS  = 

#
## Platform specific
#
# Darwin
ifeq ($(PLATFORM), Darwin)

SRCSM = $(shell find $(SRC) -name "*.m") 
OBJSM = $(SRCSM:.m=.o)

LDFLAGS += -lobjc -framework Foundation -framework Cocoa

endif

#
## Build
#
all: clean start 
default: all

$(SRC)/%.o: $(SRC)/%.m
	@echo "\033[1;33mBuilding object: $@ \033[0m"
	$(CC) -c -o $@ $< $(CFLAGS) 
	@echo "\033[1;33mFinished building object: $@ \033[0m \n"

$(SRC)/%.o: $(SRC)/%.c 
	@echo "\033[1;33mBuilding object: $@ \033[0m"
	$(CC) -c -o $@ $< $(CFLAGS) 
	@echo "\033[1;33mFinished building object: $@ \033[0m \n"

ifeq ($(PLATFORM), Darwin)
$(TARGET): $(OBJSM) $(OBJS) 
	@echo "\033[1;33mBuilding target: ./$@ \033[0m"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	@echo "\033[1;33mFinished building target: ./$@ \033[0m \n"
else
$(TARGET): $(OBJS)
	@echo "\033[1;33mBuilding target: ./$@ \033[0m"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	@echo "\033[1;33mFinished building target: ./$@ \033[0m \n"
endif

$(BIN):
	@echo "\033[1;33mBuilding location: ./$@/ \033[0m"
	mkdir -p $(BIN) 
	@echo "\033[1;33mFinished location: ./$@/ \033[0m \n"

start: $(BIN) $(TARGET)
	@echo "\033[1;33mStarting: $(TARGET) \033[0m"
	@$(TARGET)

clean: 
	rm -rf $(BIN) $(OBJS) $(OBJSM)

.PHONY: start clean
