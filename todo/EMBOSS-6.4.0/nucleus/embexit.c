/* @source embexit.c
**
** General routines for alignment.
** Copyright (c) 1999 Peter Rice
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
******************************************************************************/

#include "emboss.h"




/* @func embExit **************************************************************
**
** Cleans up as necessary, and calls ajExit
**
** @return [void]
** @@
******************************************************************************/

__noreturn void embExit (void)
{
    ajUtilLoginfo();
    embSigExit();
    embDbiExit();
    embGrpExit();
    embIndexExit();
    embWordExit();
    embPatlistExit();

    ajTextdbExit();
    ajSeqDbExit();
    ajFeatdbExit();
    ajObodbExit();
    ajAssemdbExit();
    ajTaxdbExit();
    ajUrldbExit();
    ajVardbExit();
    ajResourcedbExit();

    ajGraphicsExit();
    ajAcdExit(ajFalse);

    ajExit();
}




/* @func embExitBad ***********************************************************
**
** Cleans up as necessary, and calls ajExitBad
**
** @return [void]
** @@
******************************************************************************/

__noreturn void embExitBad (void)
{
    ajExitBad();
}
