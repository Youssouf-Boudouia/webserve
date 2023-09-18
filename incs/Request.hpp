/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:00:02 by obouhlel          #+#    #+#             */
/*   Updated: 2023/09/18 12:55:16 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <exception>
# include <sys/socket.h>
# include <sys/types.h>
# include <error.h>
# include <map>

# define BUFFER_SIZE 1024

class Request
{
private:
	int			_fd;
	std::string	_request;
	std::string	_method;
	std::string	_path;
	std::string	_version;
	std::string	_body;

	void		parseRequest(void);
public:
	Request(void);
	Request(int fd);
	Request(Request const &src);
	~Request(void);
		
	Request	&operator=(Request const &src);

	// Setter
	void		setFd(int fd);

	// Getter
	int			getFd(void) const;
	std::string	getMethod(void) const;
	std::string	getPath(void) const;
	std::string	getVersion(void) const;
	std::string	getBody(void) const;
	void		displayRequest(void);

	// Methods
	void		readRequest(void);
};

#endif