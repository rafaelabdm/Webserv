/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argc.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:20:28 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 21:20:28 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALID_ARGC_HPP
# define VALID_ARGC_HPP

# include <colors.hpp>
# include <iostream>
# include <messages.hpp>
# include <signal_handler.hpp>

/**
 * @brief Check if argc is equal to 2.
 *
 *
 * @param argc Number of arguments passed to the program.
 * @return Returns true if argc is equal to 2 or false if not.
 *
 * @note This function relies on the keep() function to check if Ctrl + C has
 *       been pressed.
 */
bool	valid_argc(const int argc);

#endif // VALID_ARGC_HPP
