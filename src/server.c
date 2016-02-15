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

static void on_request(myproto_server_t *userver, myproto_request_t *request, char *peer_host) {
    switch(request->msg_id) {
    case ARBITER_UPDATE:
        printf("arbiter update\n");
        printf("name:%s, age:%d\n", request->arbiter_update.name, request->arbiter_update.age);
        break;
    case ARBITER_REFRESH:
        printf("arbiter refresh\n");
        printf("address: %s, weight:%lf\n", request->arbiter_refresh.address, request->arbiter_refresh.weight);
        break;
    case UUU_SHIT:
        printf("uuu shit\n");
        printf("yyy:%d, xxx:%lf\n", request->uuu_shit.yyy, request->uuu_shit.xxx);
        break;
    }
}

char *get_pph(pj_str_t *id) {
    (void) id;
    return "passphrase";
}

int main(int argc, char *argv[]) {
    pj_caching_pool cp;
    pj_pool_t *pool;
	myproto_server_t userver;
	if( argc < 2 ) {
		usage(argv[0]);
	}
    
    pj_init();
    pj_caching_pool_init(&cp, 0, 4096);

    pool = pj_pool_create(&cp.factory, "pool", 256, 256, NULL);

    myproto_server_init(&userver, argv[1], pool, &get_pph);
    //myproto_server_init_ex(&userver, argv[1], pool, &get_pph);
	
	userver.on_request_f = &on_request;

	myproto_server_start(&userver);
	//myproto_server_start_ex(&userver);

	// Main loop goes here
	my_pause();
    myproto_server_join(&userver, "239.0.0.1");
    my_pause();
    myproto_server_leave(&userver, "239.0.0.1");
    my_pause();
	myproto_server_end(&userver);
	
	return 0;
}
