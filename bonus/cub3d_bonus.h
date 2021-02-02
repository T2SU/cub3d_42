/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:48:44 by smun              #+#    #+#             */
/*   Updated: 2021/02/01 19:31:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include <unistd.h>
# include <libft.h>
# include "typedef_bonus.h"
# define MAX_RESOURCE 128
# define MLX_LOOP_INTERVAL 0.0001
# define UNIT_SCREEN_EXTENT 1764000
# define FIELD_OF_VIEW 66.85
# define PLAYER_MOVE_SPEED 0.1
# define PLAYER_LOOK_SPEED 0.0785398163397448309615660845819875721
# define ENEMY_MOVE_SPEED 0.2
# define ENEMY_LOOK_SPEED 0.785398163397448309615660845819875721
# define R 1024
# define RBITS 10
# define R_2 512
# define SKYBOX_RATIO 3
# define DOOR_SPEED 0.03
# define SECRETWALL_SPEED 0.015
# define MSG_BUF_SIZE 1024

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
	Error_InvalidDoorPlace,
	Error_InvalidSecretPlace,
	Error_NoTexIdSymbol,
	Error_InvalidBpp,
	Error_End
};

enum					e_colormap
{
	ColorMap_Blue,
	ColorMap_Green,
	ColorMap_Red,
	ColorMap_Alpha
};

enum					e_hookevent
{
	HookEvent_KeyDown = 2,
	HookEvent_KeyUp = 3,
	HookEvent_MouseBtnDown = 4,
	HookEvent_MouseBtnUp = 5,
	HookEvent_MouseMove = 6,
	HookEvent_Expose = 12,
	HookEvent_CloseWindow = 17
};

enum					e_key
{
	Key_A = 0,
	Key_S = 1,
	Key_D = 2,
	Key_Q = 12,
	Key_W = 13,
	Key_1 = 18,
	Key_2 = 19,
	Key_3 = 20,
	Key_4 = 21,
	Key_6 = 22,
	Key_5 = 23,
	Key_9 = 25,
	Key_7 = 26,
	Key_8 = 28,
	Key_0 = 29,
	Key_Space = 49,
	Key_ESC = 53,
	Key_F5 = 96,
	Key_F6 = 97,
	Key_F7 = 98,
	Key_F3 = 99,
	Key_F8 = 100,
	Key_F9 = 101,
	Key_F10 = 109,
	Key_F2 = 120,
	Key_F4 = 118,
	Key_F1 = 122,
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
	Color_WhiteSmoke = 0xF5F5F5,
	Color_LightGray = 0x161616,
	Color_LightGreen = 0x001600,
	Color_LightRed = 0x2A0000,
	Color_DeadRed = 0x300000
};

enum					e_entity
{
	Entity_None,
	Entity_Player,
	Entity_Medikit,
	Entity_Money,
	Entity_Sprite1,
	Entity_Sprite2,
	Entity_Sprite3,
	Entity_Sprite4,
	Entity_Bullet,
	Entity_Shell,
	Entity_Shotgun,
	Entity_Enemy1,
	Entity_Enemy2
};

enum					e_direction
{
	Direction_Left,
	Direction_Right,
	Direction_Forward,
	Direction_Backward
};

enum					e_lifestate
{
	LifeState_Stand,
	LifeState_Walk,
	LifeState_Attack,
	LifeState_Hit,
	LifeState_Die,
	LifeState_Num
};

enum					e_orient
{

	Orient_N,
	Orient_NW,
	Orient_W,
	Orient_SW,
	Orient_S,
	Orient_SE,
	Orient_E,
	Orient_NE,
	Orient_Num
};

enum					e_id
{
	Id_Null,
	Id_Wall1,
	Id_Wall2,
	Id_Wall3,
	Id_Wall4,
	Id_Wall5,
	Id_Wall6,
	Id_Wall7,
	Id_Wall8,
	Id_Wall9,
	Id_Floor,
	Id_Skybox,
	Id_Door1,
	Id_Door2,
	Id_Sprite1,
	Id_Sprite2,
	Id_Sprite3,
	Id_Sprite4,
	Id_Money,
	Id_Medikit,
	Id_HudScore,
	Id_Digit,
	Id_HudHp,
	Id_HudHPBar,
	Id_HudHPGauge,
	Id_Crosshair,
	Id_GameOver,
	Id_GameWin,
	Id_Enemy1Std,
	Id_Enemy1Mov,
	Id_Enemy1Atk,
	Id_Enemy1Hit,
	Id_Enemy1Die,
	Id_Enemy2Std,
	Id_Enemy2Mov,
	Id_Enemy2Atk,
	Id_Enemy2Hit,
	Id_Enemy2Die,
	Id_Weapon0,
	Id_Weapon1,
	Id_Weapon2,
	Id_Weapon1A,
	Id_Weapon2A,
	Id_Weapon2I
};

enum					e_ammo
{
	Ammo_None,
	Ammo_Bullet,
	Ammo_Shell,
	Ammo_Num
};

enum					e_weapon
{
	Weapon_Foot,
	Weapon_Pistol,
	Weapon_Shotgun,
	Weapon_Chaingun,
	Weapon_Num
};

enum					e_doorstate
{
	DoorState_Closed,
	DoorState_Opening,
	DoorState_Closing,
	DoorState_Open
};

enum					e_secretstate
{
	SecretState_Unrevealed,
	SecretState_Moving,
	SecretState_Revealed
};

enum					e_hud
{
	Hud_Score,
	Hud_Digit,
	Hud_Hp,
	Hud_Num,
	Hud_Ammo,
	Hud_Weapon,
	Hud_Crosshair,
	Hud_GameOver,
	Hud_Message,
	Hud_Lifebar,
	Hud_LifeGauge
};

enum					e_raycast
{
	Raycast_Default = 0,
	Raycast_Life = 1 << 0,
	Raycast_Player = 1 << 1
};

enum					e_gameover
{
	GameOver_None,
	GameOver_Dead,
	GameOver_Win
};

enum					e_cheat
{
	Cheat_None,
	Cheat_God = 1 << 0,
	Cheat_Ammo = 1 << 1,
	Cheat_Transcendence = 1 << 2,
	Cheat_OneShot = 1 << 3
};

enum					e_sound
{
	Sound_None,
	Sound_BGM1,
	Sound_BGM2,
	Sound_BGM3,
	Sound_DoorClose,
	Sound_DoorOpen,
	Sound_EnemyDie1,
	Sound_EnemyDie2,
	Sound_EnemyHit,
	Sound_EnemyHello1,
	Sound_EnemyHello2,
	Sound_NoWay,
	Sound_Pistol,
	Sound_PlayerDie,
	Sound_PlayerHit,
	Sound_Shotgun,
	Sound_WeaponPickUp,
	Sound_ItemPickUp,
	Sound_SecretWall,
	Sound_SecretWallEnd,
	Sound_Foot,
	Sound_Switch,
	Sound_Num
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
	int			vieworient;
	t_point		texfrac;
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

typedef struct	s_texset
{
	t_image		**imgs;
	int			imgcnt;
	int			i;
}				t_texset;

typedef struct	s_resources
{
	t_texset	*texs[MAX_RESOURCE];
	char		*sounds[Sound_Num];
}				t_resources;

typedef struct	s_input
{
	t_bool		key[Key_Num];
	t_bool		mousebtn[MouseBtn_Num];
	t_point		mouse;
	t_vector2	mouselast;
	t_vector2	mousemoved;
}				t_input;

typedef struct	s_tick
{
	size_t		tick;
	size_t		tick_rate;
	size_t		loopcnt;
}				t_tick;

typedef struct	s_weapon
{
	double		spread;
	double		range;
	int			ammo;
	int			damage;
	int			bullet;
	size_t		speed;
	size_t		delay;
	int			gunsound;
}				t_weapon;

typedef struct	s_life
{
	int			state;
	size_t		statedur;
	size_t		frametick;
	int			i;
	int			texid[LifeState_Num];
	size_t		cooldown[LifeState_Num];
	t_weapon	*weapon;
	double		damagefactor;
	size_t		attackdur;
	size_t		delaydur;
	int			orientnum;
	t_bool		continousatk;
}				t_life;

typedef struct	s_entity
{
	int			type;
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	plane;
	t_vector2	size;
	t_vector2	scale;
	int			hp;
	int			maxhp;
	double		yoffset;
	double		move_speed;
	double		look_speed;
	t_life		life;
}				t_entity;

typedef struct	s_raycast
{
	t_vector2	origin;
	t_vector2	collided;
	t_point		mappos;
	t_vector2	total;
	int			hit_axis;
	int			orient;
	double		factor;
	t_entity	*hitlife;
}				t_raycast;

typedef struct	s_door
{
	double		factor;
	int			state;
	t_point		pos;
	int			axis;
	size_t		ignore_interact;
	size_t		closewait;
	int			doortex;
}				t_door;

typedef struct	s_secret
{
	double		factor;
	size_t		soundtick;
	int			state;
	t_point		pos;
	t_point		nextpos;
	int			look;
}				t_secret;

typedef struct	s_map
{
	int			*field;
	t_size		size;
	char		*tex[MAX_RESOURCE];
	int			color_ceil;
	int			color_floor;
	int			startdir;
	t_point		startpos;
	t_uint64	loadmask;
	t_uint64	fullloadmask;
	t_list		*ent;
	int			doorcnt;
	t_door		**door;
	int			secretcnt;
	t_secret	**secret;
}				t_map;

typedef struct	s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			error;
	char		errordesc[MSG_BUF_SIZE];
	double		*z;
	int			score;
	int			bullets[Ammo_Num];
	t_weapon	weapons[Weapon_Num];
	int			inventory;
	t_bool		hidemouse;
	t_cchar		*errormsg[Error_End];
	t_image		*screen;
	int			colormap[3];
	size_t		colormapdur;
	t_input		input;
	t_entity	player;
	t_map		map;
	t_resources	resource;
	t_tick		tick;
	t_size		screensize;
	int			gameover;
	size_t		gameovertick;
	char		*mapfile;
	int			cheat;
	size_t		cheatdelay;
	char		msg[MSG_BUF_SIZE];
	size_t		msgdur;
	t_entity	*attention;
	size_t		attentiondur;
}				t_game;

typedef struct	s_entry {
	void		*data;
	void		*prev;
	void		*next;
}				t_entry;

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
**  ** Device **
*/

