/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2014 - 2024 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************
*
*    The GPL License (GPL)
*
*    Copyright (C) 2014 - 2024 Vivante Corporation
*
*    This program is free software; you can redistribute it and/or
*    modify it under the terms of the GNU General Public License
*    as published by the Free Software Foundation; either version 2
*    of the License, or (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*****************************************************************************
*
*    Note: This software is released under dual MIT and GPL licenses. A
*    recipient may use this file under the terms of either the MIT license or
*    GPL License. If you wish to use only one license not the other, you can
*    indicate your decision by deleting one of the above license notices in your
*    version of this file.
*
*****************************************************************************/


#ifndef _GC_HAL_TA_HARDWARE_H_
#define _GC_HAL_TA_HARDWARE_H_
#include "gc_hal_types.h"
#include "gc_hal_security_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _gcsMMU_TABLE_ARRAY_ENTRY
{
    gctUINT32                   low;
    gctUINT32                   high;
}
gcsMMU_TABLE_ARRAY_ENTRY;

typedef struct _gcsHARDWARE_PAGETABLE_ARRAY
{
    /* Number of entries in page table array. */
    gctUINT                     num;

    /* Size in bytes of array. */
    gctSIZE_T                   size;

    /* Physical address of array. */
    gctPHYS_ADDR_T              address;

    /* Memory descriptor. */
    gctPOINTER                  physical;

    /* Logical address of array. */
    gctPOINTER                  logical;
}
gcsHARDWARE_PAGETABLE_ARRAY;

typedef struct _gcsHARWARE_FUNCTION
{
    /* Entry of the function. */
    gctUINT32                   address;

    /* CPU address of the function. */
    gctUINT8_PTR                logical;

    /* Bytes of the function. */
    gctUINT32                   bytes;

    /* Hardware address of END in this function. */
    gctUINT32                   endAddress;

    /* Logical of END in this function. */
    gctUINT8_PTR                endLogical;
}
gcsHARDWARE_FUNCTION;

typedef struct _gcTA_HARDWARE
{
    gctaOS                      os;
    gcTA                        ta;

    gctUINT32                   chipModel;
    gctUINT32                   chipRevision;
    gctUINT32                   productID;
    gctUINT32                   ecoID;
    gctUINT32                   customerID;

    gctPOINTER                  featureDatabase;

    gcsHARDWARE_PAGETABLE_ARRAY pagetableArray;

    /* Function used by gctaHARDWARE. */
    gctPHYS_ADDR                functionPhysical;
    gctPOINTER                  functionLogical;
    gctUINT32                   functionAddress;
    gctSIZE_T                   functionBytes;

    gcsHARDWARE_FUNCTION        functions[1];
}
gcsTA_HARDWARE;

gceSTATUS
gctaHARDWARE_SetMMUStates(
    IN gcTA_HARDWARE Hardware,
    IN gctPOINTER MtlbAddress,
    IN gceMMU_MODE Mode,
    IN gctPOINTER SafeAddress,
    IN gctPOINTER Logical,
    IN OUT gctUINT32 *Bytes
);

gceSTATUS
gctaHARDWARE_MmuEnable(
    IN gcTA_HARDWARE Hardware
);

#ifdef __cplusplus
}
#endif
#endif

