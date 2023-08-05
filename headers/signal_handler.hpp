/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:23:50 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 20:23:50 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_HPP
# define SIGNAL_HANDLER_HPP

# include <colors.hpp>
# include <iostream>
# include <signal.h>

extern volatile bool g_shouldTerminate;

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

void	set_signal(void);

#endif // SIGNAL_HANDLER_HPP
