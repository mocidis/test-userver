#include "myproto-client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void usage(char *app) {
	printf("%s <connection string>\n", app);
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

static void parse_response(char *buff, int len, myproto_response_t *resp) {
	sscanf(buff, "{code:%d , msg:%s }", &resp->code, resp->msg);
}

int myproto_send(myproto_client_t *uclient, char *name, int age) {
	return myproto_client_send(uclient, name, age);
}
int myproto_recv(myproto_client_t *uclient, myproto_response_t *resp) {
	return myproto_client_recv(uclient, resp);
}

int main(int argc, char *argv[]) {

	myproto_client_t uclient;
	char *server = argv[1];
	if( argc < 2 ) {
		usage(argv[0]);
	}
	uclient.build_request_f = &build_request;
	uclient.parse_response_f = &parse_response;
	myproto_client_open(&uclient, argv[1]);

	char name[] = "Bui Danh Quy";
	int age = 23;

	myproto_response_t resp;

	myproto_send(&uclient, name, age);
	myproto_recv(&uclient, &resp);

	printf("Received return code:%d , msg:%s from server\n", resp.code, resp.msg);

	return 0;
}
