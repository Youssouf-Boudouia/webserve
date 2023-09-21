/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/21 18:55:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketConnection.hpp"
#include <iostream>

SocketConnection::SocketConnection(IQueue &queue, int fd_socketBind) : _queue(queue)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, *this);
}

SocketConnection::~SocketConnection()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketConnection::read(void)
{
	_request.recv(_fd);
}

#include <string.h>
const char *response = "HTTP/1.1 200 OK\nContent-Length: 74\n\n<style>h1 { color: blue; font-size: 32px; }</style><h1>Hello, world !</h1>";

void	SocketConnection::write(void)
{

	if (_request.ok)
	{
		_request.ok = false;
		send(_fd, response, strlen(response), 0);
	}

}
