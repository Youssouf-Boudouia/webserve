/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:07:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/12 17:24:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

extern "C" {
# include <kqueue/sys/event.h>
}
# include <unistd.h>

# include <map>
# include <stdexcept>

# define MAX_EVENTS 32

class IQueueEventListener {
	public:
		virtual void	listen(void)	= 0;
};

class IQueue {
	public:
		virtual void	subscribe(int fd, IQueueEventListener &event)	= 0;
		virtual void	unsubscribe(int fd)	= 0;
};

typedef	void	(*t_event_handler)(const IQueue&, const struct kevent&);

class Queue : public IQueue {
	private:
		int				_kq_fd;
		struct kevent	*_events_list;
		size_t			_nevents;

		typedef	std::map <int, IQueueEventListener&>	t_listener_map;
		t_listener_map	_m;

	public:
		Queue();
		Queue(size_t nevents);
		~Queue();

		void	subscribe(int fd, IQueueEventListener &listener);
		void	unsubscribe(int fd);
		void	event_loop(t_event_handler handler);
};
#endif
