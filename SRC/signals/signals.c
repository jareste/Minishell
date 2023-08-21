/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:35:28 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/21 02:31:11 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

// Función para manejar la señal SIGINT (Control+C)
void sigint_handler(int signum) {
    printf("Señal SIGINT (Control+C) recibida.\n");
}

// Función para manejar la señal SIGQUIT (Control+\)
void sigquit_handler(int signum) {
    printf("Señal SIGQUIT (Control+\\) recibida.\n");
}

// Función para manejar la señal SIGTSTP (Control+Z)
void sigtstp_handler(int signum) {
    printf("Señal SIGTSTP (Control+Z) recibida.\n");
}
