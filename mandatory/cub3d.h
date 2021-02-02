/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:48:44 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 20:13:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <libft.h>
# include "typedef.h"
# define MAX_RESOURCE 128
# define MLX_LOOP_INTERVAL 0.0001
# define UNIT_SCREEN_EXTENT 1764000
# define TARGET_FRAMERATE 60
# define FIELD_OF_VIEW 66.85
# define PLAYER_MOVE_SPEED 0.1
# define PLAYER_LOOK_SPEED 0.0785398163397448309615660845819875721
# define R 1024
# define R_2 512

/*
** ============================================================================
**   Enums
** ============================================================================
*/

enum					e_error
{
	Error_System = -1,
	Error_Success,
	Error_Begin = 255,
	Error_ArgumentLacked,
	Error_InvalidFileExtension,
	Error_InvalidIdentifier,
	Error_UnexpectedIdentifier,
	Error_InvalidMapInfo,
	Error_MLX_InitFailed,
	Error_MLX_CreateWindowFailed,
	Error_NewImage,
	Error_LoadImage,
	Error_GetPtrFailed,
	Error_StrTrimFailed,
	Error_StrSplitFailed,
	Error_UnparsableColor,
	Error_InvalidColor,
	Error_UnparsableResolution,
	Error_InvalidScreenSize,
	Error_UnknownFieldCharacter,
	Error_DuplicatedPlayerStart,
	Error_NoPlayerStart,
	Error_NotSurroundedByWall,
	Error_InvalidArgument,
	Error_DuplicatedMapInfo,
	Error_End
};

enum					e_hookevent
{
	HookEvent_KeyDown = 2,
	HookEvent_KeyUp = 3,
	HookEvent_MouseBtnDown = 4,
	HookEvent_MouseBtnUp = 5,
	HookEvent_MouseMove = 6,
	HookEvent_CloseWindow = 17
};

enum					e_key
{
	Key_A = 0,
	Key_S = 1,
	Key_D = 2,
	Key_Q = 12,
	Key_W = 13,
	Key_Space = 49,
	Key_ESC = 53,
	Key_LeftArrow = 123,
	Key_RightArrow = 124,
	Key_DownArrow = 125,
	Key_UpArrow = 126,
	Key_LCtrl = 256,
	Key_LShift = 257,
	Key_LCmd = 259,
	Key_Num
};

enum					e_mousebutton
{
	MouseBtn_Left = 1,
	MouseBtn_Middle = 2,
	MouseBtn_Right = 3,
	MouseBtn_Num
};

/*
**  https://www.rapidtables.com/web/color/RGB_Color.html
*/

enum					e_color
{
	Color_Black = 0x000000,
	Color_White = 0xFFFFFF,
	Color_Red = 0xFF0000,
	Color_Lime = 0x00FF00,
	Color_Blue = 0x0000FF,
	Color_Yellow = 0xFFFF00,
	Color_Cyan = 0x00FFFF,
	Color_Magenta = 0xFF00FF,
	Color_Silver = 0xC0C0C0,
	Color_Gray = 0x808080,
	Color_Maroon = 0x800000,
	Color_Olive = 0x808000,
	Color_Green = 0x008000,
	Color_Purple = 0x800080,
	Color_Teal = 0x008080,
	Color_Navy = 0x000080,
	Color_Tomato = 0xFF6347,
	Color_Orange = 0xFFA500,
	Color_Turquoise = 0x40E0D0,
	Color_HotPink = 0xFF69B4,
	Color_LightPink = 0xFFB6C1,
	Color_WhiteSmoke = 0xF5F5F5
};

enum					e_entity
{
	Entity_None,
	Entity_Player,
	Entity_Medikit
};

enum					e_direction
{
	Direction_Left,
	Direction_Right,
	Direction_Forward,
	Direction_Backward
};

enum					e_drawmode
{
	Draw_Ceiling,
	Draw_Wall,
	Draw_Floor
};

enum					e_id
{
	Id_Null,
	Id_TextureN,
	Id_TextureS,
	Id_TextureE,
	Id_TextureW,
	Id_Sprite
};

/*
** ============================================================================
**   Structures / Unions
** ============================================================================
*/

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_vector2
{
	double		x;
	double		y;
}				t_vector2;

typedef struct	s_rect
{
	double		left;
	double		top;
	double		width;
	double		height;
}				t_rect;

