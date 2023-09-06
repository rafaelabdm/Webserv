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
# define MESSAGES_HPP

# include <colors.hpp>

# define FT_OK		"[" GREEN	"  OK   "	RESET_COLOR "] "
# define FT_FAIL	"[" RED		" FAIL  "	RESET_COLOR "] "
# define FT_WARNING	"[" YELLOW	"WARNING"	RESET_COLOR "] "
# define FT_SETUP	"[" BLUE	" SETUP "	RESET_COLOR "] "
# define FT_CLOSE	"[" BLUE	" CLOSE "	RESET_COLOR "] "

# define FT_HELP_HINT	"Try './webserv --help' for more information."
# define FT_MANY_ARGS	FT_WARNING "Too many arguments.\n" FT_HELP_HINT

#endif // MESSAGES_HPP
