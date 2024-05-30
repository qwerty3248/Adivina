# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -std=c++17 -Wall -Wextra

# Incluir directorios de SFML (ajusta estas rutas según tu instalación)
SFML_INCLUDE = -I/usr/local/include
SFML_LIBS = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

# Nombre del ejecutable
TARGET = juego_adivinanza

# Archivos fuente
SRCS = Adivinanzas.cpp

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Regla para compilar el programa
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS)

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

# Regla para limpiar archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

