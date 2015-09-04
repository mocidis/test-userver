#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myproto-server.h"
#include "ansi-utils.h"

void usage(char *app) {
	printf("%s <connection string>\n", app);
	exit(-1);
}

static void parsed_request(char *buff, int len, myproto_request_t *req) {
	char name [50];
	int age;

	sscanf(buff, "{name:%s, age:%d}", name, &age);
	strncpy(req->name, name, sizeof(req->name));
	req->age = age;
}

static void on_request(myproto_server_t *userver, myproto_request_t *request, myproto_response_t *response) {
	// Do nothing, just generate a response
	response->code = 1;
	strncpy(response->msg, "Good request", sizeof(response->msg));
}

static int build_response(char *buff, int len, myproto_response_t *response) {
	return snprintf(buff, len, "{code:%d, msg:%s}", response->code, response->msg);
}

int main(int argc, char *argv[]) {
	myproto_server_t userver;
	if( argc < 2 ) {
		usage(argv[0]);
	}

	myproto_server_init(&userver, argv[1]);
	
	userver.parse_request_f = &parsed_request;
	userver.build_response_f = &build_response;
	userver.on_request = &on_request;

	myproto_server_start(&userver);
	// Main loop goes here
	my_pause();
	myproto_server_end(&userver);
	
	return 0;
}