t_bool			device_mlx_init(t_game *g);
t_bool			device_window_init(t_game *g, t_bool has_window);

/*
**  ** Window **
*/

int				window_on_expose(t_game *g);
void			window_on_esc(t_game *g);
int				window_on_close(t_game *g);
int				window_mouse(t_game *g);

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
int				resources_pixel_raw(t_texset *tx, int i, t_point *f);
int				resources_get_pixel(t_game *g, int id, t_point *texfrac);

/*
**  ** Tick **
*/

void			tick_init(t_game *g);
t_bool			tick_update(t_game *g);

/*
**  ** Texture Set **
*/

t_texset		*texset_empty(t_game *g);
t_texset		*texset_new(t_game *g, t_cchar *path);
void			texset_delete(t_game *g, t_texset *tex);
t_image			*texset_get_img(t_game *g, int id);
void			texset_resetframe(t_game *g, int id);
void			texset_nextframe(t_game *g, int id, t_bool loop);
void			texset_update(t_game *g);

/*
**  ** Cheat **
*/

void			cheat_update(t_game *g);

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
int				map_get_attr(t_map *m, int x, int y);
void			map_set_attr(t_map *m, int x, int y, int attr);
t_bool			map_load(t_game *g, t_cchar *file, t_bool real_game);
void			map_unload(t_game *g);
t_bool			map_is(t_map *m, int x, int y, t_bool (p(int)));
int				map_get_entity_type(t_map *m, int x, int y);
t_vector2		map_alter_movevec(t_map *m, t_entity *e, t_vector2 pos);
int				map_get_wall_texid(t_game *g, int x, int y);
t_bool			map_is_walkable(t_map *m, int x, int y);
t_bool			map_load_facility(t_game *g, int di, int si);

