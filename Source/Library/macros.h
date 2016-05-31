// MACROS.H : Global Macro Definitions.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the global macro definitions.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/12/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MACROS_H__
#define __MACROS_H__


// Specify the standard VGA color macros
#define MINCOLORPALETTEINDEX   0
#define VGA_COLOR_BLACK   PALETTEINDEX(0)
#define VGA_COLOR_RED   PALETTEINDEX(1)
#define VGA_COLOR_GREEN   PALETTEINDEX(2)
#define VGA_COLOR_YELLOW   PALETTEINDEX(3)
#define VGA_COLOR_BLUE   PALETTEINDEX(4)
#define VGA_COLOR_MAGENTA   PALETTEINDEX(5)
#define VGA_COLOR_CYAN   PALETTEINDEX(6)
#define VGA_COLOR_GRAY   PALETTEINDEX(12)
#define VGA_COLOR_LTGRAY   PALETTEINDEX(7)
#define VGA_COLOR_LTRED   PALETTEINDEX(13)
#define VGA_COLOR_LTGREEN   PALETTEINDEX(14)
#define VGA_COLOR_LTYELLOW   PALETTEINDEX(15)
#define VGA_COLOR_LTBLUE   PALETTEINDEX(16)
#define VGA_COLOR_LTMAGENTA   PALETTEINDEX(17)
#define VGA_COLOR_LTCYAN   PALETTEINDEX(18)
#define VGA_COLOR_WHITE   PALETTEINDEX(19)
#define MAXCOLORPALETTEINDEX   19
#define RGB_COLOR_BLACK   RGB(1,1,1)

// Specify the default floating point decimal places
#define DEFAULTFLOATINGPOINTNUMBERPLACES   16
#define DEFAULTFLOATINGPOINTDECIMALPLACES   8

// Specify the string and character related conversion inline macros
inline INT STRINGCHARS(INT cb) { return max(cb / (INT) sizeof(TCHAR) - 1, 0); }
inline INT STRINGBYTES(INT cb) { return max(cb - (INT) sizeof(TCHAR), 0); }

// Specify the string and character related macros
#ifndef EMPTYSTRING
#define EMPTYSTRING   ((LPCTSTR) TEXT(""))
#endif
#ifndef SPACE
#define SPACE   ((LPCTSTR) TEXT(" "))
#endif
#ifndef SINGLEQUOTE
#define SINGLEQUOTE   ((TCHAR) TEXT('\''))
#endif
#ifndef DOUBLEQUOTE
#define DOUBLEQUOTE   ((TCHAR) TEXT('"'))
#endif
#ifndef PLUS
#define PLUS   ((TCHAR) TEXT('+'))
#endif
#ifndef MINUS
#define MINUS   ((TCHAR) TEXT('-'))
#endif
#ifndef BOLD
#define BOLD   ((TCHAR) TEXT('\b'))
#endif
#ifndef TAB
#define TAB   ((TCHAR) TEXT('\t'))
#endif
#ifndef EOL
#define EOL   ((TCHAR) TEXT('\n'))
#endif
#ifndef EOS
#define EOS   ((TCHAR) TEXT('\0'))
#endif
#ifndef CR
#define CR   ((TCHAR) TEXT('\r'))
#endif
#ifndef FF
#define FF   ((TCHAR) TEXT('\f'))
#endif

// Specify some code page identifiers
#define US_ASCII   20127
#define UTF_8   65001


#endif // __MACROS_H__
