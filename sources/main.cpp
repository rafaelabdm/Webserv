/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:07:14 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 21:07:14 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <c_external_functions.h>
#include <colors.hpp>
#include <iostream>
#include <man_webserv.hpp>
#include <signal_handler.hpp>

int	main(int argc, char* argv[])
{
	// For "./webserv -h" or "./webserv " -help options
	if (argc > 1 && manual_option(argv[1]))
		return (0);

	// Setup for Ctrl + C and Ctrl + \ signals
	set_signal();

	int i = 42;
	while (!g_shouldTerminate && i)
		i++;
	if (!g_shouldTerminate)
		std::cout << MAGENTA << "Hello World" << RESET_COLOR << std::endl;

	return (0);
}
