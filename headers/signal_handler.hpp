/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:44:59 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 18:44:59 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_HPP
# define SIGNAL_HANDLER_HPP

# include <colors.hpp>
# include <iostream>
# include <messages.hpp>

# include <signal.h>
/**
 * Installs a signal handler for a specific signal.
 * 
 * @param sig The signal number for which you want to set up a handler.
 * @param func A pointer to the signal handling function that will be called
 *             when the signal is received.
 * @return Returns a pointer to the previously installed signal handling
 *         function.
 */
void (*signal(int sig, void (*func)(int)))(int);

/**
 * @brief Checks if the Ctrl+C signal has been pressed.
 * 
 * This function sets up a signal handler for the Ctrl+C signal (SIGINT) on its
 * first call, and checks if the signal has been received on subsequent calls.
 * 
 * @return true if the Ctrl+C signal has not been pressed, indicating the
 *         program should continue running or false if the Ctrl+C signal has
 *         been pressed, indicating the program should exit.
 */
bool	keep(void);


#endif // SIGNAL_HANDLER_HPP
