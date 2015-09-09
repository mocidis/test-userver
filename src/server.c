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

static void on_request(myproto_server_t *userver, myproto_request_t *request) {
    switch(request->msg_id) {
    case ARBITER_UPDATE:
        printf("arbiter update\n");
        break;
    case ARBITER_REFRESH:
        printf("arbiter refresh\n");
        break;
    case UUU_SHIT:
        printf("yyy:%d, xxx:%lf\n", request->uuu_shit.yyy, request->uuu_shit.xxx);
        break;
    }
}

int main(int argc, char *argv[]) {
	myproto_server_t userver;
	if( argc < 2 ) {
		usage(argv[0]);
	}

	myproto_server_init(&userver, argv[1]);
	
	userver.on_request = &on_request;

	myproto_server_start(&userver);
	// Main loop goes here
	my_pause();
    myproto_server_join(&userver, "239.0.0.1");
    my_pause();
    myproto_server_leave(&userver, "239.0.0.1");
    my_pause();
	myproto_server_end(&userver);
	
	return 0;
}
