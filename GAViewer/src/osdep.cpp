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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#include <direct.h>
#else /* assume UNIX */
#include <sys/times.h>  // times() function
#include <unistd.h>     // sysconf() function
#include <sys/types.h>
#include <sys/stat.h>
#ifdef SUN
#include <dirent.h>
#endif /* SUN */
#endif /* WIN32/UNIX */

#include "state.h"
#include "osdep.h"




int fileLength(FILE *F) {
	long oldPos, pos;
	if (F == NULL) {
		printf("fileLength(): invalid file pointer\n");
		return -1;
	}
	if ( (oldPos = ftell(F)) < 0) {
		printf("fileLength(): ftell() failed\n");
		return -1;
	}

	if (fseek(F, 0, SEEK_END) != 0) {
		printf("fileLength(): fseek() failed\n");
		return -1;
	}

	if ( (pos = ftell(F)) < 0) {
		printf("fileLength(): ftell() failed\n");
		return -1;
	}

	if (fseek(F, oldPos, SEEK_SET) != 0) {
		printf("fileLength(): fseek() failed\n");
		return -1;
	}

	return pos;
}

// The timer resolutions for both possible platforms are stored in these variables
#ifdef WIN32
	static LARGE_INTEGER s_Performancetimerresolution;
#else /* assume UNIX */
	static long s_Clktck;  
#endif /* WIN32/UNIX */

// true once one-time initialization has been done
static int s_TimeInitDone = 0;

// when was timeElapsed() last called?
static double s_LastTimeElapsed = -1.0;

static int u_timeInit() {
#ifndef WIN32
	struct tms TMS;
#endif
	if (s_TimeInitDone) {
		printf("timeInit(): already called?\n");
		return -1;
	}

#ifdef WIN32
	if (!QueryPerformanceFrequency(&s_Performancetimerresolution)) {
		printf("timeInit(): could not QueryPerformanceFrequency()\n");
		return -1;
	}
#else /* assume UNIX */
	// get size of clock tick
	if ( (s_Clktck = sysconf(_SC_CLK_TCK)) < 0) {
	    printf("timeInit(): sysconf() error\n");
	    return -1;
	}
#endif /* WIN32 or UNIX */

	s_TimeInitDone = 1;

	return 0;
}

/*
returns time (in seconds) passed, since some arbitrary point in the past (e.g. client or workstation startup)
*/
double u_timeGet() {
	int err;
#ifdef WIN32
	LARGE_INTEGER counter;
#else /* assume UNIX */
	unsigned int real;
	struct tms TMS;
	double e,t;
#endif /* WIN32 or UNIX */

	// check for initialization
	if (!s_TimeInitDone) if ( (err = u_timeInit()) != 0) return -1.0;

#ifdef WIN32
	if (!QueryPerformanceCounter(&counter)){
		printf("timeGet(): could not QueryPerformanceCounter()\n");
		return -1.0;
	}
	return (double)(counter.QuadPart) / (double)s_Performancetimerresolution.QuadPart;
#else /* assume UNIX */
	// get current times
	// todo: adjust for long up-times
	if ( (real = (unsigned int)times(&TMS)) == (unsigned int)-1) {
	    printf("timeGet(): times() error\n");
	    return -1.0;
	}

	// process results; return elapsed time
	return (double)(real) / (double)s_Clktck;
#endif /* WIN32 or UNIX */
}

/*
returns time (in seconds) passed since last call to this function (0.0 the first time)
*/
double u_timeElapsed() {
	double t, temp;

	if ( (t = u_timeGet()) < 0.0) return -1.0;
	
	if (s_LastTimeElapsed < 0) {
		s_LastTimeElapsed = t;
		return 0.0;
	}
	else {
		temp = s_LastTimeElapsed;
		s_LastTimeElapsed = t;
		return t - temp;
	}
}

