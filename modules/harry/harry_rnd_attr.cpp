/*************************************************************************/
/*  harry_basic_primitive.cpp                                            */
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

#include "harry_rnd_attr.h"

/**
  @Author iWhiteRabbiT
*/

//void HarryRndAttr::create_geo() {
//
//	float decal = 2.0f * (Math::rand()%1000)/1000.0f;
//
//	int p0 = add_point(Vector3(0, decal, 0));
//	int p1 = add_point(Vector3(1, decal, 0));
//	int p2 = add_point(Vector3(1, decal, 1));
//	int p3 = add_point(Vector3(0, decal, 1));
//
//	PoolVector<int> tri;
//	tri.resize(3);
//
//	tri.set(0, p0);
//	tri.set(1, p1);
//	tri.set(2, p2);
//	add_prim(tri, true);
//
//	tri.set(0, p0);
//	tri.set(1, p2);
//	tri.set(2, p3);
//	add_prim(tri, true);
//}

void HarryRndAttr::RandomizeAttr(HarryNode *p_node, AttribClass p_attr_class, StringName p_attr, Variant p_default, float min, float max) {

	int c = p_node->get_attrib_class_count(p_attr_class);

	if (c == 0)
		return;

	Variant::Type type = p_default.get_type();

	if (type == Variant::VECTOR3) {

		for (int i = 0; i < c; i++) {

			Vector3 &v = Vector3(
					Math::random(min, max),
					Math::random(min, max),
					Math::random(min, max));

			p_node->set_attrib(p_attr_class, p_attr, i, v, p_default);
		}

		return;
	}

	if (type == Variant::VECTOR2) {

		for (int i = 0; i < c; i++) {

			Vector2 &v = Vector2(
					Math::random(min, max),
					Math::random(min, max));

			p_node->set_attrib(p_attr_class, p_attr, i, v, p_default);
		}

		return;
	}

	if (type == Variant::COLOR) {

		for (int i = 0; i < c; i++) {

			Color &v = Color(
					Math::random(min, max),
					Math::random(min, max),
					Math::random(min, max));

			p_node->set_attrib(p_attr_class, p_attr, i, v, p_default);
		}

		return;
	}

	if (type == Variant::REAL) {

		for (int i = 0; i < c; i++)
			p_node->set_attrib(p_attr_class, p_attr, i, Math::random(min, max), p_default);

		return;
	}

	if (type == Variant::INT) {

		for (int i = 0; i < c; i++)
			p_node->set_attrib(p_attr_class, p_attr, i, Math::fast_ftoi(Math::random(min, max)), p_default);

		return;
	}
}
