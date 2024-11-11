/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:45:39 by psapio            #+#    #+#             */
/*   Updated: 2024/10/28 14:34:31 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_isalnum(int c)
{
	return (((c >= 'a') && (c <= 'z'))
		|| ((c >= 'A') && (c <= 'Z'))
		|| ((c >= '0') && (c <= '9')));
}
/*
int	main(void)
{
	char	value;

	value = 'F';
	printf("%d\n", ft_isalnum(value));
}
devuelve 1 si es el caaracter o digito
*/