typedef struct	s_raycast
{
	t_vector2	collided;
	int			hit_axis;
	int			orient;
	t_point		mappos;
}				t_raycast;

typedef struct	s_size
{
	int			width;
	int			height;
}				t_size;

typedef struct	s_image
{
	void		*img_ptr;
	t_size		size;
	char		*data_addr;
	int			color_depth;
	size_t		bytes_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_spriteview
{
	t_vector2	coord;
	t_size		size;
	t_point		start;
	t_point		end;
	t_point		rstart;
	t_point		rend;
	int			yoffset;
}				t_spriteview;

typedef struct	s_valmap
{
	t_point		i;
	t_point		max;
	t_point		d_inner;
	t_point		d_outer;
	t_point		in;
	t_point		ij;
	int			mark;
}				t_valmap;

typedef struct	s_fpair
{
	double		f;
	void		*p;
}				t_fpair;

typedef struct	s_resources
{
	t_image		*imgs[MAX_RESOURCE];
}				t_resources;

typedef struct	s_input
{
	t_bool		key[Key_Num];
	t_bool		mousebtn[MouseBtn_Num];
	t_point		mouse;
}				t_input;

typedef struct	s_tick
{
	size_t		tick;
	size_t		tick_rate;
}				t_tick;

typedef struct	s_entity
{
	int			type;
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	plane;
	t_vector2	size;
	t_vector2	scale;
	double		yoffset;
	double		move_speed;
	double		look_speed;
}				t_entity;

typedef struct	s_map
{
	int			*field;
	t_size		size;
	char		*tex[MAX_RESOURCE];
	int			color_ceil;
	int			color_floor;
	int			startdir;
	t_point		startpos;
	int			loadmask;
	int			fullloadmask;
	t_list		*ent;
}				t_map;

typedef struct	s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			error;
	char		errordesc[1024];
	double		*z;
	t_cchar		*errormsg[Error_End];
	t_image		*screen;
	t_input		input;
	t_entity	player;
	t_map		map;
	t_resources	resource;
	t_tick		tick;
	t_size		screensize;
}				t_game;

/*
** ============================================================================
**   Functions -- [[ base/ ]]
** ============================================================================
*/

/*
**  ** Errors **
*/

void			error_init(t_game *g);
t_bool			error_raise(t_game *g, int err, t_cchar *desc);
t_bool			error_is_raised(t_game *g);
t_cchar			*error_get_msg(t_game *g, int error);

/*
**  ** App (MainLoop) **
*/

int				app_exit(t_game *g);
void			app_init_variables(t_game *g);
t_bool			app_on_loop(t_game *g);

/*
**  ** Window **
*/

t_bool			device_mlx_init(t_game *g);
t_bool			device_window_init(t_game *g, t_bool has_window);

/*
**  ** Image **
*/

t_image			*image_new(t_game *g, t_size size);
t_image			*image_load(t_game *g, t_cchar *filename);
void			image_unload(t_game *g, t_image *i);

/*
**  ** Resources **
*/

t_bool			resources_load(t_game *g);
void			resources_unload(t_game *g);
int				resources_get_pixel(t_game *g, int id, t_point texfrac);

/*
**  ** Tick **
*/

void			tick_init(t_game *g);
t_bool			tick_update(t_game *g);

/*
** ============================================================================
**   Functions -- [[ map/ ]]
** ============================================================================
*/

/*
**  ** Line Element Reader
*/

int				elem_read_str(t_game *g, char *line, t_cchar *id, char **dat);
int				elem_read_color(t_game *g, char *line, t_cchar *id, int *data);
int				elem_read_size(t_game *g, char *line, t_cchar *id, t_size *sz);

/*
**  ** Map **
*/

t_bool			map_load_entity(t_game *g);
t_bool			map_load_info(t_game *g, int fd, t_bool real_game);
t_bool			map_load_field(t_game *g, int fd);
t_bool			map_validate(t_game *g, t_map *m);
t_bool			map_check_rev(t_game *g, t_valmap vm, int m(t_game*, t_point));
int				map_get(t_map *m, int x, int y);
void			map_set(t_map *m, int x, int y, int c);
t_bool			map_load(t_game *g, t_cchar *file, t_bool real_game);
void			map_unload(t_game *g);
t_bool			map_is_wall(t_map *m, int x, int y);
int				map_get_entity_type(t_map *m, int x, int y);
t_vector2		map_alter_movevec(t_map *m, t_entity *e, t_vector2 pos);
int				map_get_wall_texid(t_game *g, int x, int y, int orient);

