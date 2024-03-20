CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -g -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../pacs-examples/Examples/include -I../pacs-examples/Examples/include/muparserx   

EXEC     = main
LDFLAGS ?= -L../pacs-examples/Examples/lib #-Wl,-rpath=/../pacs-examples/Examples/lib/libmuparser.so.2                   # 
LIBS  ?= -lmuparserx


SRCS =  main.cpp    #$(wildcard *.cpp)                                            
OBJS =  $(SRCS:.cpp=.o)
HEADERS = $(wildcard *.hpp)  
#DEPS = $(SRCS:.cpp=.d)           

all: $(EXEC)

%.o: %.cpp $(HEADERS)                             # -o $@ dopo $(EXEC)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<             

$(EXEC): $(OBJS)                                     #%: %.o    ^ instead of <
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@



#%.d: %.cpp
#	$(CXX) -MM $(CPPFLAGS) $< > $@

# Include .d files
#-include $(DEPS)

clean:                       # *.d
	@ $(RM) *.o $(EXEC)

distclean: clean
	@ $(RM) *~
