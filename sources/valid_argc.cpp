/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argc.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:20:36 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 21:20:36 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <valid_argc.hpp>

bool	ft::valid_argc(const int argc)
{
	if (argc == 2)
		return (true);

	std::string	error = "unknown";

	error = (argc == 1) ? "Missing configuration file operand." : error;
	error = (argc > 2) ? "Too many arguments." : error;

	std::cout << FT_WARNING << error << std::endl;
	std::cout << "Try './webserv --help' for more information." << std::endl;

	return (false);

}