/*
**  ** Block **
*/

t_bool			block_is_wall(int c);
t_bool			block_is_void(int c);
t_bool			block_is_item(int c);
t_bool			block_is_door(int c);
int				block_get_secret_look(int c);
t_bool			block_is_sprite(int c);
t_bool			block_is_life(int c);
t_bool			block_is_exit(int c);

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
t_bool			input_on_mousedelta(double dx, double dy, t_game *g);

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
t_point			point_next_by_dir(t_vector2 pos, t_vector2 dir);

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
t_vector2		vec_norm(t_vector2 vec);
t_vector2		vec_rotraw(t_vector2 *o, t_vector2 *uv);
t_vector2		vec_rot(t_vector2 o, double theta);
t_vector2		vec_cam(t_vector2 rl, t_vector2 pl, t_vector2 d);
t_bool			vec_set(t_vector2 *v, int axis, double val);
double			vec_get(t_vector2 *v, int axis);

/*
**  ** Rect **
*/

t_rect			rect_new(double l, double t, double w, double h);
t_rect			rect_from_size(t_vector2 pos, t_vector2 sz);
t_bool			rect_contains(t_rect rc, t_vector2 pos);
t_bool			rect_overlaps(t_rect rc, t_rect rc2);

/*
** ============================================================================
**   Functions -- [[ entity/ ]]
** ============================================================================
*/

