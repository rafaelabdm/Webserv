/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:22:59 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 20:22:59 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handler.hpp>

volatile bool g_shouldTerminate = false;

static void	signal_handler(int signal)
{
	char	key = ' ';

	key = (signal == SIGINT) ? 'C' : key;
	key = (signal == SIGQUIT) ? '\\' : key;

	std::cout
		<< '\n' << MSG_WARNING
		<< "Signal " << signal << " (Ctrl + " << key << ") received." << '\n'
		<< "Closing webserv..."
		<< std::endl;
	g_shouldTerminate = true;
}

void	set_signal(void)
{
	std::cout << MSG_SETUP << "Setting up signals." << std::endl;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
