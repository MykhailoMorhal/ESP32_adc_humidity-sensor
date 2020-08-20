
#ifndef MAIN_SOCKET_SET_GET_H_
#define MAIN_SOCKET_SET_GET_H_

/*----------------------------------------------------------------------
                                Functions
*----------------------------------------------------------------------*/

/**
 * @brief Create a listening socket.  We then wait for a client to connect.
 * Once a client has connected, we then read until there is no more data
 * and log the data read.  We then close the client socket and start
 * waiting for a new connection.
 */
void socket_server(void);

/**
 * @brief Init socket client
 */
void socket_client(void);

/**
 * @brief Create TCP client
 */
void create_tcp_client();

#endif /* MAIN_SOCKET_SET_GET_H_ */
