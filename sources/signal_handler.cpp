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

static bool ctrl_c_pressed = false;

/**
 * @brief Handles a Ctrl + C signal interrupt.
 *
 * Change the ctrl_c_pressed var value to true.
 *
 * @param signal The signal number received (SIGINT (2) for Ctrl + C).
 */
static void signal_handler(int signal)
{
	ctrl_c_pressed = true;

	std::cout
		<< '\r'
		<< FT_WARNING
		<< "Signal " << signal << " (Ctrl + C) received."
		<< std::endl;
}

bool ft::keep(void)
{
	static bool first_run = false;

	if (!first_run)
	{
		std::cout << FT_SETUP << "Setting up signals." << std::endl;

		signal(SIGINT, signal_handler);

		first_run = true;

		std::cout << FT_OK << "Signals ready." << std::endl;
		std::cout << std::endl;
	}

	return (!ctrl_c_pressed);
}
