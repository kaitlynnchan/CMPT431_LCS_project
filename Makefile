ifdef USE_INT
MACRO = -DUSE_INT
endif

CXX = g++
MPICXX = mpic++
CXXFLAGS = -std=c++11 -march=native -pthread -O3 $(MACRO)

CORE = core/read_file.h
SERIAL= lcs_serial 
PARALLEL= lcs_parallel
DISTRIBUTED= lcs_distributed
ALL = $(SERIAL) $(PARALLEL) $(DISTRIBUTED)

all : $(ALL)

$(SERIAL): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(PARALLEL): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(DISTRIBUTED): %: %.cpp
	$(MPICXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean 

clean : 
	rm -f *.o *.obj $(ALL)


