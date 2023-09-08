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
#define HELP_OPTION_HPP

#include <iostream>

namespace ft
{
	/**
	 * @brief Check if the given option is a help option.
	 *
	 * This function checks whether the provided option is equivalent to the
	 * help option ("-h" or "--help").
	 *
	 * @param options The command-line option to check.
	 * @return True if the option is a help option or false if not.
	 *
	 */
	bool help_option(const char **);
}

#endif // HELP_OPTION_HPP
