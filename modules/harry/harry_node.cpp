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
 @Author iWhiteRabbiT
*/

ATTRMAP &HarryNode::get_attrib_class(const AttribClass &p_attribclass) {

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

int HarryNode::add_row(ATTRMAP &att) {

	for (ATTRMAP::Element *a = att.front(); a; a = a->next()) {

		DefaultVectorVariant dvv = a->get();

		dvv.values.push_back(dvv.default);
		att[a->key()] = dvv;
	}

	return att.front()->get().values.size() - 1;
}

void HarryNode::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_node_name", "node_name"), &HarryNode::set_node_name);
	ClassDB::bind_method(D_METHOD("get_node_name"), &HarryNode::get_node_name);

	//ADD_GROUP("Group", "Group_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "node_name"), "set_node_name", "get_node_name");

	ADD_SIGNAL(MethodInfo("name_changed", PropertyInfo(Variant::OBJECT, "node")));
	ADD_SIGNAL(MethodInfo("dirty", PropertyInfo(Variant::OBJECT, "node")));
	ADD_SIGNAL(MethodInfo("mesh_changed"));
}

void HarryNode::dirty() {

	//set_edited(true);
	//emit_changed();
	_change_notify();

	Ref<HarryNode> t = this;

	emit_signal("dirty", t);
	emit_signal("mesh_changed");
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

	return has_attrib(get_attrib_class(attribclass), attribute_name);
}
bool HarryNode::has_attrib(ATTRMAP &att, const StringName &attribute_name) {

	return att.has(attribute_name);
}

void HarryNode::add_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, const Variant &p_defvalue) {

	add_attrib(get_attrib_class(p_attribclass), p_attribute_name, p_defvalue);
}
void HarryNode::add_attrib(ATTRMAP &att, const StringName &p_attribute_name, const Variant &p_defvalue) {

	DefaultVectorVariant dvv;

	if (att.has(p_attribute_name)) {
		att[p_attribute_name].default = p_defvalue;
		return;
	}

	dvv.default = p_defvalue;

	int size = 0;
	for (ATTRMAP::Element *a = att.front(); a; a = a->next()) {
		int s = a->get().values.size();
		size = size < s ? s : size;
	}
	dvv.values.resize(size);

	for (int i = 0; i < size; i++)
		dvv.values.set(i, dvv.default);

	att[p_attribute_name] = dvv;
}

void HarryNode::set_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum, const Variant &p_value) {

	set_attrib(get_attrib_class(p_attribclass), p_attribute_name, elemnum, p_value);
}
void HarryNode::set_attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum, const Variant &p_value) {

	if (!att.has(p_attribute_name))
		add_attrib(att, p_attribute_name, Variant());

	PoolVector<Variant> &vals = att[p_attribute_name].values;

	if (vals.size() <= elemnum)
		return;

	vals.write()[elemnum] = p_value;
}

Variant HarryNode::attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum) {

	return attrib(get_attrib_class(p_attribclass), p_attribute_name, elemnum);
}
Variant HarryNode::attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum) {

	if (!att.has(p_attribute_name)) {
		return Variant();
	}

	PoolVector<Variant> &vals = att[p_attribute_name].values;

	if (vals.size() <= elemnum)
		return Variant();

	return vals[elemnum];
}

int HarryNode::add_point(Vector3 &p) {

	ATTRMAP &att = get_attrib_class(POINT);

	if (!has_attrib(att, "P"))
		add_attrib(att, "P", Vector3());

	int pn = add_row(att);

	set_attrib(att, "P", pn, p);

	return pn;
}

int HarryNode::add_vertex(int prim_num, int point_num) {

	ATTRMAP &att = get_attrib_class(VERTEX);

	if (!has_attrib(att, "PrimNum"))
		add_attrib(att, "PrimNum", 0);

	if (!has_attrib(att, "PointNum"))
		add_attrib(att, "PointNum", 0);

	int pn = add_row(att);

	set_attrib(att, "PrimNum", pn, prim_num);
	set_attrib(att, "PointNum", pn, point_num);

	return pn;
}

int HarryNode::add_prim(PoolVector<int> &points) {

	ATTRMAP &att = get_attrib_class(PRIMITIVE);

	//if (!has_attrib(att, "Points"))
	//	add_attrib(att, "Points", PoolVector<int>());

	if (!has_attrib(att, "Vertices"))
		add_attrib(att, "Vertices", PoolVector<int>());

	int pn = add_row(att);

	PoolVector<int> vertices;
	vertices.resize(points.size());

	for (int i = 0; i < points.size(); i++) {

		int vn = add_vertex(pn, points[i]);
		vertices.set(i, vn);
	}

	//set_attrib(att, "Points", pn, points);
	set_attrib(att, "Vertices", pn, vertices);

	return 0;
}

Ref<ArrayMesh> HarryNode::create_mesh() {

	ATTRMAP &att_points = get_attrib_class(POINT);
	ATTRMAP &att_verts = get_attrib_class(VERTEX);
	ATTRMAP &att_prims = get_attrib_class(PRIMITIVE);

	PoolVector<Variant> v_points = att_points["P"].values;
	PoolVector<Variant> v_verts = att_verts["PointNum"].values;
	PoolVector<Variant> v_prims = att_prims["Vertices"].values;

	Array arrays;
	arrays.resize(ArrayMesh::ARRAY_MAX);

	// Vertex
	PoolVector<Vector3> points;
	points.resize(v_points.size());

	for (int i = 0; i < v_points.size(); i++)
		points.write()[i] = v_points[i];

	arrays[ArrayMesh::ARRAY_VERTEX] = points;

	// Index
	PoolVector<int> indices;
	indices.resize(v_prims.size() * 3);
	int n = 0;

	for (int i = 0; i < v_prims.size(); i++) {
		PoolVector<int> ind = v_prims[i];
		indices.write()[n++] = v_verts[ind[0]];
		indices.write()[n++] = v_verts[ind[1]];
		indices.write()[n++] = v_verts[ind[2]];
	}

	arrays[ArrayMesh::ARRAY_INDEX] = indices;

	// Mesh
	Ref<ArrayMesh> arr_mesh;
	arr_mesh.instance();
	arr_mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

	Ref<Mesh> mesh = arr_mesh;

	return arr_mesh;
}
