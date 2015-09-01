#ifndef __PROTO_H__
#define __PROTO_H__
struct uproto_request_s {
	char name[50];
	int age;
};

struct uproto_response_s {
	int code;
	char msg[20];
};
#endif
