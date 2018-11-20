#!make -f

PROJECT=dataperf

# Change the following to suit your needs
ifndef SYSTEMC
  # Point to systemc installation directory that contains include directory
  # NOTE: This is NOT the source directory for SystemC.
  SYSTEMC=/Users/dcblack/eda/osci/systemc/2.3-clang5.0
endif
ifndef TARGET_ARCH
  # Suffix to append to lib- directory representing host architecture.
  # Often this is linux or linux64.
  TARGET_ARCH=macosx64
  BITS=64
endif
# C++ compiler (clang++ is preferred)
CXX=clang++
# Probably no need to change the following
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
COMPILE_LOG=./compile.log
RUN_LOG=./$(PROJECT).log

.PHONY: clean compile run

run: $(RUN_LOG)

compile: ./$(PROJECT).x

heading.log:
	@-rm -f $(RUN_LOG)
	@echo "INVOKED: `date`"    >>$(RUN_LOG)
	@echo "DIRECTORY: `pwd`"   >>$(RUN_LOG)
	@echo "HOST: `uname -a`"   >>$(RUN_LOG)
	@echo ""                   >>$(RUN_LOG)

$(RUN_LOG): heading.log ./$(PROJECT).x ./$(PROJECT).sh ./filter
	@cp heading.log $(RUN_LOG)
	./$(PROJECT).sh $(ARGS) | tee -a $(RUN_LOG)

./$(PROJECT).x: ./$(PROJECT).cpp
	@cp compile.log $(COMPILE_LOG)
	 $(CXX) $(CXXFLAGS) -o $(PROJECT).x $(PROJECT).cpp $(LDFLAGS) | c++filt | tee -a $(COMPILE_LOG)

clean:
	rm -fr $(PROJECT).[xo] heading.log

#EOF
