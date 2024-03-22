CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -g -Wall -I. -I./include -Wno-conversion-null -Wno-deprecated-declarations -I../pacs-examples/Examples/include -I../pacs-examples/Examples/include/muparser   

EXEC     = main
LDFLAGS ?= -L../pacs-examples/Examples/lib  #-Wl,-rpath,../pacs-examples/Examples/lib               # 
LIBS  ?= -lmuparser


SRCS =  main.cpp    #$(wildcard *.cpp)                                            
OBJS =  $(SRCS:.cpp=.o)
HEADERS = $(wildcard include/*.hpp)  
#DEPS = $(SRCS:.cpp=.d)           

all: $(EXEC)

%.o: %.cpp $(HEADERS)                             # -o $@ dopo $(EXEC)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<             

$(EXEC): $(OBJS)                                     #%: %.o    ^ instead of <
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

clean:                       # *.d
	@ $(RM) *.o $(EXEC)

distclean: clean
	@ $(RM) *~
