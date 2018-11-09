/*
 * socket_set_get.c
 *
 *  Created on: 20 бер. 2018 р.
 *      Author: Mykhailo
 */

#include <lwip/sockets.h>

#include <string.h>
#include <errno.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include <driver/adc.h>
#include "socket_set_get.h"
#include <stdbool.h>

#define PORT_NUMBER 8001
#define IP_ADDRESS_FOR_CLIENT "192.168.127.109"
#define PORT_NUMBER_FOR_CLIENT 23

static char tag_server[] = "socket_server";
static char tag_client[] = "socket_client";
static int connect_socket_client;
static struct sockaddr_in server_addr;

extern char value_channel_0_char[10];
extern char value_channel_3_char[10];
extern char value_channel_6_char[10];
extern char value_channel_7_char[10];

char *arg1 = "1 adc\n";
char *arg2 = "2 adc\n";
char *arg3 = "3 adc\n";
char *arg4 = "4 adc\n";

_Bool status_send_loop;
int arg_waiting_for_connect;

int show_socket_error_reason(int socket);
int get_socket_error_code(int socket);
int check_working_socket();
void close_socket();
void socket_client_ini();

/**
 * Create a listening socket.  We then wait for a client to connect.
 * Once a client has connected, we then read until there is no more data
 * and log the data read.  We then close the client socket and start
 * waiting for a new connection.
 */



void socket_server(void) {
	struct sockaddr_in clientAddress;//this value accept data from client
	struct sockaddr_in serverAddress;

	// Create a socket that we will listen upon.
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ESP_LOGI(tag_server, "SOCKET: rc: %d", sock);

	if (sock < 0) {
		ESP_LOGE(tag_server, "socket: %d %s", sock, strerror(errno));//check error
		goto END;
	}

	// Bind our server socket to a port.
	serverAddress.sin_family = AF_INET;//IPv4
	serverAddress.sin_addr.s_addr = htonl(IPADDR_ANY);
	serverAddress.sin_port = htons(PORT_NUMBER);
	int rc  = bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	ESP_LOGI(tag_server, "BIND: rc: %d", rc);

	if (rc < 0) {
		ESP_LOGE(tag_server, "bind: %d %s", rc, strerror(errno));
		goto END;
	}

	// Flag the socket as listening for new connections.

	while(1)
	{
		rc = listen(sock, 5);//int listen(int sockfd, int backlog (this is how many clients may connected));
		ESP_LOGI(tag_server, "LISTEN: rc: %d", rc);
		vTaskDelay(2000/portTICK_PERIOD_MS);
	}

	//rc = listen(sock, 5);//int listen(int sockfd, int backlog (this is how many clients may connected));
	//ESP_LOGI(tag_server, "LISTEN: rc: %d", rc);

	if (rc < 0) {
		ESP_LOGE(tag_server, "listen: %d %s", rc, strerror(errno));
		goto END;
	}



	while (1) {
		// Listen for a new client connection.
		socklen_t clientAddressLength = sizeof(clientAddress);
		int clientSock = accept(sock, (struct sockaddr *)&clientAddress, &clientAddressLength);
		ESP_LOGI(tag_server, "ACCEPT: rc: %d", clientSock);

		if (clientSock < 0) {
			ESP_LOGE(tag_server, "accept: %d %s", clientSock, strerror(errno));
			goto END;
		}

		// We now have a new client ...
		int total =	10*1024;
		int sizeUsed = 0;
		char *data = malloc(total);// create area memory for data wich we accept



		// Loop reading data.
		while(1) {
			ssize_t sizeRead = recv(clientSock, data + sizeUsed, total-sizeUsed, 0);
			ESP_LOGI(tag_server, "RECV: rc: %d", sizeRead);

			if (sizeRead < 0) {
				ESP_LOGE(tag_server, "recv: %d %s", sizeRead, strerror(errno));
				break;
			}
			if (sizeRead == 0) {
				break;
			}
			sizeUsed += sizeRead;

			printf("data recv: ");
			printf(data);
			printf("\n");

		}

		// Finished reading data.
		ESP_LOGD(tag_server, "Data read (size: %d) was: %.*s", sizeUsed, sizeUsed, data);
		free(data);
		int close_socket=close(clientSock);
		ESP_LOGI(tag_server, "CLOSE: rc: %d",close_socket);

	}
	END:
	vTaskDelete(NULL);
}



