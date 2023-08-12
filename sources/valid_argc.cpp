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

bool	valid_argc(const int argc)
{
	if (!keep())
		return (false);
	if (argc != 2)
	{
		std::cout << MSG_WARNING << " missing configuration file operand" << std::endl;
		std::cout << "Try './webserv --help' for more information." << std::endl;
		return (false);
	}

	return (true);
}
