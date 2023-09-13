/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/12 19:54:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Queue.hpp"

Queue::Queue() : _nevents(MAX_EVENTS) {
	_kq_fd = kqueue();
	if (_kq_fd < 0)
		throw std::runtime_error("Fatal error when creating the kernel event queue");
	_events_list = new struct kevent [_nevents];
}

Queue::Queue(size_t nevents) : _nevents(nevents) {
	_kq_fd = kqueue();
	if (_kq_fd < 0)
		throw std::runtime_error("Fatal error when creating the kernel event queue");
	_events_list = new struct kevent [_nevents];
}

void	Queue::subscribe(int fd, IQueueEventListener &listener) {
	struct kevent evSet = {
		.ident	= fd,
		.filter	= EVFILT_READ,
		.flags	= EV_ADD
	};
	kevent(_kq_fd, &evSet, 1, NULL, 0, NULL);
	_m.insert(std::pair<int, IQueueEventListener&>(fd, listener));
}

void	Queue::unsubscribe(int fd) {
	struct kevent evSet = {
		.ident	= fd,
		.filter	= EVFILT_READ,
		.flags	= EV_DELETE
	};
	kevent(_kq_fd, &evSet, 1, NULL, 0, NULL);
	_m.erase(fd);
}

void	Queue::event_loop(t_event_handler handler)
{
	int	num_events;
	t_listener_map::iterator	listener;

	num_events = kevent(_kq_fd, NULL, 0, _events_list, _nevents, NULL);
	for (int i = 0; i < num_events; i++) {
		listener = _m.find(_events_list[i].ident);
		if (listener != _m.end())
			listener->second.listen();
		handler(*this, _events_list[i]);
	}
}

Queue::~Queue() {
	close(_kq_fd);
	delete [] _events_list;
}