/*
**  ** Entity **
*/

void			entity_init(t_game *g, t_entity *e, t_point pt, int c);
void			entity_rotate(t_entity *e, int dir, double theta);
void			entity_move(t_map *m, t_entity *e, int dir);
int				entity_get_view_orient(t_entity *e, t_entity *p);
void			entity_update(t_game *g);
t_vector2		entity_get_size(int type);
int				entity_get_texid(t_entity *e);
t_vector2		entity_get_scale(int type);
double			entity_get_yoffset(int type);
t_bool			entity_is_pickable(int type);
t_bool			entity_is_life(int type);
t_bool			entity_life_is_oriented_state(int state);
void			entity_life_init_appearance(int type, t_life *life);
void			entity_life_init_soldier(t_game *g, int type, t_entity *e);
int				entity_life_pixel(t_game *g, t_entity *e, int i, t_point *fr);
void			entity_life_init(t_game *g, t_entity *e, t_point pt);
void			entity_life_set_state(t_game *g, t_entity *e, int s, size_t t);
void			entity_life_update(t_game *g, t_entity *e);
int				entity_life_curframe(t_game *g, t_entity *e, t_spriteview *sv);
void			entity_life_ai_update(t_game *g, t_entity *e);
void			entity_life_ai_feel_bullet(t_game *g, t_entity *p);
void			entity_life_ai_attack(t_game *g, t_entity *e);

/*
**  ** Player **
*/

void			player_init(t_game *g);
void			player_update(t_game *g);
void			player_try_pickup_item(t_game *g, t_entity *p);
void			player_hit(t_game *g, int damage);
void			player_game_restart(t_game *g);
void			player_game_over(t_game *g);
void			player_win(t_game *g);

/*
** ============================================================================
**   Functions -- [[ facility/ ]]
** ============================================================================
*/

/*
**  ** Facility **
*/

t_bool			facility_can_interact(t_point pt, t_entity *e);
t_bool			facility_is_in_someone(t_game *g, t_point pt);
void			facility_update(t_game *g);

