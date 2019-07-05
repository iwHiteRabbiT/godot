/*************************************************************************/
/*  harry_rnd_attr.h                                                     */
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

#ifndef HARRY_RND_ATTR_H
#define HARRY_RND_ATTR_H

#include "harry_node.h"

/**
  @Author iWhiteRabbiT
*/
class HarryRndAttr : public HarryNode {
	GDCLASS(HarryRndAttr, HarryNode);

	AttribClass attr_class;
	StringName attr_name;
	int dimension;
	Vector3 min_val;
	Vector3 max_val;

protected:
	static void _bind_methods();

	void set_attribute_class(AttribClass attr_class);
	AttribClass get_attribute_class();

	void set_attr_name(StringName attr_name);
	StringName get_attr_name();

	void set_dimension(int dimension);
	int get_dimension();

	void set_min_val(Vector3 min_val);
	Vector3 get_min_val();

	void set_max_val(Vector3 max_val);
	Vector3 get_max_val();

public:
	HarryRndAttr() {
		node_category = "Attribute";
		node_name = "Randomize Attribute";
	}

	static void RandomizeAttr(HarryNode* p_node, AttribClass p_attr_class, StringName p_attr, Variant p_default, float min, float max);

	void create_geo() override;
};

#endif
