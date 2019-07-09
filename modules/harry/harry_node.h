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
#include "scene/resources/material.h"

#include "core/ordered_hash_map.h"

#include <iostream>

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
#define ATTRIBCLASSES "Points,Vertices,Primitives,Details"

	//enum PrimType {
	//	POLY,
	//	MESH
	//};
//#define PRIM_TYPES "Polygon,Mesh"

	enum Connectivity {
		QUAD,
		TRI,
		ROW,
		COL,
		ROWCOL,
		POINTS
	};
#define CONNECTIVITIES "Quadrilaterals,Triangles,Rows,Columns,Rows and Columns,Points"

#define MIN_SIZE 0

	struct CountSize {
		int count;
		int size;
	};

	struct DefaultVectorVariant {
		Variant default;
		PoolVector<Variant> values;

		DefaultVectorVariant() {
			values.resize(MIN_SIZE);
		}
	};

	static Color ToColor(Vector3 v);

#define ATTRCOUNTSIZE Map<HarryNode::AttribClass, HarryNode::CountSize>
#define ATTRMAP Map<StringName, HarryNode::DefaultVectorVariant>
#define CACHE Map<HarryNode::AttribClass, Map<StringName, HarryNode::DefaultVectorVariant> >

	struct CacheCount {
		ATTRCOUNTSIZE att_count_size;
		CACHE cache;
		bool was_dirty;
	};

private:
	int refresh_geo_count = 0;
	int create_mesh_count = 0;

	CACHE cache;

	//ATTRMAP points;
	//ATTRMAP vertices;
	//ATTRMAP primitives;
	//ATTRMAP details;

	//bool has_attrib(ATTRMAP &att, const StringName &p_attribute_name);
	//void add_attrib(ATTRMAP &att, const StringName &p_attribute_name, const Variant &p_defvalue);
	//void set_attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum, const Variant &p_value); //string mode = "set"
	//Variant attrib(ATTRMAP &att, const StringName &p_attribute_name, int elemnum);


	//bool batching = false;

	//HashMap<StringName, HarryNode::DefaultVectorVariant>


protected:
	ATTRCOUNTSIZE att_count_size;
	int add_row(const AttribClass &p_attribclass);
	int add_row(const AttribClass &p_attribclass, int sizeMin);

	static Ref<SpatialMaterial> mat_points;
	static Ref<SpatialMaterial> mat_edges;
	static Ref<SpatialMaterial> mat_surface;

	Vector<Ref<Material> > materials;

	StringName node_category;
	StringName node_name;

	// -1: One connector allowing multiple connections
	//  0: Any connector
	//  N: N connectors
	int input_connections = 0;

	static void _bind_methods();
	bool is_dirty = true;

	void clear(const AttribClass &p_attribclass);
	void clear_all();

	//void reset_cache(const AttribClass &p_attribclass);
	//void reset_cache();
	//void start_batch();
	//void commit_batch();

	//int batch_add_row(const AttribClass &p_attribclass);
	//void batch_set_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum, const Variant &p_value, const Variant &p_defvalue);
	//int batch_add_point(Vector3 &p);
	//int batch_add_vertex(int prim_num, int point_num);
	//int batch_add_prim(PoolVector<int> &points, bool closed);

	void create_materials();

public:
	void copy_from_cache(CacheCount cache);
	void dirty();

	StringName get_node_category() const { return node_category; }

	String get_node_name() const;
	void set_node_name(const String &p_name);

	int get_input_connections() const { return input_connections; }

	ATTRMAP &get_attrib_class(const AttribClass &p_attribclass);

	int get_attrib_class_count(const AttribClass &p_attribclass) { return att_count_size[p_attribclass].count; }
	Variant::Type get_attrib_type(const AttribClass &p_attribclass, StringName &p_attr) { return cache[p_attribclass][p_attr].default.get_type(); }

	//bool has_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name);
	//void add_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, const Variant &p_defvalue);
	//Variant attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum);

	void set_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum, const Variant &p_value, const Variant &p_defvalue); //string mode = "set"
	Variant get_attrib(const AttribClass &p_attribclass, const StringName &p_attribute_name, int elemnum); //string mode = "set"

	int add_point(Vector3 &p);
	int add_vertex(int prim_num, int point_num);
	int add_prim(PoolVector<int> &points, bool closed);

	// p_ic_acs = Input Caches, Attribute Count/Size
	virtual void create_geo(Vector<CacheCount> &p_input_caches, bool bypass) {}
	bool refresh_geo(Vector<CacheCount> &p_input_caches, bool bypass);
	CacheCount get_cache(Vector<CacheCount> &p_input_caches, bool bypass);
	virtual Ref<ArrayMesh> create_mesh();
	virtual Vector<Ref<Material>> get_materials();

	PoolVector<Variant> get_overriden_attr(const StringName attr);
};

VARIANT_ENUM_CAST(HarryNode::AttribClass)
VARIANT_ENUM_CAST(HarryNode::Connectivity)
#endif
