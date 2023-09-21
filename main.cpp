/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/21 18:34:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "SocketBind.hpp"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	int	port = 8081;

	Queue	queue = Queue();

	SocketBind	sock(queue, port, 5);

	std::cout << "localhost:" << port << std::endl;
	while (42)
		queue.event_loop();
	return (0);
}