/*
**  ** Door **
*/

t_door			*door_get(t_map *m, int x, int y);
t_bool			door_interact(t_game *g, t_entity *p, t_point pos);
void			door_update(t_game *g, t_door *door);
t_bool			door_is_throughable(t_map *m, int x, int y);

/*
**  ** Secret **
*/

t_secret		*secret_get(t_map *m, int x, int y);
t_bool			secret_interact(t_game *g, t_entity *p, t_point pos);
void			secret_update(t_game *g, t_secret *secret);
t_bool			secret_is_throughable(t_map *m, int x, int y);

/*
**  ** Exit **
*/

void			exit_interact(t_game *g, t_entity *p);

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
double			util_getf(double x);
double			util_distance(t_vector2 v1, t_vector2 v2);
void			util_lstdel_find(t_game *g, t_list *del);
uint64_t		util_random_int(void);
double			util_random_double(void);

/*
**  ** Geometry (Raycasting) **
*/

t_raycast		geometry_raycast(t_game *g, t_vector2 o, t_vector2 ry, int md);
t_bool			geometry_raycast_door(t_game *g, t_raycast *r, t_vector2 *ray);
t_bool			geometry_raycast_secret(t_game *g, t_raycast *r, t_vector2 *y);
double			geometry_correct(t_raycast *r, t_vector2 rd);
double			geometry_get_orthodist(t_game *g, t_raycast *r, t_vector2 rd);
int				geometry_shade(double dist, int color);
t_bool			geometry_raycast_life(t_game *g, t_raycast *r, t_vector2 *ray);
t_bool			geometry_raycast_user(t_game *g, t_raycast *r, t_vector2 *ry);

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
t_bool			project_skybox(t_game *g, t_vector2 dir);

/*
**  ** Screen **
*/

t_bool			screen_init(t_game *g);
void			screen_uninit(t_game *g);
t_bool			screen_draw(t_game *g);
void			screen_setcolormap(t_game *g, int color, size_t dur);
void			screen_apply_colormap(t_game *g);

/*
** ============================================================================
**   Functions -- [[ output/ ]]
** ============================================================================
*/

/*
**  ** BMP **
*/

t_bool			bmp_save(t_game *g, t_image *img, t_cchar *filename);

/*
** ============================================================================
**   Functions -- [[ hud/ ]]
** ============================================================================
*/

/*
**  ** Hud **
*/

void			hud_put(t_game *g, t_point pos, t_size sz, int tex);
t_point			hud_middle_offset(t_game *g, t_point off, t_size sz, int type);
t_bool			hud_draw(t_game *g);
void			hud_draw_digit(t_game *g, t_point pos, int number);
double			hud_scale(t_game *g, int type);
t_point			hud_offset(t_game *g, int type);
t_size			hud_size(t_game *g, int type);
int				hud_to_resid(t_game *g, int id);
void			hud_draw_weapon(t_game *g);
void			hud_draw_text(t_game *g);
void			hud_draw_lifebar(t_game *g);

/*
** ============================================================================
**   Functions -- [[ weapon/ ]]
** ============================================================================
*/

/*
**  ** Weapon **
*/

void			weapon_init(t_game *g);
void			weapon_update(t_game *g, t_entity *e, t_texset *tex);
int				weapon_cur(t_game *g);
int				weapon_calc_damage(t_weapon *wp, t_entity *e, t_vector2 d);
void			weapon_player_fire(t_game *g, t_entity *p);
void			weapon_player_switch(t_game *g, t_entity *p, int forced);

/*
** ============================================================================
**   Functions -- [[ sound/ ]]
** ============================================================================
*/

/*
**  ** Sound **
*/

void			sound_init(t_game *g);
void			sound_play(t_game *g, int sound, t_vector2 pos, t_bool loop);
void			sound_stop(t_game *g, int sound);

#endif
