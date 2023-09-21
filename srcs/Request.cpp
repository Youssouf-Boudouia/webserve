/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/21 18:34:04 by yboudoui         ###   ########.fr       */
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
	_request.append(buff, bytes_read);

	std::cout << "\033[1;31m" << _request <<"\033[0m"<<std::endl;

	ok =false;
	std::string	line;
	while (getNextLine(line))
	{
		if (line.size() == 0)
		{
			ok = true;
			print();
			_method.clear();
			_content.clear();
			_request.clear();
			return ;
		}
		if (EndsWith(line, "HTTP/1.1") && _method.empty())
			_method = line;
		else {
			std::size_t	colomn = line.find(":");
			if (colomn != std::string::npos)
				_content[line.substr(0, colomn)] = line.substr(colomn + 1);
		}
	}
}

bool	Request::getNextLine(std::string &line)
{
	line.clear();
	std::size_t	endl = _request.find("\r\n");
	if (endl == std::string::npos)
		return (false);
	line = _request.substr(0, endl);
	_request.erase(0, endl + 2);
	return (true);
}

# define TAB_SIZE 4
#include <iomanip>
void	Request::print(void)
{
	std::cout << "\t" <<  _method << std::endl;
	std::map<std::string, std::string>::iterator content_it;
	for (content_it = _content.begin(); content_it != _content.end(); content_it++)
		std::cout << "\t" << "\033[1;34m" <<content_it->first << "\033[0m"<< ":" << content_it->second << std::endl;
}