void create_tcp_client()
{
	socket_client_ini();

    // Send data to server
    while(!status_send_loop){

    	int rc = connect(connect_socket_client, (struct sockaddr *)&server_addr, sizeof(server_addr));

    	if(rc<0){
    		printf("Connect error! %d",rc);
    		get_socket_error_code(rc);
    		socket_client_ini();
    		arg_waiting_for_connect++;
    		if(arg_waiting_for_connect>1){
    			status_send_loop = 1;
    		}

    	}else{
    		printf("Connect success! %d",rc);

    		for(int i = 0;i<1;i++){

    			char value_for_choice[4] = "3";
    			rc = send(connect_socket_client, value_for_choice, strlen(value_for_choice), 0);
    			printf("%s",value_for_choice);
    			printf("\n");
    			vTaskDelay(500/portTICK_PERIOD_MS);

    			rc = send(connect_socket_client, value_channel_0_char, strlen(value_channel_0_char), 0);
    			printf("%s",value_channel_0_char);
    			printf("\n");
    			vTaskDelay(500/portTICK_PERIOD_MS);

    			rc = send(connect_socket_client, value_channel_3_char, strlen(value_channel_3_char), 0);
    			printf("%s",value_channel_3_char);
    			printf("\n");
    			vTaskDelay(500/portTICK_PERIOD_MS);

    			rc = send(connect_socket_client, value_channel_6_char, strlen(value_channel_6_char), 0);
    			printf("%s",value_channel_6_char);
    			printf("\n");
    			vTaskDelay(500/portTICK_PERIOD_MS);

    			rc = send(connect_socket_client, value_channel_7_char, strlen(value_channel_7_char), 0);
    			printf("%s",value_channel_7_char);
    			printf("\n");
    			vTaskDelay(500/portTICK_PERIOD_MS);
    		}

    		close(connect_socket_client);// close socket
    		status_send_loop = 1;
    		break;
    	}

    	vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void socket_client_ini(){

	ESP_LOGI(tag_client, "client socket....serverip:port=%s:%d\n",
	    		IP_ADDRESS_FOR_CLIENT, PORT_NUMBER_FOR_CLIENT);
	    connect_socket_client = socket(AF_INET, SOCK_STREAM, 0);
	    if (connect_socket_client < 0) {
	    	show_socket_error_reason(connect_socket_client);
	    }


	    server_addr.sin_family = AF_INET;
	    server_addr.sin_port = htons(PORT_NUMBER_FOR_CLIENT);
	    inet_pton(AF_INET,IP_ADDRESS_FOR_CLIENT, &server_addr.sin_addr.s_addr);
	    ESP_LOGI(tag_client, "connecting to server...");

	    status_send_loop = 0;
}

int get_socket_error_code(int socket)
{
    int result;
    u32_t optlen = sizeof(int);
    if(getsockopt(socket, SOL_SOCKET, SO_ERROR, &result, &optlen) == -1) {
	ESP_LOGE(tag_client, "getsockopt failed");
	return -1;
    }
    return result;
}

int show_socket_error_reason(int socket)
{
    int err = get_socket_error_code(socket);
    ESP_LOGW(tag_client, "socket error %d %s", err, strerror(err));
    return err;
}

int check_working_socket()
{
    int ret;
#if EXAMPLE_ESP_TCP_MODE_SERVER
    ESP_LOGD(TAG, "check server_socket");
    ret = get_socket_error_code(server_socket);
    if(ret != 0) {
	ESP_LOGW(TAG, "server socket error %d %s", ret, strerror(ret));
    }
    if(ret == ECONNRESET)
	return ret;
#endif
    ESP_LOGD(tag_client, "check connect_socket");
    ret = get_socket_error_code(connect_socket_client);
    if(ret != 0) {
	ESP_LOGW(tag_client, "connect socket error %d %s", ret, strerror(ret));
    }
    if(ret != 0)
	return ret;
    return 0;
}

void close_socket()
{
    close(connect_socket_client);
    //close(server_socket);
}
