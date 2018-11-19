#include "WiFiClient.h"

extern WiFiClass WiFi;

#ifndef WIFI_TCP_BUFFER_SIZE
#define WIFI_TCP_BUFFER_SIZE        1508
#endif

arduino::WiFiClient::WiFiClient() {
	sock = new TCPSocket(WiFi.getNetwork());
	sock->sigio(mbed::callback(this, &WiFiClient::getStatus));
	sock->set_blocking(false);
}

uint8_t arduino::WiFiClient::status() {
	return _status;
}

void arduino::WiFiClient::getStatus() {
}


int arduino::WiFiClient::connect(IPAddress ip, uint16_t port) {
}

int arduino::WiFiClient::connect(const char *host, uint16_t port) {
	sock->connect(host, port);
}

int arduino::WiFiClient::connectSSL(IPAddress ip, uint16_t port) {

}

int arduino::WiFiClient::connectSSL(const char *host, uint16_t port) {
	sock_ssl->open(WiFi.getNetwork());
	sock_ssl->connect(host, port);
}

size_t arduino::WiFiClient::write(uint8_t c) {
	sock->send(&c, 1);
}

size_t arduino::WiFiClient::write(const uint8_t *buf, size_t size) {
	sock->send(buf, size);
}

int arduino::WiFiClient::available() {
	uint8_t data[256];
	int ret = sock->recv(data, 256);
    for (int i = 0; i < ret; i++) {
      rxBuffer.store_char(data[i]);
    }
    return rxBuffer.available();
}

int arduino::WiFiClient::read() {
	if (!available()) {
    	return -1;
	}

	return rxBuffer.read_char();
}

int arduino::WiFiClient::read(uint8_t *data, size_t len) {
	int avail = available();

	if (!avail) {
		return -1;
	}

	if ((int)len > avail) {
		avail = len;
	}

	for (size_t i = 0; i < len; i++) {
		data[i] = rxBuffer.read_char();
	}

	return len;
}

int arduino::WiFiClient::peek() {
	return rxBuffer.peek();
}

void arduino::WiFiClient::flush() {

}

void arduino::WiFiClient::stop() {
	sock->close();
}

uint8_t arduino::WiFiClient::connected() {
	return 1;
}

IPAddress arduino::WiFiClient::remoteIP() {
	return IPAddress((uint32_t)0);
}

uint16_t arduino::WiFiClient::remotePort() {
	return 0;
}