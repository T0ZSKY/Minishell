/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:42:31 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/29 00:51:11 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ft_ascii()
{
	printf("\033[38;5;213m");
	printf(" __  __ _       _     _          _ _                             \n");
	printf("|  \\/  (_)_ __ (_)___| |__   ___| | |                            \n");
	printf("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |							\n");
	printf("| |  | | | | | | \\__ \\ | | |  __/ | |                            \n");
	printf("|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|							\n");
	printf("| |__  _   _  | |_ ___  _ __ ___ | (_)_ __ ___   ___  _ __       \n");
	printf("| '_ \\| | | | | __/ _ \\| '_ ` _ \\| | | '_ ` _ \\ / _ \\| '_ \\      \n");
	printf("| |_) | |_| | | || (_) | | | | | | | | | | | | | (_) | | | |     \n");
	printf("|_.__/ \\__, |  \\__\\___/|_| |_| |_|_|_|_| |_| |_|\\___/|_| |_|     \n");
	printf("  __ _ |___/  __| | | |_ __ _  ___  _ __ ___   __ _| | |__   ___ \n");
	printf(" / _` | '_ \\ / _` | | __/ _` |/ _ \\| '_ ` _ \\ / _` | | '_ \\ / _ \n");
	printf("| (_| | | | | (_| | | || (_| | (_) | | | | | | (_| | | |_) |  __/\n");
	printf(" \\__,_|_| |_|\\__,_|  \\__\\__,_|\\___/|_| |_| |_|\\__,_|_|_.__/ \\___|\n");
	printf("\033[0m");
}
