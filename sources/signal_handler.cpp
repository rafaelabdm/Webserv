/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:41:46 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 18:41:46 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handler.hpp>

static bool	ctrl_c_pressed = false;

static void signal_handler(int signal)
{
	ctrl_c_pressed = true;

	std::cout
		<< '\n' << MSG_WARNING
		<< "Signal " << signal << " (Ctrl + C) received." << '\n'
		<< "Closing webserv..."
		<< std::endl;

		return;
}

bool keep(void)
{
	static bool	first_run = false;

	if (!first_run)
	{
		std::cout << MSG_SETUP << "Setting up signals." << std::endl;

		signal(SIGINT, signal_handler);

		first_run = true;
	}

	return (!ctrl_c_pressed);
}