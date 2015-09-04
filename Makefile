.PHONY: all clean

COMMON_DIR:=../common
COMMON_SRCS:=ansi-utils.c

PROTOCOL:=$(shell ls -1 protocol|head -1)

GEN_DIR:=gen
GEN_S_SRCS:=myproto-server.c
GEN_C_SRCS:=myproto-client.c

MAIN_DIR:=.
MAIN_S_SRCS:=server.c
MAIN_C_SRCS:=client.c

CFLAGS:=-I$(MAIN_DIR)/include -I$(COMMON_DIR)/include -I$(GEN_DIR)
CFLAGS += -I../json-c/output/include/json-c
LIBS:=../json-c/output/lib/libjson-c.a -lpthread

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
	awk -f gen-tools/gen.awk $<
clean:
	rm -fr gen $(SERVER_APP) $(CLIENT_APP) *.o
