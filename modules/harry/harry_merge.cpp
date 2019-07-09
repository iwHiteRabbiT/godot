/*************************************************************************/
/*  harry_merge.cpp                                                      */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "harry_merge.h"

/**
  @Author iWhiteRabbiT
*/

void HarryMerge::create_geo(Vector<CacheCount> &p_input_caches, bool bypass) {

	int nc = p_input_caches.size();
	if (nc>0)
		copy_from_cache(p_input_caches[0]);

	if (bypass)
		return;

	Map<AttribClass, int> decal_by_class;	

	for (int i=1; i<nc ; i++) {

		for (AttribClass attr_c = POINT; attr_c != DETAIL; attr_c = (AttribClass)(attr_c + 1)) {

			CacheCount cc = p_input_caches[i];

			int count = cc.att_count_size[attr_c].count;
			decal_by_class[attr_c] = count;

			int old_count = att_count_size[attr_c].count;
			att_count_size[attr_c].size = 0;

			int tt_count = old_count + count;
			add_row(attr_c, tt_count);
			att_count_size[attr_c].count = tt_count;

			for (ATTRMAP::Element *a = cc.cache[attr_c].front(); a; a = a->next()) {

				const StringName &name = a->key();
				HarryNode::DefaultVectorVariant &dvv = a->get();

				for(int i=0 ; i<count ; i++) {

					Variant v = dvv.values[i];

					if (name == "PointNum") {
						v = (int)v + decal_by_class[POINT];
					}
					else if (name == "Vertices") {

						Array vs = (Array)v;

						for(int iv=0; iv<vs.size(); iv++)
							vs[iv] = (int)vs[iv] + decal_by_class[VERTEX];

						v = vs;
					}

					set_attrib(attr_c, name, old_count + i, v, dvv.default);
				}
			}
		}
	}
}