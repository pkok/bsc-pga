// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2002-2009, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifndef _OSDEP_H_
#define _OSDEP_H_

#ifdef WIN32
#define strcmpnc stricmp
#else
#define strcmpnc strcasecmp
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846 
#endif
#define U_RAD2DEG( x ) ( (x) * (float)180.0 / (float)M_PI)
#define U_DEG2RAD( x ) ( (x) * (float)M_PI / (float)180.0)

int fileLength(FILE *F);

/*
returns time (in seconds) passed, since some arbitrary point in the past (e.g. client or workstation startup)
returns -1.0 on error
*/
double u_timeGet();

/*
returns time (in seconds) passed since last call to this function (returns 0.0 the first time)
returns -1.0 on error
*/
double u_timeElapsed();


// deletes 'fullname'
int deleteFile(const char *fullname);

/*
This function will try to determine if 'filename' is an absolute filename
or a relative filename. 

If it finds it is an absoluate filename, it will simply copy 'filename' to 'dst'.

Otherwise, it will try search for the last (back-)slash in 'base'. If that 
(back-)slash is not present, 'filename' will be copied 'dst'. Othersize,
'dst' will be set to 'base' + 


dst: destionation string
base: filename (if is is a path, it must end with a '/' or '\') that is used as 
a reference relative to which 'filename' may or may not be specified
filename: the absolute or relative filename
*/
// (obsolete, replaced by state->fullFilename())
//int fullFilename(char *dst, const char *base, const char *filename);

#ifdef WIN32
/*
Puts the current working directory in front of the filename
*/
//int fullFilenameCWD(char *filename);
#endif /* WIN32 */


#define U_MIN(x, y) ( ((x) < (y)) ? (x) : (y))
#define U_MAX(x, y) ( ((x) > (y)) ? (x) : (y))
#define U_ABS(x) ( ((x) >= (0)) ? (x) : -(x))
#define U_SIGN(x) ( ((x) >= (0)) ? (1) : -(1))


/*
Platform independant directory reading
*/

#ifdef WIN32
#include <windows.h>
#else /* assume UNIX */
#include <sys/types.h>
#include <sys/stat.h>
#ifdef SUN
#include <dirent.h>
#else
#include <sys/dir.h>
#endif /* SUN */
#endif /* WIN32 */

// error codes return by functions returning an int
#define U_DIR_OK 0				// all ok
#define U_DIR_ERROR -1		// a error occured
#define U_DIR_END  -2			  // end of directory reached

typedef struct u_dirEnt_s {
	char *dirName;
#ifdef WIN32
	WIN32_FIND_DATA FD;
	HANDLE hFile;
	int next;
#else /* assume UNIX */
	DIR *dir;
#ifdef SUN
	struct dirent *dp;
#else
	struct direct *dp;
#endif /* SUN */
#endif /* WIN32 */
} u_dirEnt;

// flags returned by u_dirNext()
#define U_DIR_FILE 0x01		// file is a 'real' file
#define U_DIR_DIR  0x02		// file is a directory

/*
get and set the current working directory 
*/
int u_dirSetCwd(const char *dirname);
int u_dirGetCwd(char *dirname, int maxlen);

/*
'Opens' a directory. Returns a pointer to a platform dependant 'directory entry struct'.
This 'u_dirEnt' must be closed with closeu_dirEnt() to free resources.
'ext' specifies the extension of the files you want to be listed. Pass NULL for
all files.
*/
u_dirEnt *u_dirOpen(const char *dirname, const char *ext);

/*
Is used to close a valid u_dirEnt struct. Frees any resources used by 'dir'.
The pointer to 'dir' is invalid after this call.
*/
void u_dirClose(u_dirEnt *dir);

/*
Returns the name of the next file in the directory.
maxlen is the maximum length of the name including the terminating '\0'
The name returned is the name _relative_ to the directory, so not the fullname
Returns a flag specifying the properties of the file (DIR_X)
*/
int u_dirNext(u_dirEnt *dir, char *name, int maxlen);

/*
Adds the path of 'dir' to 'name' to make a 'fullname'
maxlen is the maximum length of the 'fullname' including the terminating '\0'
*/
int u_dirFullName(u_dirEnt *dir, const char *name, char *fullname, int maxlen);

/*
Creates directory 'fullname'. Returns DIR_ERROR on failure
*/
int u_dirCreate(const char *fullname);

/*
Creates directory 'fullname'. Returns dirEnt on success
If already exist: only opens the directory
*/
u_dirEnt *u_dirOpenOrCreate(const char *dirname, const char *ext);


/*
Delete a file 
*/
int u_dirFileDelete(const char *fullname);

/*
Delete a directory (only when all files have been removed from directory)
*/
int u_dirDirDelete(const char *fullname);

/* returns the length of the file F */
int fileLengthByName(const char *name);


#endif /* _OSDEP_H_ */
