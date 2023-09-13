/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:24:26 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 18:24:26 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_argc.hpp>
#include <help_option.hpp>
#include <iostream>
#include <messages.hpp>
#include <WebServer.hpp>
#include <CGI.hpp>
#include <close_fds.hpp>

int main(const int argc, const char **argv)
{
	// ===== CGI TEST START :eyes: =============================================
	try
	{
		std::string script_path = "public/cgi/HelloWorld.py";

		ft::CGI cgi(script_path);
		std::string result = cgi.executePythonScript();

		std::cout
			<< FT_HIGH_LIGHT_COLOR
			<< result
			<< RESET_COLOR
			<< std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;

		ft::print_random_exit_error_message();

		ft::close_fds();

		return (1);
	}

	ft::close_fds();

	return (0);

	// ===== CGI TEST END :eyes: ===============================================

	if (ft::help_option(argv))
		return (0);

	if (ft::check_argc(argc))
		return (1);

	ft::print_random_start_message();

	try
	{
		ft::WebServer ws(argv[1]);
		ws.start_servers();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;

		ft::print_random_exit_error_message();

		ft::close_fds();

		return (1);
	}

	ft::print_random_exit_message();

	ft::close_fds();

	return (0);
}
