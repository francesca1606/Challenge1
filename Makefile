CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../pacs-examples/Examples/include -I../pacs-examples/Examples/include/muparserx 

EXEC     = main
LDFLAGS ?= -L../pacs-examples/Examples/lib   #è DA CAMBIARE (CURRENT DIRECTORY DI GETPOT)
LIBS  ?= -lmuparserx

SRCS = $(wildcard *.cpp)                     #main.cpp Vector.cpp 
OBJS = $(SRCS:.cpp=.o)

HEADERS = $(wildcard *.hpp)                  #Vector.hpp muparserx_fun.hpp 

all: $(EXEC)

%.o: %.cpp  $(HEADERS)                       #gradientMethod.hpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(EXEC):  $(OBJS)                           #%: %.o   
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

clean:
	$(RM) *.o

distclean: clean
	$(RM) *~
