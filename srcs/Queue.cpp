/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/22 08:43:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Queue.hpp"

#include <iostream>
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
		.filter	= EVFILT_READ | EV_CLEAR,
		.flags	= EV_ADD
	};
	kevent(_kq_fd, &evSet, 1, NULL, 0, NULL);

	struct kevent evSet2 = {
		.ident	= fd,
		.filter	= EVFILT_WRITE | EV_CLEAR,
		.flags	= EV_ADD
	};
	kevent(_kq_fd, &evSet2, 1, NULL, 0, NULL);

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

void	Queue::event_loop(void)
{
	int	num_events;
	t_listener_map::iterator	listener;

	num_events = kevent(_kq_fd, NULL, 0, _events_list, _nevents, NULL);
	for (int i = 0; i < num_events; i++)
	{
		listener = _m.find(_events_list[i].ident);
		if (listener == _m.end())
			continue ;
		if (_events_list[i].flags & EV_EOF)
		{
			std::cout << "EOF" << std::endl;
//			unsubscribe(_events_list[i].ident);
//			continue ;
		}
		if (_events_list[i].filter & EVFILT_READ)
		{
			std::cout << "READ" << std::endl;
			listener->second.read();
		}
		if (_events_list[i].filter & EVFILT_WRITE)
		{
			std::cout << "WRITE" << std::endl;
			listener->second.write();
		}
	}
}

Queue::~Queue() {
	close(_kq_fd);
	delete [] _events_list;
}


