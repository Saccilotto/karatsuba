# Compiler
CC := g++
CFLAGS := -std=c++1y

# Source files
KARATSUBA_SRCS := karatsuba.cpp 
KARATSUBA_TRIPLO_SRCS := karatsuba_triplo.cpp 

# Object files
KARATSUBA_OBJS := $(KARATSUBA_SRCS:.cpp=.o)
KARATSUBA_TRIPLO_OBJS := $(KARATSUBA_TRIPLO_SRCS:.cpp=.o)

# Executables
KARAT_TARGET := karat
KARAT_TRIPLO_TARGET := karat3

# Default target
all: $(KARAT_TARGET) $(KARAT_TRIPLO_TARGET)

# Compile karatsuba source files
$(KARAT_TARGET): $(KARATSUBA_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile karatsuba_triplo source files
$(KARAT_TRIPLO_TARGET): $(KARATSUBA_TRIPLO_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean all .o files and executable generated files
clean:
	rm -f $(KARATSUBA_OBJS) $(KARATSUBA_TRIPLO_OBJS) $(KARAT_TARGET) $(KARAT_TRIPLO_TARGET)

