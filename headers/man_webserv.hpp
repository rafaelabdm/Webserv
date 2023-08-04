/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_webserv.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:58:57 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 19:58:57 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAN_WEBSERV_HPP
# define MAN_WEBSERV_HPP

# include <iostream>

const char * const HELP_MSG = "\
Usage: webserv <confFile>.conf \n\
 \n\
A project about basic HTTP server creation. \n\
 \n\
	-h, --help	display this help page and exit. \n\
\n\
More about this project can be found on \n\
https://github.com/rafaelabdm/Webserv/ \n\
\n\
";

bool	manual_option(const std::string& option);

#endif // MAN_WEBSERV_HPP
