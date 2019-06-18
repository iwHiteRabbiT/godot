/*************************************************************************/
/*  harry.cpp                                                            */
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

#include "harry_node.h"

/**
 * @Author iWhiteRabbiT
*/

ATTRMAP HarryNode::get_attrib_class(const AttribClass &p_attribclass) {
	switch (p_attribclass) {

		case POINT:
			return points;

		case VERTEX:
			return vertices;

		case PRIMITIVE:
			return primitives;

		case DETAIL:
			return details;

		default:
			ERR_EXPLAIN("AttribClass unknown");
			ERR_FAIL_V(ATTRMAP());
	}
}

void HarryNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_node_name", "node_name"), &HarryNode::set_node_name);
	ClassDB::bind_method(D_METHOD("get_node_name"), &HarryNode::get_node_name);

	//ADD_GROUP("Group", "Group_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "node_name"), "set_node_name", "get_node_name");

	ADD_SIGNAL(MethodInfo("name_changed", PropertyInfo(Variant::OBJECT, "node")));
	ADD_SIGNAL(MethodInfo("dirty", PropertyInfo(Variant::OBJECT, "node")));
}

void HarryNode::dirty() {
	//set_edited(true);
	//emit_changed();
	_change_notify();

	Ref<HarryNode> t = this;

	emit_signal("dirty", t);
}

String HarryNode::get_node_name() const {
	return node_name;
}

void HarryNode::set_node_name(const String &p_name) {

	if (node_name == p_name)
		return;

	StringName old_name = node_name;
	node_name = p_name;

	Ref<HarryNode> t = this;

	emit_signal("name_changed", t);
	dirty();
}

bool HarryNode::has_attrib(const AttribClass &attribclass, const StringName &attribute_name) {

	ATTRMAP att = get_attrib_class(attribclass);

	return att.has(attribute_name);
}

void HarryNode::add_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, const Variant &p_defvalue) {

	DefaultVectorVariant dvv;

	ATTRMAP att = get_attrib_class(p_attribclass);

	if (att.has(p_attribute_name)) {
		att[p_attribute_name].default = p_defvalue;
		return;
	}

	dvv.default = p_defvalue;
	att[p_attribute_name] = dvv;
}

void HarryNode::set_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum, const Variant &p_value) {

	ATTRMAP att = get_attrib_class(p_attribclass);

	if (!att.has(p_attribute_name))
		att[p_attribute_name] = DefaultVectorVariant();

	PoolVector<Variant> vals = att[p_attribute_name].values;

	if (vals.size() <= elemnum)
		return;

	vals.write()[elemnum] = p_value;
}

Variant HarryNode::attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum) {

	ATTRMAP att = get_attrib_class(p_attribclass);

	if (!att.has(p_attribute_name)) {
		return Variant();
	}
	   
	PoolVector<Variant> vals = att[p_attribute_name].values;

	if (vals.size() <= elemnum)
		return Variant();

	return vals[elemnum];
}

int HarryNode::add_point(Vector3 &p) {

	ATTRMAP att = get_attrib_class(POINT);

	att["P"].values.append(p);

	return att["P"].values.size() - 1;
}

int HarryNode::add_vertex(int prim_num, int point_num) {

	ATTRMAP att = get_attrib_class(VERTEX);

	att["P"].values.append(prim_num);
	att["N"].values.append(point_num);

	return 0;
}

int HarryNode::add_prim(int points[]) {

	ATTRMAP att = get_attrib_class(PRIMITIVE);



	return 0;
}
