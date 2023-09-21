/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/21 17:26:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/socket.h>
# include <string>
# include <cstring>
# include <map>

class Request {
	private:
		std::string							_request;
		std::string							_method;
		std::map<std::string, std::string>	_content;

	public:
		bool	ok;
		Request(void);
		~Request(void);

		void	recv(int _fd);
		bool	getNextLine(std::string &line);
		void	print(void);
};
#endif
