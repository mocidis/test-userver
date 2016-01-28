#include "myproto-client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(char *app) {
	printf("%s <connection string>\n", app);
	exit(-1);
}

char *my_id() {
    return "clientapp";
}

char *my_pph() {
    return "passphrase";
}

int main(int argc, char *argv[]) {
	myproto_client_t uclient;
    myproto_request_t req;

	if( argc < 2 ) {
		usage(argv[0]);
	}
	//myproto_client_open(&uclient, argv[1]);
	myproto_client_open_ex(&uclient, argv[1], &my_id, &my_pph);
    
    req.msg_id = ARBITER_UPDATE;
    strncpy(req.arbiter_update.name, "HOANG XUAN TUNG", sizeof(req.arbiter_update.name));
    req.arbiter_update.age = 38;

	//myproto_client_send(&uclient, &req);
	myproto_client_send_ex(&uclient, &req);

    myproto_client_close(&uclient);

	return 0;
}
