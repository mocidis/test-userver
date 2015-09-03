#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "userver.h"
#include "ansi-utils.h"

void usage(char *app) {
	printf("%s <connection string>\n", app);
	exit(-1);
}

static void parsed_request(char *buff, int len, uproto_request_t *req) {
	char name [50];
	int age;

	sscanf(buff, "{name:%s, age:%d}", name, &age);
	strncpy(req->name, name, sizeof(req->name));
	req->age = age;
}

static void on_request(userver_t *userver, uproto_request_t *request, uproto_response_t *response) {
	// Do nothing, just generate a response
	response->code = 1;
	strncpy(response->msg, "Good request", sizeof(response->msg));
}

static int build_response(char *buff, int len, uproto_response_t *response) {
	return snprintf(buff, len, "{code:%d, msg:%s}", response->code, response->msg);
}

int main(int argc, char *argv[]) {
	userver_t userver;
	if( argc < 2 ) {
		usage(argv[0]);
	}

	userver_init(&userver, argv[1]);
	
	userver.parse_request_f = &parsed_request;
	userver.build_response_f = &build_response;
	userver.on_request = &on_request;

	userver_start(&userver);
	// Main loop goes here
	my_pause();
	userver_end(&userver);
	
	return 0;
}
