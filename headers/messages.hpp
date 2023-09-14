/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:45:51 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 18:45:51 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <colors.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <messages.hpp>
#include <vector>

#define FT_WEBSERV "[" MAGENTA "WEBSERV" RESET_COLOR "] "
#define FT_OK "[" GREEN "  OK   " RESET_COLOR "] "
#define FT_ERROR "[" RED " ERROR " RESET_COLOR "] "
#define FT_WARNING "[" YELLOW "WARNING" RESET_COLOR "] "
#define FT_EVENT "[" CYAN " EVENT " RESET_COLOR "] "
#define FT_CGI "[" CYAN "  CGI  " RESET_COLOR "] "
#define FT_STATUS "[" RED "STATUS " RESET_COLOR "] "
#define FT_INFO "[" MAGENTA " INFO  " RESET_COLOR "] "
#define FT_SETUP "[" BLUE " SETUP " RESET_COLOR "] "
#define FT_CLOSE "[" BLUE " CLOSE " RESET_COLOR "] "

namespace ft
{
	/**
	 * @brief Prints a random message on Webserv startup.
	 *
	 */
	void print_random_start_message(void);

	/**
	 * @brief Prints a random message on Webserv exit.
	 *
	 */
	void print_random_exit_message(void);

	/**
	 * @brief Prints a random error message on Webserv exit.
	 *
	 */
	void print_random_exit_error_message(void);
}

#endif // MESSAGES_HPP
