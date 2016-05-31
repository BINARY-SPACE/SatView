// SCRIPTS.H : Scripts Code Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the automation script assemblies related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/02/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SCRIPTS_H__
#define __SCRIPTS_H__

#include <math.h>


#define NULL   0

#define SPACE   L##' '
#define TAB   L##'\t'
#define EOL   L##'\n'
#define EOS   L##'\0'
#define CR   L##'\r'
#define FF   L##'\f'

#define SPACESTRING   L##" "
#define EMPTYSTRING   L##""

#define SCRIPTSCOMPILER_ERROR_FORMAT   L##"{0}: {1}"
#define SCRIPTSCOMPILER_ERROR_LINEFORMAT   L##"{0} ({1}): {2}"
#define SCRIPTSCOMPILER_WARNING_FORMAT   L##"{0}: {1}"
#define SCRIPTSCOMPILER_WARNING_LINEFORMAT   L##"{0} ({1}): {2}"


#endif // __SCRIPTS_H__
