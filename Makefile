SRCDIR = src
OUTDIR = out

CXXFLAGS = -std=c++17 -Wall -Werror -O3
CXX = g++
INCLUDES = -Ijson/external/PEGTL/include -Ijson/include/

TARGETS = $(OUTDIR)/tnk2js $(OUTDIR)/json2js $(OUTDIR)/tnk2json

all: outdir $(TARGETS)
	
outdir:
	mkdir -p $(OUTDIR)

$(OUTDIR)/tnk2js: $(SRCDIR)/compile.cpp $(SRCDIR)/compile.hpp $(SRCDIR)/compilable_types.hpp $(SRCDIR)/parser.hpp $(SRCDIR)/tokenizer.hpp $(SRCDIR)/util.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OUTDIR)/json2js: $(SRCDIR)/json2js.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

$(OUTDIR)/tnk2json: $(SRCDIR)/tnk2json.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

.PHONY: all outdir