/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:18:00 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/05 07:18:00 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP

# include <colors.hpp>
# include <iostream>
# include <messages.hpp>

namespace ft
{
	class ConfigFile
	{
		public:
			ConfigFile(const std::string& file);
			~ConfigFile(void);

		private:
	};
}

# include <ConfigFile.ipp>

#endif //CONFIGFILE_HPP
