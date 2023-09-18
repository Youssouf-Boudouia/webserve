/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/17 19:49:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#include <iostream>

bool EndsWith(const std::string& data, const std::string& suffix)
{
    return data.find(suffix, data.size() - suffix.size()) != std::string::npos;
}


Request::Request(void): ok(false){}

Request::~Request(void) {}

void	Request::recv(int _fd) {
	size_t				bytes_read = 0;
	const unsigned int	buff_len = 512;
	char				buff[buff_len] = {0};

	bytes_read = ::recv(_fd, buff, buff_len, 0);
	std::cout << bytes_read << std::endl;
	_request.append(buff, bytes_read);
	ok = EndsWith(_request, "\r\n");
	if (ok)
	{
		std::cout << _request << std::endl;
		_request.clear();
	}
}
