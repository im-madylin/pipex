/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:42:00 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/26 15:45:24 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    while (i < 256)
    {
        // printf("%d: %s\n", i, strerror(i));
        errno = i;
        perror(NULL);
        i++;
    }
    return 0;
}
