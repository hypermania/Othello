program_NAME := Othello
program_C_SRCS := $(wildcard *.c)
# program_CXX_SRCS := $(wildcard *.cpp)
program_C_OBJS := ${program_C_SRCS:.c=.o}
# program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES :=

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))  -pthread -Wall
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir)) 
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library)) 

CFLAGS += -std=gnu90
CPPFLAGS += -std=gnu90

CFLAGS += -pthread -Wall

CFLAGS += -msse4.2 -mpopcnt -mbmi -mbmi2 -mavx -mavx2
CPPFLAGS += -msse4.2 -mpopcnt -mbmi -mbmi2 -mavx -mavx2

#CFLAGS += -O0
#CPPFLAGS += -O0

CFLAGS += -O3
CPPFLAGS += -O3

#CPPFLAGS += -pg
#CFLAGS += -pg

CFLAGS += -DNDEBUG

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME)

clean:
	$(RM) $(program_NAME)
	$(RM) $(program_OBJS)
	$(RM) $(wildcard *~)

distclean: clean

