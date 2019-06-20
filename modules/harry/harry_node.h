/*************************************************************************/
/*  harry_node.h                                                         */
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

#ifndef HARRY_NODE_H
#define HARRY_NODE_H

#include "core/resource.h"
#include "scene/resources/mesh.h"


/**
@Author iWhiteRabbiT
*/
class HarryNode : public Resource {
	GDCLASS(HarryNode, Resource);

public:
	enum AttribClass {
		POINT,
		VERTEX,
		PRIMITIVE,
		DETAIL
	};

	struct DefaultVectorVariant {
		Variant default;
		PoolVector<Variant> values;
	};


private:
#define ATTRMAP Map<StringName, HarryNode::DefaultVectorVariant>

	ATTRMAP points;
	ATTRMAP vertices;
	ATTRMAP primitives;
	ATTRMAP details;

	bool has_attrib(ATTRMAP &att, const StringName &p_attribute_name);
	void add_attrib(ATTRMAP &att, const StringName &p_attribute_name, const Variant &p_defvalue);
	void set_attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum, const Variant &p_value); //string mode = "set"
	Variant attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum);

	int add_row(ATTRMAP &att);

protected:
	StringName node_category;
	StringName node_name;
	static void _bind_methods();
	void dirty();

public:
	StringName get_node_category() const { return node_category; }

	String get_node_name() const;
	void set_node_name(const String &p_name);

	ATTRMAP &get_attrib_class(const AttribClass &p_attribclass);

	bool has_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name);
	void add_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, const Variant &p_defvalue);
	void set_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum, const Variant &p_value); //string mode = "set"
	Variant attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum);

	int add_point(Vector3 &p);
	int add_vertex(int prim_num, int point_num);
	int add_prim(PoolVector<int> &points);

	virtual Ref<ArrayMesh> create_mesh();
};

#endif
