/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:28:11 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/03 18:37:43 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_segment_length(const char *s, char c)
{
	int		len;
	char	quote_char;

	len = 0;
	quote_char = '\0';
	while (s[len] && (s[len] != c || quote_char != '\0'))
	{
		if (is_quote(s[len]))
		{
			if (quote_char == '\0')
				quote_char = s[len];
			else if (s[len] == quote_char)
				quote_char = '\0';
		}
		len++;
	}
	return (len);
}

static char	*copy_segment(const char *s, int len)
{
	char	*segment;
	int		i;

	segment = ft_calloc(sizeof(char), len + 1);
	if (!segment)
		return (NULL);
	i = 0;
	while (i < len)
	{
		segment[i] = s[i];
		i++;
	}
	segment[i] = '\0';
	return (segment);
}

static int	process_segment(const char *s, char c, t_split_state *state)
{
	int	len;

	while (is_space(s[state->i]))
		state->i++;
	if (s[state->i] == '\0')
		return (0);
	len = get_segment_length(&s[state->i], c);
	state->split[state->j] = copy_segment(&s[state->i], len);
	if (!state->split[state->j])
		return (-1);
	state->i += len;
	state->j += 1;
	if (s[state->i] == c)
		state->i++;
	return (1);
}

char	**ft_split2(const char *s, char c)
{
	t_split_state	state;
	int				status;

	state.i = 0;
	state.j = 0;
	state.split = ft_calloc(sizeof(char *), strlen(s) + 1);
	if (!state.split)
		return (NULL);
	while (s[state.i])
	{
		status = process_segment(s, c, &state);
		if (status == -1)
		{
			free_split(state.split);
			return (NULL);
		}
		else if (status == 0)
			break ;
	}
	state.split[state.j] = NULL;
	remove_quotes(state.split);
	return (state.split);
}
