
FPNN_RELEASE_INCLUDE_PATH = ../fpnn-sdk-cpp/release/include

OBJS_C = 

OBJS_CXX = src/RTMServerClient.o  src/RTMProcessor.o src/base/bit.o src/base/obpool.o src/base/jenkins.o src/base/hashint.o src/base/MidGenerator.o

# Static 
LIBRTM_A = librtm.a

CFLAGS +=
CXXFLAGS +=
CPPFLAGS += -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/base -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/proto -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/proto/msgpack -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/proto/rapidjson -Isrc/base

all: $(LIBRTM_A)

clean:
	find . -name \*.lo -o -name \*.o | xargs rm -f
	find . -name \*.la -o -name \*.a | xargs rm -f 
	find . -name \*.so | xargs rm -f
	find . -name .libs -a -type d | xargs rm -rf
	rm -rf $(LIBRTM_A) 

include src/def.mk
