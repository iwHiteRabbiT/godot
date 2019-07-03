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

Ref<SpatialMaterial> HarryNode::mat_points = NULL;
Ref<SpatialMaterial> HarryNode::mat_edges = NULL;
Ref<SpatialMaterial> HarryNode::mat_surface = NULL;

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

	//BIND_CONSTANT(POLY);
	//BIND_CONSTANT(MESH);

	BIND_CONSTANT(POINT);
	BIND_CONSTANT(VERTEX);
	BIND_CONSTANT(PRIMITIVE);
	BIND_CONSTANT(DETAIL);

	BIND_CONSTANT(QUAD);
	BIND_CONSTANT(TRI);
	BIND_CONSTANT(ROW);
	BIND_CONSTANT(COL);
	BIND_CONSTANT(ROWCOL);
	BIND_CONSTANT(POINTS);
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

void HarryNode::create_materials() {

	if (!mat_points.is_valid()) {
		mat_points.instance();

		mat_points->set_flag(SpatialMaterial::FLAG_UNSHADED, true);
		mat_points->set_flag(SpatialMaterial::FLAG_USE_POINT_SIZE, true);
		mat_points->set_flag(SpatialMaterial::FLAG_ALBEDO_FROM_VERTEX_COLOR, true);
		mat_points->set_point_size(6);
	}

	if (!mat_edges.is_valid()) {
		mat_edges.instance();

		mat_edges->set_flag(SpatialMaterial::FLAG_UNSHADED, true);
		mat_edges->set_flag(SpatialMaterial::FLAG_ALBEDO_FROM_VERTEX_COLOR, true);
		mat_edges->set_line_width(2);
	}

	if (!mat_surface.is_valid()) {
		mat_surface.instance();
		mat_surface->set_flag(SpatialMaterial::FLAG_ALBEDO_FROM_VERTEX_COLOR, true);
		mat_surface->set_diffuse_mode(SpatialMaterial::DIFFUSE_OREN_NAYAR);
		mat_surface->set_roughness(0.5f);
	}
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

	//Connectivity c = closed ? CLOSED_OR_TRI : OPEN_OR_ROW;

	//set_attrib(PRIMITIVE, "Type", pn, POLY, POLY);
	set_attrib(PRIMITIVE, "Closed", pn, closed, closed);
	set_attrib(PRIMITIVE, "Vertices", pn, vertices, Array());

	return pn;
}

