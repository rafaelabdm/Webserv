/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:24:26 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 18:24:26 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <help_option.hpp>
#include <signal_handler.hpp>
#include <valid_argc.hpp>

int	main(const int argc, const char** argv)
{
	if (!valid_argc(argc))
		return (1);
	if (help_option(argv[1]))
		return (0);

	std::cout << "Press Ctrl + C to exit the program." << std::endl;
	while (keep());

	return (0);
}
