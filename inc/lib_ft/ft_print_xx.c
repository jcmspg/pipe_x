/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 03:08:57 by joamiran          #+#    #+#             */
/*   Updated: 2024/05/08 18:19:15 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_prefix(t_data *data, unsigned int arg, int upcase)
{
	char	*prefix;

	if (upcase)
		prefix = "0X";
	else
		prefix = "0x";
	if (data->format.hashtag && arg != 0)
		data->chars_printed += ft_write_str(prefix, 2);
}

static void	ft_print_hex(t_data *data, char *hex_str, int padding, int prpad)
{
	if (data->format.zero_padding && !data->format.minus_sign && \
		data->format.precision == -1)
	{
		print_padding(data, padding, '0');
		padding = 0;
	}
	print_padding(data, prpad, '0');
	write(1, hex_str, ft_strlen(hex_str));
	data->chars_printed += ft_strlen(hex_str);
	if (data->format.minus_sign)
		print_padding(data, padding, ' ');
}

void	print_padding_logic(t_data *data, int padding, int zero_padding)
{
	if (zero_padding)
		print_padding(data, padding, '0');
	else
		print_padding(data, padding, ' ');
}

void	ft_print_xx(t_data *data, unsigned int arg, int upcase)
{
	char	*hex_str;
	int		padding;
	int		prpad;

	hex_str = set_hex_str(data, arg);
	if (upcase)
		ft_strtoupper(hex_str);
	padding = data->format.width - ft_max(ft_strlen(hex_str), \
		data->format.precision);
	prpad = set_prpad(data, hex_str);
	if (data->format.minus_sign)
	{
		print_prefix(data, arg, upcase);
		ft_print_hex(data, hex_str, 0, prpad);
		print_padding(data, padding, ' ');
	}
	else
	{
		print_padding_logic(data, padding, data->format.zero_padding && \
			data->format.precision < 0);
		print_prefix(data, arg, upcase);
		ft_print_hex(data, hex_str, 0, prpad);
	}
	free(hex_str);
}

/* void	ft_print_xx(t_data *data, unsigned int arg, int upcase)
{
	char	*hex_str;
	int		padding;
	int		prpad;

	if (!arg && data->format.precision != 0)
		hex_str = ft_strdup("0");
	else if (!arg && data->format.precision == 0)
		hex_str = ft_strdup("");
	else
		hex_str = ft_itoa_base(arg, 16);
	if (upcase)
		ft_strtoupper(hex_str);
	padding = data->format.width - ft_max(ft_strlen(hex_str), \
		data->format.precision);
	prpad = data->format.precision - ft_strlen(hex_str);
	if (prpad < 0)
		prpad = 0;
	if (data->format.minus_sign)
	{
		print_prefix(data, arg, upcase);
		ft_print_hex(data, hex_str, 0, prpad);
		print_padding(data, padding, ' ');
	}
	else
	{
		if (data->format.zero_padding && data->format.precision < 0)
			print_padding(data, padding, '0');
		else
			print_padding(data, padding, ' ');
		print_prefix(data, arg, upcase);
		ft_print_hex(data, hex_str, 0, prpad);
	}
	free(hex_str);
} */
