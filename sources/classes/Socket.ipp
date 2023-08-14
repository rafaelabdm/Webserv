/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:35:44 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/14 09:49:35 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

ft::Socket::Socket(const std::string& host, const std::string& port) : _host(host), _port(port)
{
	std::cout
		<< FT_SETUP
		<< "Setting up "
		<< GREEN << this->_host << RESET_COLOR
		<< " socket on port "
		<< GREEN << this->_port << RESET_COLOR
		<< "."
		<< std::endl;
}

ft::Socket::~Socket()
{
	std::cout
		<< FT_CLOSE
		<< "Closing "
		<< GREEN << this->_host << RESET_COLOR
		<< " socket on port "
		<< GREEN << this->_port << RESET_COLOR
		<< "."
		<< std::endl;
}
