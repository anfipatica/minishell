/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:40:13 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 17:48:43 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define VERSION "🍍🚫🍕 shell, version 1.0 - release (x64-linux-gnu)\n\
Copyright (C) 2025 Free Software Foundation, Inc.\n\
License GPLv3+: GNU GPL version 3 or later\n\
<http://www.instagram.com/anfi_patica>\n\
<http://www.sapioart.com>\n\
\n\
This is free software; you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
\n\
I just wanted to take a moment to thank all of you for your invaluable\n\
help and support during this journey.\n\n\
	- David: apoyo moral,\n\
	- Kevin: vision final,\n\
	- Pepe: pepex,\n\
	- Jorge: automata,\n\
	- Andrii: inversor y supervisor de mentes maestras\n\
	- Vicente: clean code\n\
	- Raúl: un padre maestro\n\
	- los Franceses: Augustin y Guillaume\n\
\n\
Each of you has played a crucial role in shaping this project,\n\
and I am truly grateful for your guidance, expertise, and dedication.\n\
Your insights and passion have made this experience unforgettable,\n\
and I’ve learned so much from every one of you. Thank you for being\n\
part of this adventure and for sharing your knowledge with me.\n\
This project wouldn’t have been the same without you!\n\
\n\
\n\
\"You're all clear, kid! Now let's blow this thing and go home!\"\n\
No tengan miedo, nunca en la vida. A veces,\n\
la vida nos presenta desafíos enormes,\n\
pero siempre hay un momento en que tenemos que dar ese paso\n\
y hacer lo que parece imposible.\n\
¡Es hora de seguir adelante con valentía,\n\
romper barreras y conquistar nuestros miedos!\n\
"

void	version(void)
{
	printf("%s\n", VERSION);
}
