/*************************************************************************/
/*  harry_node.cpp                                                       */
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

	return cache[p_attribclass];

	//switch (p_attribclass) {

	//	case POINT:
	//		return points;

	//	case VERTEX:
	//		return vertices;

	//	case PRIMITIVE:
	//		return primitives;

	//	case DETAIL:
	//		return details;

	//	default:
	//		ERR_EXPLAIN("AttribClass unknown");
	//		ERR_FAIL_V(ATTRMAP());
	//}
}

int HarryNode::add_row(const AttribClass &p_attribclass) {

	CountSize &cs = att_count_size[p_attribclass];

	int count = cs.count++;

	if (cs.size == 0) {
		cs.size = 16;

		for (ATTRMAP::Element *a = cache[p_attribclass].front(); a; a = a->next()) {

			HarryNode::DefaultVectorVariant &dvv = a->get();
			dvv.values.resize(cs.size);

			//if (!dvv.default.is_ref())
			//	continue;

			//PoolVector<Variant>::Write w = dvv.values.write();
			//for (int i=0 ; i<cs.size ; i++)
			//	w[i] = dvv.default;
		}
	}

	if (cs.count > cs.size) {

		cs.size *= 2;

		for (ATTRMAP::Element *a = cache[p_attribclass].front(); a; a = a->next()) {

			HarryNode::DefaultVectorVariant &dvv = a->get();
			dvv.values.resize(cs.size);

			//PoolVector<Variant>::Write w = dvv.values.write();
			//for (int i = count; i < cs.size; i++)
			//	w[i] = dvv.default;
		}
	}

	return count;
}

void HarryNode::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_node_name", "node_name"), &HarryNode::set_node_name);
	ClassDB::bind_method(D_METHOD("get_node_name"), &HarryNode::get_node_name);

	//ADD_GROUP("Group", "Group_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "node_name"), "set_node_name", "get_node_name");

	ADD_SIGNAL(MethodInfo("name_changed", PropertyInfo(Variant::OBJECT, "node")));
	ADD_SIGNAL(MethodInfo("dirty", PropertyInfo(Variant::OBJECT, "node")));
	ADD_SIGNAL(MethodInfo("mesh_changed"));

	BIND_CONSTANT(POLY);
	BIND_CONSTANT(MESH);

	BIND_CONSTANT(OPEN_OR_ROW);
	BIND_CONSTANT(CLOSED_OR_TRI);
	BIND_CONSTANT(QUAD);
	BIND_CONSTANT(COL);
	BIND_CONSTANT(ROWCOL);
}

void HarryNode::dirty() {

	//set_edited(true);
	//emit_changed();
	_change_notify();

	Ref<HarryNode> t = this;

	emit_signal("dirty", t);
	emit_signal("mesh_changed");
}

void HarryNode::clear(const AttribClass &p_attribclass) {

	//ATTRMAP &attr = cache[p_attribclass]; //get_attrib_class(p_attribclass);

	//for (ATTRMAP::Element *a = attr.front(); a; a = a->next()) {

	//	a->get().values.resize(0);
	//}

	att_count_size[p_attribclass].count = 0;

	if (att_count_size[p_attribclass].size < MIN_SIZE)
		att_count_size[p_attribclass].size = MIN_SIZE;
}

void HarryNode::clear_all() {

	clear(POINT);
	clear(VERTEX);
	clear(PRIMITIVE);
	clear(DETAIL);
}

//void HarryNode::reset_cache(const AttribClass &p_attribclass) {
//
//	//ATTRMAP &att = get_attrib_class(p_attribclass);
//
//	//Map<StringName, HarryNode::DefaultVectorVariant> &c = cache[p_attribclass];
//
//	//for (ATTRMAP::Element *a = att.front(); a; a = a->next()) {
//
//	//	Map<StringName, PoolVector<Variant> > s = a->get();
//
//	//	for (Map<StringName, PoolVector<Variant> >::Element *b = s.front(); b; b = b->next()) {
//
//	//		b->get().resize(0);
//	//	}
//	//	s.clear();
//	//}
//
//	//cache
//}
//
//void HarryNode::reset_cache() {
//
//	reset_cache(POINT);
//	reset_cache(VERTEX);
//	reset_cache(PRIMITIVE);
//	reset_cache(DETAIL);
//}
//
//void HarryNode::start_batch() {
//
//	//for (CACHE::Element *a = cache.front(); a; a = a->next()) {
//
//	//	Map<StringName, PoolVector<Variant>> s = a->get();
//
//	//	for (Map<StringName, PoolVector<Variant>>::Element *b = s.front(); b; b = b->next()) {
//
//	//			b->get().resize(0);
//	//	}
//	//	s.clear();
//	//}
//	//cache.clear();
//
//	/////////////////////
//	//cache[POINT];
//	//cache[VERTEX];
//	//cache[PRIMITIVE];
//	//cache[DETAIL];
//
//	//for (CACHE::Element *a = cache.front(); a; a = a->next()) {
//
//	//	Map<StringName, PoolVector<Variant> > s = a->get();
//
//	//	for (Map<StringName, PoolVector<Variant> >::Element *b = s.front(); b; b = b->next()) {
//
//	//		b->get().resize(0);
//	//	}
//	//	s.clear();
//	//}
//	//cache.clear();
//
//	batching = true;
//}
//
//void HarryNode::commit_batch() {
//
//	batching = false;
//}

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

