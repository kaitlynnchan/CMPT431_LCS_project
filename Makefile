CXX = g++
CXXFLAGS = -std=c++20 -march=native -pthread -O3

CORE = core/read_file.h
ALL = lcs_serial lcs_parallel lcs_distributed

all : $(ALL)

% : %.cpp $(CORE) 
	$(CXX) $(CXXFLAGS) -o $@ $< 

.PHONY: clean 

clean : 
	rm -f *.o *.obj $(ALL)