/*
**  ** Block **
*/

t_bool			block_is_wall(int c);
t_bool			block_is_void(int c);
t_bool			block_is_walkable(int c);
t_bool			block_is_item(int c);

/*
** ============================================================================
**   Functions -- [[ input/ ]]
** ============================================================================
*/

/*
**  ** Input [Keyboard/Mouse] **
*/

t_bool			input_on_keyup(int keycode, t_game *g);
t_bool			input_on_keydown(int keycode, t_game *g);
t_bool			input_on_mousebtnup(int btn, int x, int y, t_game *g);
t_bool			input_on_mousebtndown(int btn, int x, int y, t_game *g);
t_bool			input_on_mousemove(int x, int y, t_game *g);

/*
** ============================================================================
**   Functions -- [[ type/ ]]
** ============================================================================
*/

/*
**  ** Point **
*/

t_point			point_from_vector(t_vector2 vec);
t_vector2		point_to_vector(t_point pt);
t_point			point_new(int x, int y);

/*
**  ** Size **
*/

t_size			size_new(int w, int h);

/*
**  ** Vector **
*/

t_vector2		vec_new(double x, double y);
t_vector2		vec_add(t_vector2 vec, t_vector2 d);
t_vector2		vec_mult(t_vector2 vec, t_vector2 d);
t_vector2		vec_mult_scalar(t_vector2 vec, double d);
t_vector2		vec_sub(t_vector2 vec, t_vector2 d);
t_vector2		vec_rot(t_vector2 o, double theta);
t_vector2		vec_cam(t_vector2 rl, t_vector2 pl, t_vector2 d);

/*
**  ** Rect **
*/

t_rect			rect_new(double l, double t, double w, double h);
t_rect			rect_from_size(t_vector2 pos, t_vector2 sz);

/*
** ============================================================================
**   Functions -- [[ entity/ ]]
** ============================================================================
*/

/*
**  ** Entity **
*/

void			entity_init(t_game *g, t_entity *e, t_point pt, int c);
void			entity_rotate(t_entity *e, int dir);
void			entity_move(t_map *m, t_entity *e, int dir);
t_vector2		entity_get_size(int type);
int				entity_get_texid(t_entity *e);
t_vector2		entity_get_scale(int type);
double			entity_get_yoffset(int type);

/*
**  ** Player **
*/

void			player_init(t_game *g);
void			player_update(t_game *g);

/*
** ============================================================================
**   Functions -- [[ util/ ]]
** ============================================================================
*/

/*
**  ** Utils
*/

t_bool			util_is_digits(char *str);
t_bool			util_is_empty_line(t_cchar *s);
void			util_unify_spaces(char **ps);
int				util_sign(double nb);
int				util_chrcnt(const char *s, int c);
void			util_qsort(t_fpair **tab, int size);
t_bool			util_file_exists(t_cchar *filename);
t_bool			util_file_extension(t_cchar *filename, t_cchar *ext);
int				util_atoi(const char *str);

/*
**  ** Geometry (Raycasting) **
*/

t_raycast		geometry_raycast(t_game *g, t_vector2 org, t_vector2 ray);
double			geometry_correct(t_raycast *r, t_vector2 rd);
double			geometry_get_orthodist(t_game *g, t_raycast *r, t_vector2 rd);

/*
** ============================================================================
**   Functions -- [[ graphic/ ]]
** ============================================================================
*/

/*
**  ** Draw **
*/

void			draw_pixel(t_game *g, int x, int y, int color);

/*
**  ** Project (3D) **
*/

t_bool			project_3d(t_game *g);
void			project_wall(t_game *g, int x, t_raycast *r, t_vector2 rd);
t_bool			project_sprite(t_game *g);

/*
**  ** Screen **
*/

t_bool			screen_init(t_game *g);
void			screen_uninit(t_game *g);
t_bool			screen_draw(t_game *g);

/*
** ============================================================================
**   Functions -- [[ output/ ]]
** ============================================================================
*/

/*
**  ** BMP **
*/

t_bool			bmp_save(t_game *g, t_image *img, t_cchar *filename);

#endif
