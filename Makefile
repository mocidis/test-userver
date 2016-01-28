.PHONY: all clean

USERVER_DIR:=../userver

COMMON_DIR:=../common
COMMON_SRCS:=ansi-utils.c my-pjlib-utils.c my-openssl.c lvcode.c

PROTOCOL:=$(shell ls -1 protocol|head -1)

GEN_DIR:=gen
GEN_S_SRCS:=myproto-server.c
GEN_C_SRCS:=myproto-client.c

MAIN_DIR:=.
MAIN_S_SRCS:=server.c
MAIN_C_SRCS:=client.c

CFLAGS:=-g -I$(MAIN_DIR)/include -I$(COMMON_DIR)/include -I$(GEN_DIR) -DPJ_AUTOCONF=1 -O2 -DPJ_IS_BIG_ENDIAN=0 -DPJ_IS_LITTLE_ENDIAN=1 -I../libs/darwin-x86_64/include/json-c -I../libs/darwin-x86_64/include

LIBS:=-L../libs/darwin-x86_64/lib ../libs/darwin-x86_64/lib/libjson-c.a -lpthread -lstdc++ -lpjsua-x86_64-apple-darwin12.5.0 -lpjsip-ua-x86_64-apple-darwin12.5.0 -lpjsip-simple-x86_64-apple-darwin12.5.0 -lpjsip-x86_64-apple-darwin12.5.0 -lpjmedia-codec-x86_64-apple-darwin12.5.0 -lpjmedia-x86_64-apple-darwin12.5.0 -lpjmedia-videodev-x86_64-apple-darwin12.5.0 -lpjmedia-audiodev-x86_64-apple-darwin12.5.0 -lpjmedia-x86_64-apple-darwin12.5.0 -lpjnath-x86_64-apple-darwin12.5.0 -lpjlib-util-x86_64-apple-darwin12.5.0 -lsrtp-x86_64-apple-darwin12.5.0 -lresample-x86_64-apple-darwin12.5.0 -lgsmcodec-x86_64-apple-darwin12.5.0 -lspeex-x86_64-apple-darwin12.5.0 -lilbccodec-x86_64-apple-darwin12.5.0 -lg7221codec-x86_64-apple-darwin12.5.0 -lportaudio-x86_64-apple-darwin12.5.0 -lpj-x86_64-apple-darwin12.5.0 -lm -lpthread -lcrypto

SERVER_APP:=server
CLIENT_APP:=client

all: gen $(SERVER_APP) $(CLIENT_APP)

$(SERVER_APP): $(COMMON_SRCS:.c=.o) $(GEN_S_SRCS:.c=.o) $(MAIN_S_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(CLIENT_APP): $(COMMON_SRCS:.c=.o) $(GEN_C_SRCS:.c=.o) $(MAIN_C_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(COMMON_SRCS:.c=.o): %.o: $(COMMON_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(GEN_S_SRCS:.c=.o): %.o: $(GEN_DIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(GEN_C_SRCS:.c=.o): %.o: $(GEN_DIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_C_SRCS:.c=.o): %.o: $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_S_SRCS:.c=.o): %.o: $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

gen: protocol/$(PROTOCOL)
	mkdir -p gen 
	awk -v base_dir=$(USERVER_DIR) -f $(USERVER_DIR)/gen-tools/gen.awk $<
clean:
	rm -fr gen $(SERVER_APP) $(CLIENT_APP) *.o