Ref<ArrayMesh> HarryNode::create_mesh() {

	create_materials();
	materials.clear();

	// Mesh
	Ref<ArrayMesh> arr_mesh;
	arr_mesh.instance();

	// Cache
	ATTRMAP &att_points = cache[POINT];
	ATTRMAP &att_verts = cache[VERTEX];
	ATTRMAP &att_prims = cache[PRIMITIVE];
	ATTRMAP &att_details = cache[DETAIL];

	int pc = att_count_size[POINT].count;
	int vc = att_count_size[VERTEX].count;
	int pmc = att_count_size[PRIMITIVE].count;

	// Attributes
	PoolVector<Variant> v_p_pos = att_points["P"].values;
	PoolVector<Variant> v_v_pn = att_verts["PointNum"].values;
	PoolVector<Variant> v_pri_vn = att_prims["Vertices"].values;
	PoolVector<Variant> v_pri_closed = att_prims["Closed"].values;

	PoolVector<Variant> &v_pv_cols = get_overriden_attr("Cd");

	Color gizmo_col = Color(0.072f, 0.072f, 0.072f);
	bool use_gizmo_col = false;

	// Draw Polys
	if (true) {

		int pts_count = 0;
		for (int p = 0; p < pmc; p++) {
			if (v_pri_closed[p] == (Variant) false)
				continue;

			PoolVector<int> ind = v_pri_vn[p];

			pts_count += (ind.size() - 2) * 3;
		}

		if (pts_count == 0)
			goto NoPoly;

		PoolVector<Vector3> points;
		PoolVector<Color> colors;
		PoolVector<Vector3> normals;
		points.resize(vc);
		colors.resize(vc);
		normals.resize(vc);
		PoolVector3Array::Write pw = points.write();
		PoolColorArray::Write cw = colors.write();
		PoolVector3Array::Write nw = normals.write();

		for (int i = 0; i < vc; i++) {

			int p = v_v_pn[i];

			pw[i] = v_p_pos[p];
			cw[i] = v_pv_cols[i];
			nw[i] = Vector3();
		}

		use_gizmo_col = true;

		PoolVector<int> indices;
		indices.resize(pts_count);
		PoolIntArray::Write iw = indices.write();

		int n = 0;

		for (int p = 0; p < pmc; p++) {

			if (v_pri_closed[p] == (Variant) false)
				continue;

			PoolVector<int> ind = v_pri_vn[p];

			int s = ind.size();
			for (int i = 0; i < s - 1; i += 2) {

				int va = ind[i];
				int vb = ind[i + 1];
				int vc = ind[(i + 2) % s];

				Vector3 pa = points[va];
				Vector3 pb = points[vb];
				Vector3 pc = points[vc];

				Vector3 nrm = (pc - pa).cross(pb - pa);
				nrm.normalize();
				nw[va] = nrm;
				nw[vb] = nrm;
				nw[vc] = nrm;

				iw[n++] = va;
				iw[n++] = vb;
				iw[n++] = vc;
			}
		}

		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = points;
		arrays[ArrayMesh::ARRAY_COLOR] = colors;
		arrays[ArrayMesh::ARRAY_NORMAL] = normals;
		arrays[ArrayMesh::ARRAY_INDEX] = indices;
		arr_mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
		materials.push_back(mat_surface);
	}
NoPoly:

	// Draw Primitive Edges
	if (true) {

		int pts_count = 0;

		for (int p = 0; p < pmc; p++) {
			PoolVector<int> ind = v_pri_vn[p];
			pts_count += ind.size() * 2;

			if (v_pri_closed[p] == (Variant)false)
				pts_count -= 2;
		}

		if (pts_count == 0)
			goto NoEdges;

		PoolVector<Vector3> points;
		PoolVector<Color> colors;
		points.resize(pts_count);
		colors.resize(pts_count);
		PoolVector3Array::Write pw = points.write();
		PoolColorArray::Write cw = colors.write();

		int n = 0;
		for (int p = 0; p < pmc; p++) {
			PoolVector<int> ind = v_pri_vn[p];

			int s = ind.size();
			int scount = s;

			if (v_pri_closed[p] == (Variant) false)
				scount--;

			for (int i = 0; i < scount; i++) {

				int va = ind[i];
				int vb = ind[(i + 1) % s];

				int a = v_v_pn[va];
				int b = v_v_pn[vb];

				pw[n] = v_p_pos[a];
				cw[n++] = use_gizmo_col ? gizmo_col : v_pv_cols[va];

				pw[n] = v_p_pos[b];
				cw[n++] = use_gizmo_col ? gizmo_col : v_pv_cols[vb];
			}
		}

		use_gizmo_col = true;

		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = points;
		arrays[ArrayMesh::ARRAY_COLOR] = colors;
		arr_mesh->add_surface_from_arrays(Mesh::PRIMITIVE_LINES, arrays);
		materials.push_back(mat_edges);
	}
NoEdges:
	
	// Draw Points
	if (true) {

		if (pc == 0)
			goto NoPoints;

		PoolVector<Vector3> points;
		PoolVector<Color> colors;
		points.resize(pc);
		colors.resize(pc);
		PoolVector3Array::Write pw = points.write();
		PoolColorArray::Write cw = colors.write();
		for (int i = 0; i < pc; i++) {
			pw[i] = v_p_pos[i];
		}

		if (vc == 0)
			for (int i = 0; i < pc; i++)
				cw[i] = use_gizmo_col ? gizmo_col : v_pv_cols[i];
		else
			for (int v = 0; v < vc; v++) {

				int p = v_v_pn[v];
				cw[p] = use_gizmo_col ? gizmo_col : v_pv_cols[v];
			}

		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = points;
		arrays[ArrayMesh::ARRAY_COLOR] = colors;
		arr_mesh->add_surface_from_arrays(Mesh::PRIMITIVE_POINTS, arrays);
		materials.push_back(mat_points);
	}
NoPoints:
		
	// Ref Mesh
	Ref<Mesh> mesh = arr_mesh;

	return arr_mesh;
}

Vector<Ref<Material>> HarryNode::get_materials() {
	return materials;
}

PoolVector<Variant> HarryNode::get_overriden_attr(const StringName attr) {

	// Cache
	ATTRMAP &att_points = cache[POINT];
	ATTRMAP &att_verts = cache[VERTEX];
	ATTRMAP &att_prims = cache[PRIMITIVE];
	ATTRMAP &att_details = cache[DETAIL];

	int pc = att_count_size[POINT].count;
	int vc = att_count_size[VERTEX].count;
	int pmc = att_count_size[PRIMITIVE].count;

	// Attributes
	PoolVector<Variant> v_verts = att_verts["PointNum"].values;
	PoolVector<Variant> v_prims = att_prims["Vertices"].values;

	// Vertex over Point over Prim over Detail

	PoolVector<Variant> v_attrs;
	if (att_verts.has(attr)) {

		v_attrs = att_verts[attr].values;

		return v_attrs;
	}

	if (att_points.has(attr)) {

		if (vc == 0)
			return att_points[attr].values;

		v_attrs.resize(vc);
		PoolVector<Variant>::Write cvw = v_attrs.write();

		for (int v = 0; v < vc; v++)
			cvw[v] = att_points[attr].values[v_verts[v]];

		return v_attrs;
	}

	if (att_prims.has(attr)) {

		v_attrs.resize(vc);
		PoolVector<Variant>::Write cvw = v_attrs.write();

		for (int p = 0; p < pc; p++) {

			PoolVector<int> ind = v_prims[p];

			for (int i = 0; i < ind.size(); i++) {

				int v = v_verts[ind[i]];

				cvw[v] = att_prims[attr].values[p];
			}
		}

		return v_attrs;
	}

	if (att_details.has(attr)) {

		v_attrs.resize(vc);
		PoolVector<Variant>::Write cvw = v_attrs.write();

		for (int v = 0; v < vc; v++)
			cvw[v] = att_details[attr].values[0];

		return v_attrs;
	}

	v_attrs.resize(vc);
	PoolVector<Variant>::Write cvw = v_attrs.write();

	for (int v = 0; v < vc; v++)
		cvw[v] = Color(1, 1, 1);

	return v_attrs;
}
