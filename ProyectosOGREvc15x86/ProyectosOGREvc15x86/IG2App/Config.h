#pragma once
//clase para declarar constantes

using uint = unsigned int;
const uint CUBE_SIZE = 98;
const uint VIDAS = 3;
const uint PUNTOS_POR_PERLA = 10;
const uint ENEMY_LIFES = 1;
const uint SUBDIVISION_LUZ_PLANO = 200;

const float ENEMY_SPEED = 2.0f;
const float PERLA_SCALE = 0.1f;
const float OGRE_SCALE = 10.0f;
const float PLAYER_SPEED = 3.0f;
const float INVENCIBLE_TIME = 100.0f;

const float OGRE_SCALE_ANIM = 30.0f;
const float SUELO_SCALE_ANIM = 7000.0f;
const float SUELO_BAJAR_ANIM = -2.0f;
const std::string DIR_MAT_SUELO_ANIM = "Examples/FloorAnim";
const float ANIM_DURATION = 21.0f;
const float STOP_DANCING = 4.0f;
const float SPIN = 10.0f;
const float SECOND_SPIN = 15.0f;
const float TIME_FOR_SPIN = 1.0f;
const float TIEMPO_BAILE = 4000.0f;
const float TIEMPO_MAX = 21000.0f;
const float MUESTRA_ESPADAS = 10000.0f;

const float TIEMPO_OGREHEAD_EMIT_HUM = 5000.0f;
const float TIEMPO_OGREHEAD_STOP_EMIT_HUM = 19800.0f;
const std::string DIRECCION_PART_HUMO = "Particulas/HumoOgreHead";


const std::string DIRECCION_PART_HUMO_MAPA = "Particulas/HumoMapa";


const float TIEMPO_EMIT_Fire = 0.0f;
const float TIEMPO_STOP_EMIT_Fire = 17000.0f;
const std::string DIRECCION_PART_FUEGO = "Particulas/Fire";

const std::string DIRECCION_MAT_PERLA = "Examples/CloudySky";
const std::string DIRECCION_MAT_MURO = "Examples/BumpyMetal";
const std::string DIRECCION_MAT_SUELO = "Examples/BeachStones";