#ifdef WIN32
int deleteFile(const char *fullname) {
	return DeleteFile(fullname) ? 0 : -1;
}
#else // assume UNIX
int deleteFile(const char *fullname) {
	// error handling ok?
	return unlink(fullname) ? -1 : 0;
}
#endif


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
int fullFilename(char *dst, const char *base, const char *filename) {
	if ((filename == NULL) || (dst == NULL)) return -1;

	if (base == NULL) { // if no base specified, assume filename is absolute
		strcpy(dst, filename);
		return 0;
	}

	// check if filename is absolute
#ifdef WIN32
	if (((filename[0] == '\\') && (filename[1] == '\\')) ||
		(filename[1] == ':')) {
#else // assume UNIX
	if (filename[0] == '/') {
#endif
		strcpy(dst, filename);
		return 0;
	}

	// check for a (back)slash in base
	char *ptr;
	strcpy(dst, base);
	if ((ptr = strrchr(dst, '\\')) || (ptr = strrchr(dst, '/'))) {
		strcpy(ptr + 1, filename);
	}
	else { // assume filename is absolute
		strcpy(dst, filename);
	}

	return 0;
}

#ifdef WIN32
	/*
	Puts the current working directory in front of the filename
	*/
int fullFilenameCWD(char *filename) {
	char dir[1024];
	_getcwd(dir, 1023);

	memmove(filename + strlen(dir) + 1, filename, strlen(filename)  + 1);
	memcpy(filename, dir, strlen(dir));
	filename[strlen(dir)] = '\\';
	return 0;
}
#endif /* WIN32 */


/*
Platform independent directory reading
*/

u_dirEnt *u_dirOpenOrCreate(const char *dirname, const char *ext) {
	u_dirEnt *ent;
	if (ent = u_dirOpen(dirname, ext)) return ent;
	if (u_dirCreate(dirname)) return NULL;
	return u_dirOpen(dirname, ext);
}

#ifdef WIN32
// The win32 implementations of 'u_dir'

/*
'Opens' a directory. Returns a pointer to a platform dependant 'directory entry struct'.
This 'u_dirEnt' must be closed with closeu_dirEnt() to free resources.
ext can be used to limit the search to files ending on .ext only.
*/
u_dirEnt *u_dirOpen(const char *dirname, const char *ext) {
    u_dirEnt *dir;

    // sanity check
    if (dirname == NULL) {
        cprintf("dirOpen(): null pointer passed.\n");
        return NULL;
    }

    // allocate mem for struct
    if ( (dir = (u_dirEnt *)malloc(sizeof(u_dirEnt))) == NULL) {
        cprintf("dirOpen(): memory allocation error for %d bytes.\n",
            sizeof(u_dirEnt));
        return NULL;
    }

    // reset struct content
    dir->dirName = NULL;
    dir->hFile = NULL;

    // copy dirname
    if ( (dir->dirName = (char*)malloc(strlen(dirname) + 1 + 16)) == NULL) {        // + 16 for extension
        cprintf("dirOpen(): memory allocation error for %d bytes.\n",
            strlen(dirname) + 1);
        free(dir);
        return NULL;
    }

    // setup search pattern
    if (ext) {
        sprintf(dir->dirName, "%s/*.%s", dirname, ext);
    }
    else {
        sprintf(dir->dirName, "%s/*.*", dirname);
    }

    // open directory
    if ( (dir->hFile = FindFirstFile(dir->dirName, &(dir->FD))) == INVALID_HANDLE_VALUE) {
        // regular error -> don't complain...
        free(dir->dirName);
        free(dir);
        return NULL;
    }

    dir->next = 1;

    // copy directory name
    strcpy(dir->dirName, dirname);

    return dir;
}

/*
Is used to close a valid u_dirEnt struct. Frees any resources used by 'dir'.
The pointer to 'dir' is invalid after this call.
*/
void u_dirClose(u_dirEnt *dir) {
    // sanity check
    if (dir == NULL) {
        cprintf("u_dirClose(): null pointer passed.\n");
        return;
    }

    // close directory; free resources
    FindClose(dir->hFile);
    free(dir->dirName);
    dir->hFile = NULL;
    dir->dirName = NULL;
    free(dir);
}


/*
Returns the name of the next file in the directory.
maxlen is the maximum length of the name including the terminating '\0'
The name returned is the name _relative_ to the directory, so not the fullname
Returns a flag specifying the properties of the file (U_DIR_X)
*/
int u_dirNext(u_dirEnt *dir, char *name, int maxlen) {
    int ret;

    if (!dir->next) return U_DIR_END;

    // copy file if there is space
    if ((int)(strlen(dir->FD.cFileName) + 1) > maxlen) {
        return U_DIR_ERROR;
    }
    strcpy(name, dir->FD.cFileName);

    // return correct flag
    if (dir->FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ret = U_DIR_DIR;
    else ret = U_DIR_FILE;

    // thou shall move on to the next...
    if (!FindNextFile(dir->hFile, &(dir->FD))) {
        dir->next = 0;
    }

    return ret;
}


/*
Adds the path of 'dir' to 'name' to make a 'fullname'
maxlen is the maximum length of the 'fullname' including the terminating '\0'
*/
int u_dirFullName(u_dirEnt *dir, const char *name, char *fullname, int maxlen) {
    if ((int)(strlen(dir->dirName) + strlen(name) + 2) > maxlen) {
        return -1;
    }
    sprintf(fullname, "%s/%s", dir->dirName, name);
    return U_DIR_OK;
}

/*
Creates directory 'fullname'. Returns U_DIR_ERROR on failure
*/
int u_dirCreate(const char *fullname) {
    if (!CreateDirectory(fullname, NULL)) return U_DIR_ERROR;
    return U_DIR_OK;
}

int u_dirFileDelete(const char *fullname) {
	return DeleteFile(fullname) ? U_DIR_OK : U_DIR_ERROR;
}

/*
Delete a directory (only when all files have been removed from directory)
*/
int u_dirDirDelete(const char *fullname) {
	return RemoveDirectory(fullname) ? U_DIR_OK : U_DIR_ERROR;
}

int u_dirSetCwd(const char *dirname) {
	return (_chdir(dirname)) ? U_DIR_ERROR : U_DIR_OK;
}

int u_dirGetCwd(char *dirname, int maxlen) {
	if (dirname == NULL) return U_DIR_ERROR;
	return (_getcwd(dirname, maxlen-1)) ? U_DIR_OK : U_DIR_ERROR;
}

#else /* assume UNIX */

// The UNIX implementations of 'u_dir'

u_dirEnt *u_dirOpen(const char *dirname, const char *ext /* = NULL */) {
    u_dirEnt *dir;

    if (dirname == NULL) {
        cprintf("dirOpen(): null pointer passed.\n", sizeof(u_dirEnt));        
        return NULL;
    }
    // allocate mem for struct
    if ( (dir = (u_dirEnt *)malloc(sizeof(u_dirEnt))) == NULL) {
        cprintf("dirOpen(): memory allocation error for %d bytes.\n", sizeof(u_dirEnt));
        return NULL;
    }
    // copy dirname
    if ( (dir->dirName = (char*)malloc(strlen(dirname) + 1 + 16)) == NULL) {        // + 16 for extension
        cprintf("dirOpen(): memory allocation error for %d bytes.\n", strlen(dirname) + 1);
        free(dir);
        return NULL;
    }
    sprintf(dir->dirName, "%s", dirname);

    if ((dir->dir = opendir(dirname)) == NULL)
    {
        printf("can't open %s directory.\n", dirname);
        free(dir->dirName);
        free(dir);
        return NULL;
    }

    rewinddir(dir->dir);

    return dir;
}

void u_dirClose(u_dirEnt *dir) {
    // sanity check
    if (dir == NULL) {
        cprintf("dirClose(): null pointer passed.\n");
        return;
    }
        closedir(dir->dir);
    free(dir->dirName);
    free(dir);
}


/*
Returns the name of the next file in the directory.
maxlen is the maximum length of the name including the terminating '\0'
The name returned is the name _relative_ to the directory, so not the fullname
Returns a flag specifying the properties of the file (U_DIR_X)
*/

int u_dirNext(u_dirEnt *dir, char *name, int maxlen) {
/*
    struct direct *dp;
*/
    int    ftype;
    struct stat st;
    char file[256];

     while ((dir->dp = readdir(dir->dir)) != NULL) {
         sprintf(name, "%s", dir->dp->d_name);
         sprintf(file, "%s/%s", dir->dirName, dir->dp->d_name);

         if (stat(file, &st) == 0)
         {
             ftype = st.st_mode & S_IFMT;
             switch (ftype)
             {
                 case S_IFDIR:
                    return U_DIR_DIR;
                 case S_IFCHR:
                 case S_IFBLK:
                 case S_IFIFO:
                 case S_IFLNK:
                 case S_IFSOCK:
                     continue;
                 default:
                     return U_DIR_FILE;
             }
         }
         else
         {
             printf("cannot stat %s\n", file);
             continue;
         }
     }
     return U_DIR_END;
}

/*
Adds the path of 'dir' to 'name' to make a 'fullname'
maxlen is the maximum length of the 'fullname' including the terminating '\0'
*/
int u_dirFullName(u_dirEnt *dir, const char *name, char *fullname, int maxlen) {
    if ((int)(strlen(dir->dirName) + strlen(name) + 2) > maxlen) {
        return -1;
    }
    sprintf(fullname, "%s/%s", dir->dirName, name);
    return U_DIR_OK;
}

/*
Creates directory 'fullname'. Returns U_DIR_ERROR on failure
*/
int u_dirCreate(const char *fullname) {
    if (mkdir(fullname,  S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH))
        return U_DIR_ERROR;
    return U_DIR_OK;
}

int u_dirFileDelete(const char *fullname) {
	// error handling ok?
	return unlink(fullname) ? U_DIR_ERROR : U_DIR_OK ;
}

/*
Delete a directory (only when all files have been removed from directory)
*/
int u_dirDirDelete(const char *fullname) {
	return rmdir(fullname) ? U_DIR_ERROR : U_DIR_OK ;
}


int u_dirSetCwd(const char *dirname) {
	return (chdir(dirname)) ? U_DIR_ERROR : U_DIR_OK;
}

int u_dirGetCwd(char *dirname, int maxlen) {
	if (dirname == NULL) return U_DIR_ERROR;
	return (getcwd(dirname, maxlen)) ? U_DIR_OK : U_DIR_ERROR;
}


#endif /* WIN32 */

int fileLengthByName(const char *name) {
	FILE *F;
	int l;
	
	if ( (F = fopen(name, "rb")) == NULL) {
		cprintf("fileLengthByName(): can not open '%s'\n", name);
		return U_DIR_ERROR;
	}

	l = fileLength(F);
	fclose(F);
	return l;
}

