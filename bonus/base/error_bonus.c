/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 10:46:18 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 18:31:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <string.h>

static void	error_init2(t_game *g)
{
	g->errormsg[Error_InvalidBpp] = "This app must be run at 32bit color pc.";
	g->errormsg[Error_InvalidFileExtension] = "Invalid file extension.";
}

void		error_init(t_game *g)
{
	g->errormsg[Error_ArgumentLacked] = "Usage: ./cub3D <map file> [--save]";
	g->errormsg[Error_InvalidIdentifier] = "Invalid map component identifier.";
	g->errormsg[Error_UnexpectedIdentifier] = "Unexpected map identifier.";
	g->errormsg[Error_InvalidMapInfo] = "Invalid map component info.";
	g->errormsg[Error_MLX_InitFailed] = "Failed to initialize MiniLibX";
	g->errormsg[Error_MLX_CreateWindowFailed] = "Failed to create a window";
	g->errormsg[Error_NewImage] = "Failed to create a new image.";
	g->errormsg[Error_LoadImage] = "Failed to load image from file.";
	g->errormsg[Error_GetPtrFailed] = "Couldn't get ptr from image.";
	g->errormsg[Error_StrTrimFailed] = "An error was occured while ft_strtrim";
	g->errormsg[Error_StrSplitFailed] = "An error was occured while ft_split";
	g->errormsg[Error_UnparsableColor] = "Unparsable color.";
	g->errormsg[Error_InvalidColor] = "Color value must be in 0 ~ 255";
	g->errormsg[Error_UnparsableResolution] = "Unparsable resolution.";
	g->errormsg[Error_InvalidScreenSize] = "Invalid screen size value.";
	g->errormsg[Error_UnknownFieldCharacter] = "Unknown field character";
	g->errormsg[Error_DuplicatedPlayerStart] = "Duplicated player start.";
	g->errormsg[Error_NoPlayerStart] = "No player start position";
	g->errormsg[Error_NotSurroundedByWall] = "Map is not surrounded by a wall";
	g->errormsg[Error_InvalidArgument] = "Invalid Argument";
	g->errormsg[Error_DuplicatedMapInfo] = "Duplicated Map Info.";
	g->errormsg[Error_InvalidDoorPlace] = "Invalid Door Place";
	g->errormsg[Error_InvalidSecretPlace] = "Invalid Secret Place";
	g->errormsg[Error_NoTexIdSymbol] = "No Texture Id Symbol '%'";
	error_init2(g);
}

t_cchar		*error_get_msg(t_game *g, int error)
{
	t_cchar	*ret;

	ret = NULL;
	if (error)
	{
		if (error < Error_Begin)
			ret = strerror(error);
		else
		{
			if (error < Error_End)
				ret = g->errormsg[error];
			else
				ret = "Unknown Error";
		}
	}
	return (ret);
}

t_bool		error_raise(t_game *g, int err, t_cchar *desc)
{
	g->error = err;
	if (desc)
		ft_strlcpy(g->errordesc, desc, MSG_BUF_SIZE);
	if (err == Error_Success && !desc)
		g->errordesc[0] = '\0';
	return (FALSE);
}

t_bool		error_is_raised(t_game *g)
{
	return (g->error != Error_Success);
}
