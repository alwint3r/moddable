/*
 * Copyright (c) 2016-2017  Moddable Tech, Inc.
 *
 *   This file is part of the Moddable SDK Runtime.
 * 
 *   The Moddable SDK Runtime is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 * 
 *   The Moddable SDK Runtime is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 * 
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with the Moddable SDK Runtime.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and  
 * permission notice:  
 *
 *       Copyright (C) 2010-2016 Marvell International Ltd.
 *       Copyright (C) 2002-2010 Kinoma, Inc.
 *
 *       Licensed under the Apache License, Version 2.0 (the "License");
 *       you may not use this file except in compliance with the License.
 *       You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *       Unless required by applicable law or agreed to in writing, software
 *       distributed under the License is distributed on an "AS IS" BASIS,
 *       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *       See the License for the specific language governing permissions and
 *       limitations under the License.
 */

#include "crypt.h"	/* for crypt_malloc/free */
#include "crypt_common.h"
#include "kcl_arith.h"

typedef struct {
	kcl_z_t *ctx;
	xsSlot proto_int;
} z_t;

typedef struct {
	kcl_mod_t *ctx;
	xsSlot proto_int;
} mod_t;

static inline kcl_int_t *__arith_get_integer(xsMachine *the, xsSlot *slot, xsSlot *proto)
{
	kcl_int_t *ai;

#ifdef __XSMC_H__
	if (!xsmcIsInstanceOf(*slot, *proto))
		kcl_throw_error(the, KCL_ERR_TYPE);
	ai = xsmcGetHostData(*slot);
#else
	if (!xsIsInstanceOf(*slot, *proto))
		kcl_throw_error(the, KCL_ERR_TYPE);
	ai = xsGetHostData(*slot);
#endif
	if (kcl_int_isNaN(ai))
		kcl_throw_error(the, KCL_ERR_NAN);
	return ai;
}

static inline void __arith_set_integer(xsMachine *the, xsSlot *slot, kcl_int_t *ai, xsSlot *proto)
{
#ifdef __XSMC_H__
	*slot = xsmcNewHostInstance(*proto);
	xsmcSetHostData(*slot, ai);
#else
	*slot = xsNewHostInstance(*proto);
	xsSetHostData(*slot, ai);
#endif
}
