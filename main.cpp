/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/12 20:04:44 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SocketBind.hpp"

void	handler(const IQueue& q, const struct kevent& e) {

/*
	if (sockets.find(e.ident) != sockets.end()) {
		int fd = sockets[e.ident].accept()
		q.subscribe(fd);
	} // client disconnected
	else
*/
/*
	if (e.flags & EV_EOF) {
		q.unsubscribe(e.ident);
		socket.erase(e.ident);
	} // read message from client
	else if (e.filter == EVFILT_READ) {
		socket[e.ident].create_request();
	    recv_msg(e.ident);
	}
*/
	(void)q;
	(void)e;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	Queue	queue = Queue();

	SocketBind	sock(queue, 8083, 5);

	while (42)
		queue.event_loop(handler);
	return (EXIT_SUCCESS);
}
