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

bool	help_option(const std::string& option)
{
	if (!keep())
		return (false);
	if (option == "-h" || option == "--help")
	{
		std::cout<< MSG_HELP << std::endl;

		return (true);
	}

	return (false);
}
