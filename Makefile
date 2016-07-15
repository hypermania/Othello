program_NAME := main
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

CFLAGS += -pthread -Wall

CFLAGS += -msse4.2 -mpopcnt
CPPFLAGS += -msse4.2 -mpopcnt

#CFLAGS += -O0
#CPPFLAGS += -O0

CFLAGS += -Ofast
CPPFLAGS += -Ofast

CPPFLAGS += -pg
CFLAGS += -pg

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

