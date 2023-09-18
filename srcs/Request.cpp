/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:06:06 by obouhlel          #+#    #+#             */
/*   Updated: 2023/09/18 14:31:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "Colors.hpp"

Request::Request(void) : _fd(0), _method(""), _path(""), _version(""), _body("") {}

Request::Request(int fd) : _fd(fd), _method(""), _path(""), _version(""), _body("") {}

Request::Request(Request const &src) { *this = src; }

Request::~Request(void) {}

Request &Request::operator=(Request const &src)
{
	if (this != &src)
	{
		this->_fd = src._fd;
		this->_method = src._method;
		this->_path = src._path;
		this->_version = src._version;
		this->_body = src._body;
	}
	return (*this);
}

// Setter
void	Request::setFd(int fd) { this->_fd = fd; }

// Getter
int			Request::getFd(void) const { return (this->_fd); }
std::string	Request::getMethod(void) const { return (this->_method); }
std::string	Request::getPath(void) const { return (this->_path); }
std::string	Request::getVersion(void) const { return (this->_version); }
std::string	Request::getBody(void) const { return (this->_body); }

// Methods
void	Request::readRequest(void)
{
	int		ret;
	char	buffer[BUFFER_SIZE + 1];

	ret = recv(this->_fd, buffer, BUFFER_SIZE, 0);
	if (ret == -1)
	{
		std::cerr << RED << BOLD << "Error when reading request" << RESET << std::endl;
		return ;
	}
	else if (ret > 0)
	{
		buffer[ret] = '\0';
		this->_request += buffer;
	}
	else
		std::cout << "All data receved" << std::endl;
	this->parseRequest();
}

void	Request::parseRequest(void)
{
	std::string		line;

	try
	{
		line = this->_request.substr(0, this->_request.find("\r\n"));
		this->_method = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
		this->_path = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
		this->_version = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
		if (this->_method == "POST")
			this->_body = this->_request.substr(this->_request.find("\r\n\r\n") + 4);
	}
	catch (std::exception &e)
	{
		std::cerr << RED << BOLD << "Error when parsing request" << RESET << std::endl;
		return ;
	}
	// std::cout << CYAN;
	// std::cout << "Method: `" << this->_method << "`" << std::endl;
	// std::cout << "Path: `" << this->_path << "`" << std::endl;
	// std::cout << "Version: `" << this->_version << "`" << std::endl;
	// std::cout << "Body: `" << this->_body << "`" << std::endl;
	// std::cout << RESET;
}

void	Request::displayRequest(void)
{
	std::cout << YELLOW << "Request from fd n°" << this->_fd << RESET << std::endl;
	std::cout << YELLOW << this->_request << RESET << std::endl;
}