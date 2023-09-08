/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:25:00 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/09/07 14:25:00 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_argc.hpp>

bool ft::check_argc(const int argc)
{
	if (argc > 2)
		std::cout << FT_MANY_ARGS << std::endl;

	return (argc > 2);
}
