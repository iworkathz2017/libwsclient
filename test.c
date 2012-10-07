#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wsclient/wsclient.h>

int onmessage(wsclient *c, libwsclient_message *msg) {
	fprintf(stderr, "Received (%llu): %s\n", msg->payload_len, msg->payload);
	return 0;
}

int onopen(wsclient *c) {
	fprintf(stderr, "onopen called.\n");
	libwsclient_send(c, "testing");
	return 0;
}

int main(int argc, char **argv) {
	wsclient *client = libwsclient_new("ws://websocket.mtgox.com/mtgox");
	if(!client) {
		fprintf(stderr, "Unable to initialize new WS client.\n");
		exit(1);
	}
	libwsclient_onopen(client, &onopen);
	libwsclient_onmessage(client, &onmessage);
	libwsclient_run(client);
	libwsclient_finish(client);
	return 0;
}

