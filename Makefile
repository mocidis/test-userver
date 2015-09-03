.PHONY: all clean

COMMON_DIR:=../common
COMMON_SRCS:=ansi-utils.c

USERVER_DIR:=../userver
USERVER_S_SRCS:=userver.c
USERVER_C_SRCS:=uclient.c

MAIN_DIR:=.
MAIN_S_SRCS:=server.c
MAIN_C_SRCS:=client.c

CFLAGS:=-I$(MAIN_DIR)/include -I$(COMMON_DIR)/include -I$(USERVER_DIR)/include
CFLAGS += -I../json-c/output/include/json-c
LIBS:=../json-c/output/lib/libjson-c.a -lpthread

SERVER_APP:=server
CLIENT_APP:=client

all: $(SERVER_APP) $(CLIENT_APP)

$(SERVER_APP): $(COMMON_SRCS:.c=.o) $(USERVER_S_SRCS:.c=.o) $(MAIN_S_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(CLIENT_APP): $(COMMON_SRCS:.c=.o) $(USERVER_C_SRCS:.c=.o) $(MAIN_C_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(COMMON_SRCS:.c=.o): %.o: $(COMMON_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(USERVER_S_SRCS:.c=.o): %.o: $(USERVER_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(USERVER_C_SRCS:.c=.o): %.o: $(USERVER_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_C_SRCS:.c=.o): %.o: $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_S_SRCS:.c=.o): %.o: $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr $(SERVER_APP) $(CLIENT_APP) *.o
