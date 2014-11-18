# Maxime Brodat
# maxime.brodat@utbm.fr
# contact@fouss.fr
#
# Stéphane Perrez
# stéphane.perrez@utbm.fr
#
# Deadline of the project: 01/05/2015


# My general makefile template
CXX = gcc
CFLAGS = -Wall -Werror -g -ansi -pedantic -fpic
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

# Library-related macros
LIBTARGET2 = Polygon
LIBTARGET = libPolygon.so
LIBSOURCE = polygon useful_fcts
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

# Application-related macros
TARGET = polygonManager.exe
EXESOURCE = polygonmain
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

# To overload the content of the LD_LIBRARY_PATH
# Export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.

# Running the program
run: $(TARGET)
	@echo "\n Executing the executable " $(TARGET)
	./$(TARGET)

# Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET)
	@echo "\n Generating the executable " $@
	$(CXX) $(EXESOURCEOFILE) -l$(LIBTARGET2) $(LIBSDIR) -o $(TARGET)

# Generating the library binary code
$(LIBTARGET): $(LIBSOURCEOFILE)
	@echo "\n Generating the library " $@
	$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)

# Generating an object file from a C file having the same name
.c.o:
	@echo "\n Generating " $@ " from " $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

# Cleaning the content of the current directory
clean:
	@echo "\n Cleaning temporary files"
	rm -rf *.o *~ *.so *.exe
