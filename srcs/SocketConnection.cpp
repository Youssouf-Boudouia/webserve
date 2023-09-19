/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/19 11:48:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketConnection.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <iostream>
#include <string.h>

SocketConnection::SocketConnection(IQueue &queue, int fd_socketBind) : _queue(queue)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, *this);
	std::cout << "New connection" <<std::endl;
}

SocketConnection::~SocketConnection()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketConnection::listen(void)
{
// 	std::string			request("");
// 	ssize_t				bytes_read;
// 	const unsigned int	buff_len = 512;
// 	char				buff[buff_len];

// 	do {
// 		bzero(buff, buff_len);
// 		bytes_read = recv(_fd, buff, buff_len, 0);
// 		request.append(buff, buff_len);
// 	} while (bytes_read > 0);

// 	std::cout << "_______________________________________________" << std::endl;
// 	std::cout << request <<std::endl;

// _queue.unsubscribe(_fd);
// return;
// 	const char *response = "HTTP/1.1 200 OK\nContent-Length: 74\n\n<style>h1 { color: blue; font-size: 32px; }</style><h1>Hello, world !</h1>";

// 	int len = strlen(response);
// 	int bytes_send = 0;
// 	do {
// 		bytes_send = send(_fd, &response[bytes_send], len - bytes_send, 0);
// 	} while (bytes_send > 0);

// 	_queue.unsubscribe(_fd);
// 	//Request	new_request(/*..?..*/);
	Request		new_request(_fd);
	Response	new_response(new_request);

	new_request.readRequest();
	new_request.displayRequest();
	new_response.sendResponse();
	new_response.displayResponse();
}
