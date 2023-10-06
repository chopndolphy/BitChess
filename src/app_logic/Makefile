# list of sources in *this* directory
CCSRC = a.cc b.cc etc 
OBJS := $(addsuffix .o,  $(CCSRC))
VPATH = $(OBJDIR)
 .SUFFIXES: .cc .o
 .cc.o:
    $(CXX) $(CFLAGS) $< -o $(OBJDIR)/$@