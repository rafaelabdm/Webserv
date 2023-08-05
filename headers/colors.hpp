/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:40:58 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 19:40:58 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

# define RESET_COLOR  "\033[0m"
# define INVERT_COLOR "\033[7m"
# define RED          "\033[0;31m"
# define GREEN        "\033[0;32m"
# define YELLOW       "\033[0;33m"
# define BLUE         "\033[0;34m"
# define MAGENTA      "\033[0;35m"
# define CYAN         "\033[0;36m"

# define MSG_OK			"[ " GREEN "OK" RESET_COLOR " ] "
# define MSG_WARNING	"[ " YELLOW "WARNING" RESET_COLOR " ] "
# define MSG_SETUP		"[ " BLUE "SETUP" RESET_COLOR " ] "

#endif // COLORS_HPP
