/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:36:49 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/09/09 14:36:49 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <messages.hpp>

void ft::print_random_start_message(void)
{
	std::vector<std::string> messages;

	messages.push_back("Hello o/");
	messages.push_back("Hi :3");
	messages.push_back("My name is not Frank.");

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int randomIndex = std::rand() % messages.size();

	std::cout << FT_WEBSERV << messages[randomIndex] << std::endl;
	std::cout << std::endl;
}

void ft::print_random_exit_message(void)
{
	std::vector<std::string> messages;

	messages.push_back("Bye, bye, until next time");

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int randomIndex = std::rand() % messages.size();

	std::cout << FT_WEBSERV << messages[randomIndex] << std::endl;
}

void ft::print_random_exit_error_message(void)
{
	std::vector<std::string> messages;

	messages.push_back("I can't operate in an unsafe environment.");
	messages.push_back("This is not my fault.");
	messages.push_back("Despite all my efforts, I encountered a setback.");
	messages.push_back("Please give me another shot.");
	messages.push_back("My journey must continue...");
	messages.push_back("WHAT?!");
	messages.push_back("Okay, nothing to worry about. Let's try again.");
	messages.push_back("...");

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int randomIndex = std::rand() % messages.size();

	std::cout << FT_WEBSERV << messages[randomIndex] << std::endl;
}
