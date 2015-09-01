#include "uclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(char *app) {
	printf("%s <server ip> <server port>\n", app);
	exit(-1);
}

static int build_request(char *buff, int len, va_list params) {
	// use json here
	int age;
	char *name;
	int n;
	name = va_arg(params, char *);
	printf("name = %s\n", name);
	age = va_arg(params, int);
	printf("age = %d\n", age);

	n = snprintf(buff, len, "{name:%s , age:%d}", name, age );
	return n;
}

static void parse_response(char *buff, int len, uproto_response_t *resp) {
	sscanf(buff, "{code:%d , msg:%s }", &resp->code, resp->msg);
}

int myproto_uclient_send(uclient_t *uclient, char *name, int age) {
	return uclient_send(uclient, name, age);
}
int myproto_uclient_recv(uclient_t *uclient, uproto_response_t *resp) {
	return uclient_recv(uclient, resp);
}

int main(int argc, char *argv[]) {

	uclient_t uclient;
	int port = -1;
	char *server = argv[1];
	if( argc < 3 ) {
		usage(argv[0]);
	}
	port = atoi(argv[2]);
	if(port <= 0) {
		port = 23456;
	}
	printf("--%s-- --%d--\n", server, port);
	uclient.build_request_f = &build_request;
	uclient.parse_response_f = &parse_response;
	uclient_open(&uclient, server, port);

	char name[] = "Bui Danh Quy";
	int age = 23;

	uproto_response_t resp;

	myproto_uclient_send(&uclient, name, age);
	myproto_uclient_recv(&uclient, &resp);

	printf("Received return code:%d , msg:%s from server\n", resp.code, resp.msg);

	return 0;
}
