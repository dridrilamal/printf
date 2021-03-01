/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:25:43 by amilis            #+#    #+#             */
/*   Updated: 2021/02/23 13:25:44 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_conversions(char type, va_list args)
{
	int		len;
	
	if (type == 'c')
		len = ft_putchar(va_arg(args, int));
	if (type == 's')
		len = ft_putstr(va_arg(args, char*));
	if (type == 'p')
		len = print_pointer(va_arg(args, void*));
	if (type == 'd' || type == 'i')
		len = ft_putnbr(va_arg(args, int), 1);
	if (type == 'u')
		len = ft_putnbr(va_arg(args, unsigned int), 1);
	if (type == 'x')
		len = dec_to_hex(va_arg(args, unsigned int), 1, 1);
	if (type == 'X')
		len = dec_to_hex(va_arg(args, unsigned int), 0, 1);
	return (len);
}

int	flags(const char *str, va_list args)
{
	int		i;
	int 	len;

	i = 0;
	len = 0;
	if (str[i] >= '1' && str[i] <= '9')
		len = flag_width(str, args);
	else if (str[i] == '-')
		len = flag_minus(str + 1, args, get_width(str + 1, args, 0));
	else if (str[i] == '0')
		len = flag_zero(str + 1, args);
	else if (str[i] == '.')
		len = flag_point(str + 1, args, 0, 0);
	else if (str[i] == '*')
		len = flag_width(str, args);
	return (len);
}

int	ft_printf_start(const char *str, va_list args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] != '%' && str[i])
			len += ft_putchar(str[i++]);
		if (str[i++] == 0)
			return (len);
		if (is_type(str[i]))
			len += print_conversions(str[i++], args);
		else if (str[i] == '-' || is_number(str[i])
					|| str[i] == '.' || str[i] == '*')
		{
			len += flags(str + i, args);
			while (!is_type(str[i]))
				i++;
			i++;
		}
		else
			len += ft_putchar(str[i++]);
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	int		len;

	va_start(args, str);
	len = ft_printf_start(str, args);
	va_end(args);
	return (len);
}

int	main()
{
	int	i = -5462;
	unsigned int	u = UINT_MAX;
	char	*s = "ceci est un test";
	char 	c = 49;
	int		ft_len;
	int		sd_len;

	//" [%-*.*d] [%*.*d] ", 4, 5, 10, 10, 21, -10
	ft_len = ft_printf("[%1.0d]\n", 0);
	sd_len = printf("[%1.0d]\n", 0);
	printf("ft : %d, std : %d\n", ft_len, sd_len);
	return (0);
}
