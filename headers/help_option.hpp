/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_option.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:33:39 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 21:33:39 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_OPTION_HPP
# define HELP_OPTION_HPP

# include <colors.hpp>
# include <iostream>
# include <messages.hpp>

# define FT_HELP \
"\
Usage: webserv <Configuration File>.conf \n\
\n\
A project about basic HTTP server creation. \n\
\n\
	-h, --help	display this help page and exit. \n\
\n\
More about this project can be found on \n\
https://github.com/rafaelabdm/Webserv/\
"

namespace	ft
{
	/**
	 * @brief Check if the given option is a help option.
	 *
	 * This function checks whether the provided option is equivalent to the
	 * help option ("-h" or "--help").
	 *
	 * @param option The command-line option to check.
	 * @return True if the option is a help option or false if not.
	 *
	 */
	bool	help_option(const char* option);
}

#endif // HELP_OPTION_HPP