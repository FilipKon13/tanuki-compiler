SRCDIR = src
OUTDIR = out

CXXFLAGS = -std=c++17 -Wall -Werror -O3
CXX = g++
INCLUDES = -Ijson/external/PEGTL/include -Ijson/include/

TARGETS = $(OUTDIR)/tnk2js $(OUTDIR)/json2js

all: $(TARGETS)

$(OUTDIR)/tnk2js: $(SRCDIR)/compile.cpp $(SRCDIR)/compile.hpp $(SRCDIR)/compilable_types.hpp $(SRCDIR)/parser.hpp $(SRCDIR)/tokenizer.hpp $(SRCDIR)/util.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OUTDIR)/json2js:
	echo TODO $@
