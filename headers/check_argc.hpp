/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:25:18 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/09/07 14:25:18 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_ARGC_HPP
# define CHECK_ARGC_HPP

# include <iostream>
# include <messages.hpp>

# define FT_HELP_HINT	"Try './webserv --help' for more information."
# define FT_MANY_ARGS	FT_WARNING "Too many arguments.\n" FT_HELP_HINT

namespace	ft
{
	/**
	 * @brief Verify the number of arguments
	 * 
	 * @param argc Number of arguments
	 * @return true if argc is bigger than 2
	 * @return false if is equal or lower than 2
	 */
	bool	check_argc(const int argc);
}

#endif // CHECK_ARGC_HPP
