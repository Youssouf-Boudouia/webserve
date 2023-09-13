/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/12 20:03:02 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBIND_HPP
# define SOCKETBIND_HPP

# include "Queue.hpp"
# include <sys/socket.h>
# include <netinet/in.h>
# include "SocketConnection.hpp"

#include <vector>
class SocketBind : public IQueueEventListener {
	private:
		int					_fd;
		struct sockaddr_in	_sin;
		IQueue		&_queue;
		std::vector<SocketConnection*>	_v;

	public:
		SocketBind(IQueue &queue, int port, int backlog);
		~SocketBind();
		void	listen(void);
};

#endif
