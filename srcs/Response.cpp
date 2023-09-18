/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:26:13 by obouhlel          #+#    #+#             */
/*   Updated: 2023/09/18 14:36:35 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "Response.hpp"
#include "Colors.hpp"

Response::Response(void) : _response(""), _methods(), _status(), _headers(), _body()
{
	this->_methods["GET"] = &Response::_methodGet;
	this->_methods["POST"] = &Response::_methodPost;
	this->_methods["DELETE"] = &Response::_methodDelete;

	this->_status[200] = "OK";
	this->_status[201] = "Created";
	this->_status[202] = "Accepted";
	this->_status[204] = "No Content";
	this->_status[301] = "Moved Permanently";
	this->_status[302] = "Found";
	this->_status[304] = "Not Modified";
	this->_status[400] = "Bad Request";
	this->_status[401] = "Unauthorized";
	this->_status[403] = "Forbidden";
	this->_status[404] = "Not Found";
	this->_status[405] = "Method Not Allowed";
	this->_status[413] = "Payload Too Large";
	this->_status[414] = "URI Too Long";
	this->_status[500] = "Internal Server Error";
	this->_status[501] = "Not Implemented";
	this->_status[503] = "Service Unavailable";

	this->_request = NULL;
}

Response::Response(Request &request) : _response(""), _methods(), _status(), _headers(), _body()
{
	this->_methods["GET"] = &Response::_methodGet;
	this->_methods["POST"] = &Response::_methodPost;
	this->_methods["DELETE"] = &Response::_methodDelete;

	this->_status[200] = "OK";
	this->_status[201] = "Created";
	this->_status[202] = "Accepted";
	this->_status[204] = "No Content";
	this->_status[301] = "Moved Permanently";
	this->_status[302] = "Found";
	this->_status[304] = "Not Modified";
	this->_status[400] = "Bad Request";
	this->_status[401] = "Unauthorized";
	this->_status[403] = "Forbidden";
	this->_status[404] = "Not Found";
	this->_status[405] = "Method Not Allowed";
	this->_status[413] = "Payload Too Large";
	this->_status[414] = "URI Too Long";
	this->_status[500] = "Internal Server Error";
	this->_status[501] = "Not Implemented";
	this->_status[503] = "Service Unavailable";

	this->_request = &request;
}

Response::Response(Response const &src) { *this = src; }

Response::~Response(void) {}

Response	&Response::operator=(Response const &src)
{
	if (this != &src)
	{
		this->_response = src._response;
		this->_methods = src._methods;
		this->_status = src._status;
		this->_headers = src._headers;
		this->_body = src._body;
	}
	return (*this);
}

// Setter
void	Response::setRequest(Request &request) { this->_request = &request; }

// Getter
void	Response::displayResponse(void) { std::cout << GREEN << this->_response << RESET << std::endl; }

// Methods
void	Response::sendResponse(void)
{
	if (this->_request == NULL)
	{
		std::cerr << RED << BOLD << "No request" << RESET << std::endl;
		return ;
	}
	std::string		version = this->_request->getVersion();
	std::string		method = this->_request->getMethod();
	std::string		path = this->_request->getPath();
	ssize_t			ret;

	this->_response = version + " " + "200" + " " + this->_status[200] + "\r\n";
	if (this->_methods.find(method) != this->_methods.end())
        (this->*_methods[method])();
	
	ret = send(this->_request->getFd(), this->_response.c_str(), this->_response.size(), 0);
	if (ret < 0)
		std::cerr << RED << BOLD << "Error when sending the response" << RESET << std::endl;
}

void	Response::_methodGet(void)
{
	std::string		path = "./html" + this->_request->getPath();
	std::string		extension("");

	// If the path is a / it's a index.html
	if (path == "./html/")
		path += "index.html";
	std::cout << "PATH: " << path << std::endl;
	// Find the extension of the file
	if (path.find_last_of(".") != std::string::npos)
		extension = path.substr(path.find_last_of(".") + 1);

	// Give the right content type
	if (extension == "html")
		this->_headers["Content-Type"] = "text/html";
	else if (extension == "css")
		this->_headers["Content-Type"] = "text/css";
	else if (extension == "webp")
		this->_headers["Content-Type"] = "image/webp";

	// Open the file and read it
	std::ifstream	file(path.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		this->_response.clear();
		this->_response = this->_request->getVersion() + " " + "404" + " " + this->_status[404] + "\r\n";
		return ;
	}

	// Get the size of the file
	file.seekg(0, std::ios::end);
	int	content_lenght = file.tellg();
	file.seekg(0, std::ios::beg);

	// Convert the size of the file to a string
	std::stringstream	itoa;	
	itoa << content_lenght;
	this->_headers["Content-Length"] = itoa.str();
	
	// Set the headers
	this->_response += "Content-Type: " + this->_headers["Content-Type"] + "\r\n";
	this->_response += "Content-Length: " + this->_headers["Content-Length"] + "\r\n";
	this->_response += "\r\n\r\n";

	// Read the file and put it in the response
	std::string		line;
	while (std::getline(file, line))
		this->_response += line;
	file.close();
}

void	Response::_methodPost(void)
{
	std::cout << "TO DO POST" << std::endl;
}

void	Response::_methodDelete(void)
{
	std::cout << "TO DO DELETE" << std::endl;
}