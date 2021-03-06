

#include "../../includes/ft_cub3d.h"

void		ft_check_0_out(t_cub3d *game, int i, int j)
{
	while (game->map[++i])
	{
		while (game->map[i][++j] && i != game->maplinecount)
		{
			if (game->map[i][j] == '0' && (ft_strlen(game->map[i - 1]) - 1 < j
			|| ft_strlen(game->map[i + 1]) - 1 < j))
			{
				ft_putstr_fd("Error\nA 0 is not well placed", 1);
				ft_exit(game, 0);
			}
			if (game->map[i][j] == '0' && game->map[i - 1][j] != '1'
			&& game->map[i + 1][j] != '1' && game->map[i - 1][j] != '0'
			&& game->map[i + 1][j] != '0' && game->map[i - 1][j] != 'N'
			&& game->map[i - 1][j] != 'E' && game->map[i - 1][j] != 'W'
			&& game->map[i - 1][j] != 'S' && game->map[i - 1][j] != '2'
			&& game->map[i + 1][j] != 'N' && game->map[i + 1][j] != 'E'
			&& game->map[i + 1][j] != 'W' && game->map[i + 1][j] != 'S'
			&& game->map[i + 1][j] != '2')
			{
				ft_putstr_fd("Error\nA 0 is not well placed", 1);
				ft_exit(game, 0);
			}
		}
		j = -1;
	}
}

int			ft_check_is_map_line(t_cub3d *game, char *line)
{
	if (game->arg_count == 8 && game->skip == 1)
	{
		if (ft_isemptyline(line) == 0 && game->maplinecount == 0)
			return (0);
		return (1);
	}
	return (0);
}

int			ft_isemptyline(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (i == ft_strlen(line))
		return (0);
	return (1);
}

void		ft_count_map_args(t_cub3d *game, char *line, int i)
{
	int f;
	int c;

	f = 0;
	c = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'R' || (line[i] == 'N' && line[i + 1] == 'O') ||
		(line[i] == 'S' && line[i + 1] == 'O') || (line[i] == 'W' &&
		line[i + 1] == 'E') || (line[i] == 'E' && line[i + 1] == 'A')
		|| (line[i] == 'S' && line[i + 1] != '1' && line[i + 1] != '0')
		|| line[i] == 'F' || line[i] == 'C')
		{
			game->arg_count++;
			c++;
		}
		else if ((ft_isalpha(line[i]) || ft_isdigit(line[i])) && c == 0)
			f++;
		i++;
	}
	if (f != 0 && game->arg_count != 8)
		check_map_qwerty_error(game);
	if (game->arg_count > 8)
		check_map_qwerty_error(game);
	ft_check_map_arg(game, line, 0);
}

void		ft_check_map_arg(t_cub3d *game, char *line, int i)
{
	while (line[i] != '\0')
	{
		if (line[i] == 'R')
			game->arg_r++;
		if (game->arg_r == 1)
			if ((((!ft_isdigit(line[i]) && line[i] != 32 && line[i] != 'R')
				|| game->arg_r > 2)))
			{
				ft_putstr_fd("Error\nMultiple arg R or bad format.", 1);
				ft_exit(game, 0);
			}
		i++;
	}
	if (game->arg_r == 1)
	{
		game->arg_r++;
		ft_parser_r(game, line, 0);
	}
	ft_texture_path_no(game, line, 0);
	ft_colors(game, line, -1, 1);
	if (game->verif_f > 1 || game->verif_c > 1)
	{
		ft_putstr_fd("Error\nToo many argument F or C\n", 1);
		ft_exit(game, 0);
	}
}
