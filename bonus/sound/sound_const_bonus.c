/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_const_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:34:00 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 04:54:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		sound_init(t_game *g)
{
	char	**s;

	s = g->resource.sounds;
	s[Sound_None] = NULL;
	s[Sound_BGM1] = "./sounds/BlackPlanet.mp3";
	s[Sound_BGM2] = "./sounds/DededePayback2.mp3";
	s[Sound_BGM3] = "./sounds/DoolyEnding.mp3";
	s[Sound_DoorClose] = "./sounds/DoorClose.wav";
	s[Sound_DoorOpen] = "./sounds/DoorOpen.wav";
	s[Sound_EnemyDie1] = "./sounds/EnemyDie1.wav";
	s[Sound_EnemyDie2] = "./sounds/EnemyDie2.wav";
	s[Sound_EnemyHit] = "./sounds/EnemyHit.wav";
	s[Sound_EnemyHello1] = "./sounds/EnemyHello1.wav";
	s[Sound_EnemyHello2] = "./sounds/EnemyHello2.wav";
	s[Sound_NoWay] = "./sounds/NoWay.wav";
	s[Sound_Pistol] = "./sounds/Pistol.wav";
	s[Sound_PlayerDie] = "./sounds/PlayerDie.wav";
	s[Sound_PlayerHit] = "./sounds/PlayerHit.wav";
	s[Sound_Shotgun] = "./sounds/Shotgun.wav";
	s[Sound_WeaponPickUp] = "./sounds/WeaponPickUp.wav";
	s[Sound_ItemPickUp] = "./sounds/ItemPickUp.wav";
	s[Sound_SecretWall] = "./sounds/SecretWall.wav";
	s[Sound_SecretWallEnd] = "./sounds/SecretWallEnd.wav";
	s[Sound_Foot] = "./sounds/Foot.wav";
	s[Sound_Switch] = "./sounds/Switch.wav";
}