//bool HarryNode::has_attrib(const AttribClass &attribclass, const StringName &attribute_name) {
//
//	return has_attrib(get_attrib_class(attribclass), attribute_name);
//}
//bool HarryNode::has_attrib(ATTRMAP &att, const StringName &attribute_name) {
//
//	return att.has(attribute_name);
//}
//
//void HarryNode::add_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, const Variant &p_defvalue) {
//
//	add_attrib(get_attrib_class(p_attribclass), p_attribute_name, p_defvalue);
//}
//void HarryNode::add_attrib(ATTRMAP &att, const StringName &p_attribute_name, const Variant &p_defvalue) {
//
//	DefaultVectorVariant dvv;
//
//	if (att.has(p_attribute_name)) {
//		att[p_attribute_name].default = p_defvalue;
//		return;
//	}
//
//	dvv.default = p_defvalue;
//
//	int size = 0;
//	for (ATTRMAP::Element *a = att.front(); a; a = a->next()) {
//		int s = a->get().values.size();
//		size = size < s ? s : size;
//	}
//	dvv.values.resize(size);
//
//	for (int i = 0; i < size; i++)
//		dvv.values.set(i, dvv.default);
//
//	att[p_attribute_name] = dvv;
//}

void HarryNode::set_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum, const Variant &p_value, const Variant &p_defvalue) {

	HarryNode::DefaultVectorVariant &dvv = cache[p_attribclass][p_attribute_name];

	if (dvv.values.size() < att_count_size[p_attribclass].size)
		dvv.values.resize(att_count_size[p_attribclass].size);

	if (dvv.default.is_zero())
		dvv.default = p_defvalue;

	dvv.values.write()[elemnum] = p_value;
}

//Variant HarryNode::attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum) {
//
//	return attrib(get_attrib_class(p_attribclass), p_attribute_name, elemnum);
//}
//Variant HarryNode::attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum) {
//
//	if (!att.has(p_attribute_name)) {
//		return Variant();
//	}
//
//	PoolVector<Variant> &vals = att[p_attribute_name].values;
//
//	if (vals.size() <= elemnum)
//		return Variant();
//
//	return vals[elemnum];
//}

int HarryNode::add_point(Vector3 &p) {

	int pn = add_row(POINT);

	set_attrib(POINT, "P", pn, p, Vector3());

	return pn;
}

int HarryNode::add_vertex(int prim_num, int point_num) {

	int pn = add_row(VERTEX);

	set_attrib(VERTEX, "PrimNum", pn, prim_num, 0);
	set_attrib(VERTEX, "PointNum", pn, point_num, 0);

	return pn;
}

int HarryNode::add_prim(PoolVector<int> &points, bool closed) {

	int pn = add_row(PRIMITIVE);

	PoolVector<int> vertices;
	vertices.resize(points.size());

	for (int i = 0; i < points.size(); i++) {

		int vn = add_vertex(pn, points[i]);
		vertices.set(i, vn);
	}

	//set_attrib(att, "Points", pn, points);

	Connectivity c = closed ? CLOSED_OR_TRI : OPEN_OR_ROW;

	set_attrib(PRIMITIVE, "Type", pn, POLY, POLY);
	set_attrib(PRIMITIVE, "Connectivity", pn, c, c);
	set_attrib(PRIMITIVE, "Vertices", pn, vertices, Array());

	return pn;
}

Ref<ArrayMesh> HarryNode::create_mesh() {

	ATTRMAP &att_points = cache[POINT]; //get_attrib_class(POINT);
	ATTRMAP &att_verts = cache[VERTEX]; //get_attrib_class(VERTEX);
	ATTRMAP &att_prims = cache[PRIMITIVE]; //get_attrib_class(PRIMITIVE);

	PoolVector<Variant> v_points = att_points["P"].values;
	PoolVector<Variant> v_verts = att_verts["PointNum"].values;
	PoolVector<Variant> v_prims = att_prims["Vertices"].values;

	int pc = att_count_size[POINT].count;
	int vc = att_count_size[VERTEX].count;
	int pmc = att_count_size[PRIMITIVE].count;

	Array arrays;
	arrays.resize(ArrayMesh::ARRAY_MAX);

	// Vertex
	PoolVector<Vector3> points;
	points.resize(pc);

	for (int i = 0; i < pc; i++)
		points.write()[i] = v_points[i];

	arrays[ArrayMesh::ARRAY_VERTEX] = points;

	// Index
	PoolVector<int> indices;
	indices.resize(pmc * 3);
	int n = 0;

	for (int i = 0; i < pmc; i++) {
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
