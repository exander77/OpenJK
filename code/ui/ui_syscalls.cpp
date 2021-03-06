/*
This file is part of Jedi Academy.

    Jedi Academy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Jedi Academy is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Jedi Academy.  If not, see <http://www.gnu.org/licenses/>.
*/
// Copyright 2001-2013 Raven Software
// Copyright (C) 1999-2000 Id Software, Inc.
//
// leave this at the top of all UI_xxxx files for PCH reasons...
//
#include "../server/exe_headers.h"

#include "ui_local.h"

// this file is only included when building a dll
// syscalls.asm is included instead when building a qvm

#define syscall Q_syscall
static int (*syscall)( int arg, ... ) = (int (*)( int, ...))-1;

void dllEntry( int (*syscallptr)( int arg,... ) ) {
	syscall = syscallptr;
//	CG_PreInit();
}

inline int PASSFLOAT( float x ) 
{
	float	floatTemp;
	floatTemp = x;
	return *(int *)&floatTemp;
}

int CL_UISystemCalls( int *args );


int FloatAsInt( float f );

float trap_Cvar_VariableValue( const char *var_name ) 
{
	int temp;
//	temp = syscall( UI_CVAR_VARIABLEVALUE, var_name );
	temp = FloatAsInt( Cvar_VariableValue(var_name) );
	return (*(float*)&temp);
}


void trap_R_ClearScene( void )
{
	ui.R_ClearScene();
}

void trap_R_AddRefEntityToScene( const refEntity_t *re )
{
	ui.R_AddRefEntityToScene(re);
}

void trap_R_RenderScene( const refdef_t *fd ) 
{
//	syscall( UI_R_RENDERSCENE, fd );
	ui.R_RenderScene(fd);
}

void trap_R_SetColor( const float *rgba ) 
{
//	syscall( UI_R_SETCOLOR, rgba );
//	re.SetColor( rgba );
	ui.R_SetColor(rgba);
}

void trap_R_DrawStretchPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader ) 
{
//	syscall( UI_R_DRAWSTRETCHPIC, PASSFLOAT(x), PASSFLOAT(y), PASSFLOAT(w), PASSFLOAT(h), PASSFLOAT(s1), PASSFLOAT(t1), PASSFLOAT(s2), PASSFLOAT(t2), hShader );
//	re.DrawStretchPic( x, y, w, h, s1, t1, s2, t2, hShader  );

	ui.R_DrawStretchPic( x, y, w, h, s1, t1, s2, t2, hShader );

}

void	trap_R_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs ) 
{
//	syscall( UI_R_MODELBOUNDS, model, mins, maxs );
	ui.R_ModelBounds(model, mins, maxs);
}

void trap_S_StartLocalSound( sfxHandle_t sfx, int channelNum ) 
{
//	syscall( UI_S_STARTLOCALSOUND, sfx, channelNum );
	S_StartLocalSound( sfx, channelNum );
}


void trap_S_StopSounds( void ) 
{
	S_StopSounds( );
}

sfxHandle_t	trap_S_RegisterSound( const char *sample, qboolean compressed ) 
{
	return S_RegisterSound(sample);
}

void trap_Key_SetBinding( int keynum, const char *binding ) 
{
	Key_SetBinding( keynum, binding);
}

qboolean trap_Key_GetOverstrikeMode( void ) 
{
	return Key_GetOverstrikeMode();
}

void trap_Key_SetOverstrikeMode( qboolean state ) 
{
	Key_SetOverstrikeMode( state );
}

void trap_Key_ClearStates( void ) 
{
	Key_ClearStates();
}

int Key_GetCatcher( void );

int trap_Key_GetCatcher( void ) 
{
	return Key_GetCatcher();
}

void Key_SetCatcher( int catcher ); 

void trap_Key_SetCatcher( int catcher ) 
{
	Key_SetCatcher( catcher );
}
/*
void trap_GetClipboardData( char *buf, int bufsize ) {
	syscall( UI_GETCLIPBOARDDATA, buf, bufsize );
}

void trap_GetClientState( uiClientState_t *state ) {
	syscall( UI_GETCLIENTSTATE, state );
}
*/

void CL_GetGlconfig( glconfig_t *glconfig );

void trap_GetGlconfig( glconfig_t *glconfig ) 
{
//	syscall( UI_GETGLCONFIG, glconfig );
	CL_GetGlconfig( glconfig );
}

#ifndef _XBOX
// this returns a handle.  arg0 is the name in the format "idlogo.roq", set arg1 to NULL, alteredstates to qfalse (do not alter gamestate)
int trap_CIN_PlayCinematic( const char *arg0, int xpos, int ypos, int width, int height, int bits, const char *psAudioFile) {
  return syscall(UI_CIN_PLAYCINEMATIC, arg0, xpos, ypos, width, height, bits, psAudioFile);
}
#endif

// stops playing the cinematic and ends it.  should always return FMV_EOF
// cinematics must be stopped in reverse order of when they are started
int trap_CIN_StopCinematic(int handle) 
{
  return syscall(UI_CIN_STOPCINEMATIC, handle);
}

