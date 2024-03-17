CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../pacs-examples/Examples/include/muparserx -I../pacs-examples/Examples/include  

EXEC     = main
LDFLAGS ?= -L../pacs-examples/Examples/lib 
LIBS  ?= -lmuparserx


SRCS = $(wildcard *.cpp)                                #main.cpp Vector.cpp gradientMethod.cpp              
OBJS = $(SRCS:.cpp=.o)
HEADERS = Vector.h muParserXFun.hpp  gradientMethod.h             #$(wildcard *.hpp)  
DEPS = $(SRCS:.cpp=.d)           

all: $(EXEC)

$(EXEC): $(OBJS)                                     #%: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

%.o: %.cpp $(HEADERS)             #Vector.h muParserXFun.hpp  gradientMethod.h                
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

%.d: %.cpp
	$(CXX) -MM $(CPPFLAGS) $< > $@

# Include .d files
-include $(DEPS)

clean:
	$(RM) *.o *.d $(EXEC)

distclean: clean
	$(RM) *~
