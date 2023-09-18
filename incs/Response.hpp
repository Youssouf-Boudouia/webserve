/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:47:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/09/18 14:20:47 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <iostream>
# include <string>
# include <exception>
# include <fstream>
# include <sstream>
# include <sys/socket.h>
# include <sys/types.h>
# include "Request.hpp"

// Seulement à gerer GET, POST, et DELETE, c'est écrit dans le sujet
class Response
{
	private:
		Request											*_request;
		std::string										_response;
		std::map<std::string, void (Response::*)(void)>	_methods;
		std::map<int, std::string>						_status;
		std::map<std::string, std::string>				_headers;
		std::string										_body;

		void		_methodGet(void);
		void		_methodPost(void);
		void		_methodDelete(void);
	public:
		Response(void);
		Response(Request &request);
		Response(Response const &src);
		~Response(void);

		Response	&operator=(Response const &src);

		// Setter
		void		setRequest(Request &request);

		// Getter
		void		displayResponse(void);

		// Methods
		void		sendResponse(void);
};

#endif