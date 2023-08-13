/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_option.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:33:36 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 21:33:36 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <help_option.hpp>

bool	ft::help_option(const char* option)
{
	if (!option)
		return (false);

	const std::string	str_option = option;

	if (str_option == "-h" || str_option == "--help")
	{
		std::cout<< FT_HELP << std::endl;

		return (true);
	}

	return (false);
}
