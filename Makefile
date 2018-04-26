include options.mk

TGTS=dreconf

all: $(TGTS)

OBJS=\
	Application.o\
	Utils.o

dreconf: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# install target
include install.mk

clean:
	$(RM) $(OBJS)
	$(RM) $(TGTS)
