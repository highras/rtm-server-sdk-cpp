
EXES_DEMO_EXAMPLE = demo

FPNN_RELEASE_DIR = ../../../infra-fpnn-sdk/C++/release
RTM_RELEASE_DIR = ../release

FPNN_INCLUDE_DIR = $(FPNN_RELEASE_DIR)/include/fpnn
FPNN_LIB_DIR = $(FPNN_RELEASE_DIR)/lib

CFLAGS +=
CXXFLAGS += -std=c++11
CPPFLAGS += -g -Wall -Werror -fPIC -O2
CPPFLAGS += -I$(FPNN_INCLUDE_DIR) -I$(FPNN_INCLUDE_DIR)/core -I$(FPNN_INCLUDE_DIR)/base -I$(FPNN_INCLUDE_DIR)/proto -I$(FPNN_INCLUDE_DIR)/proto/msgpack -I$(RTM_RELEASE_DIR)/include
LIBS += -rdynamic -lstdc++ -L$(FPNN_LIB_DIR) -lfpnn -L$(RTM_RELEASE_DIR)/lib -lrtm -lpthread

OBJS_DEMO_EXAMPLE = demo.o

all: $(EXES_DEMO_EXAMPLE) 

clean:
	$(RM) *.o $(EXES_DEMO_EXAMPLE) 

# exmples list

$(EXES_DEMO_EXAMPLE): $(OBJS_DEMO_EXAMPLE)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS)

#for rules

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cpp:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS)

LIBS += -rdynamic -lstdc++ -L$(FPNN_LIB_DIR) -lfpnn -L$(RTM_RELEASE_DIR)/lib -lrtm -lpthread
