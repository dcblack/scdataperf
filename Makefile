#!make -f

PROJECT=dataperf

# Change the following to suit your needs
ifndef SYSTEMC
  SYSTEMC=/Users/dcblack/eda/osci/systemc/2.3-clang5.0
endif
ifndef TARGET_ARCH
  TARGET_ARCH=macosx64
  BITS=64
endif
CXX=clang++
CXXFLAGS=\
  -arch x86_64\
  -stdlib=libc++\
  -DSC_INCLUDE_FX=1\
  -I.\
  -I$(SYSTEMC)/include\
  -m$(BITS)\
  -std=c++11\
  -pedantic\
  -g\
  -O2
LDFLAGS=\
  -L$(SYSTEMC)/lib-$(TARGET_ARCH)\
  -lsystemc

.PHONY: clean compile run

run: ./$(PROJECT).log

compile: ./$(PROJECT).x

$(PROJECT).log: ./$(PROJECT).x ./$(PROJECT).sh ./filter
	./$(PROJECT).sh $(ARGS) | tee -a $(PROJECT).log

./$(PROJECT).x: ./$(PROJECT).cpp
	 $(CXX) $(CXXFLAGS) -o $(PROJECT).x $(PROJECT).cpp $(LDFLAGS) | c++filt | tee -a compile.log

clean:
	rm -fr $(PROJECT).[xo]

#EOF
