/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:30:14 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 00:52:40 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   COLORS   */

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define STD "\033[0m"
#define PURPLE "\033[0;35m"
#define BLUE "\033[1;36m"
#define ORANG "\033[1;33m"
#define WHITE "\033[1;37m"

/*   AUTOMATA DEFINES   */

#define ERROR__STATE	5
#define ACCEPT_STATES	2
#define PIPE_STATE		4

/*   COMMAND MATRIX DEFINES   */

#define ARGS	0
#define ENV		1

/*   HEREDOC BOOL   */

#define DONT_EXPAND '0'
#define EXPAND '1'

/*   ERRORS   */

#define OK 0
#define EXIT_STATUS_ERROR 1
#define IS_DIR 126
#define NO_PERMISSION 126
#define COMMAND_NOT_FOUND 127
#define INVALID_EXPORT_IDENTIFIER 3
#define EXIT_NON_DIGIT 2
#define OPEN_ERROR -1
#define CD_ERROR 1
#define CHDIR_ERROR -1

/*   OPEN MODE   */

//(O_WRONLY | O_CREAT | O_TRUNC)
#define O_REDIRECT_RIGHT 577
//(O_WRONLY | O_CREAT | O_APPEND)
#define O_REDIRECT_APPEND 1089
// (O_RDONLY)
#define O_REDIRECT_LEFT 0
// (O_WRONLY | O_CREAT | O_TRUNC)
#define O_HEREDOC 1089
// (O_RDONLY)
#define O_READ_HEREDOC 0

#define STD_PERMISSIONS 0644
#define NULL_FD -2

#define SPACES " \f\n\r\t\v"
#define QUOTES "\"\'"
#define SYMBOLS "|<>"

#define OUT_FILE 1
#define IN_FILE 0

#define ALL_CHILDREN_DEAD -1
// EXEC
#define CHILD 0

//EXIT_STATUS
#define SIGINT_SIGNAL 130