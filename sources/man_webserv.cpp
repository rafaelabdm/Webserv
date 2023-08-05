/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_webserv.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:02:49 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 20:02:49 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <man_webserv.hpp>

bool	manual_option(const std::string& option)
{
	if (option == "-h" || option == "--help")
	{
		std::cout<< HELP_MSG << std::endl;

		return (true);
	}

	return (false);
}
