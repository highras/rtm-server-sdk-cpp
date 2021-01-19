
FPNN_RELEASE_INCLUDE_PATH = ../fpnn-sdk-cpp/release/include

OBJS_C = 

OBJS_CXX = src/RTMServerClient.o  src/RTMProcessor.o src/RTMServerConfig.o src/RTMServerClient.Chat.o src/RTMServerClient.Data.o src/RTMServerClient.Files.o src/RTMServerClient.Friends.o src/RTMServerClient.Groups.o src/RTMServerClient.Listening.o src/RTMServerClient.Message.o src/RTMServerClient.Room.o src/RTMServerClient.Token.o src/RTMServerClient.Users.o src/RTMServerClient.Device.o

# Static 
LIBRTM_A = librtm.a

CFLAGS +=
CXXFLAGS +=
CPPFLAGS += -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/base -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/proto -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/proto/msgpack -I$(FPNN_RELEASE_INCLUDE_PATH)/fpnn/proto/rapidjson

all: $(LIBRTM_A)

clean:
	find . -name \*.lo -o -name \*.o | xargs rm -f
	find . -name \*.la -o -name \*.a | xargs rm -f 
	find . -name \*.so | xargs rm -f
	find . -name .libs -a -type d | xargs rm -rf
	rm -rf $(LIBRTM_A) 

include src/def.mk
