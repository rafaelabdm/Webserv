/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 08:12:59 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/05 08:12:59 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ConfigFile.hpp>

ft::ConfigFile::ConfigFile(const std::string& config_file)
{
	std::cout
		<< FT_SETUP
		<< "Parsing "
		<< GREEN << config_file << RESET_COLOR
		<< " configuration file."
		<< std::endl;

	return;
}

ft::ConfigFile::~ConfigFile()
{
	std::cout << FT_CLOSE << "Closing configuration file." << std::endl;

	return;
}
