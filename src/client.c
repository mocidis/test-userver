#include "myproto-client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(char *app) {
	printf("%s <connection string>\n", app);
	exit(-1);
}


int main(int argc, char *argv[]) {
    char buffer[50];
	myproto_client_t uclient;
	char *server = argv[1];
    myproto_request_t req;

	if( argc < 2 ) {
		usage(argv[0]);
	}
	myproto_client_open(&uclient, argv[1]);
    strncpy(req.arbiter_update.name, "HOANG XUAN TUNG", sizeof(req.arbiter_update.name));
    
    printf("-- %s\n", req.arbiter_update.name);

    req.msg_id = UUU_SHIT;
    req.uuu_shit.yyy = 38;
    req.uuu_shit.xxx = 0.8;

    printf("%d, %d, %lf\n", req.msg_id, req.uuu_shit.yyy, req.uuu_shit.xxx);

	myproto_client_send(&uclient, &req);

    myproto_client_close(&uclient);

	return 0;
}
