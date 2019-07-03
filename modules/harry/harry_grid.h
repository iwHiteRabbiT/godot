/*************************************************************************/
/*  harry_grid.h                                                         */
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

#ifndef HARRY_GRID_H
#define HARRY_GRID_H

#include "harry_node.h"

/**
  @Author iWhiteRabbiT
*/
class HarryGrid : public HarryNode {
	GDCLASS(HarryGrid, HarryNode);

	Vector2 grid_size = Vector2(1, 1);
	int num_column = 2;
	int num_row = 2;

	//PrimType prim_type = POLY;
	Connectivity connectivity = QUAD;

protected:
	static void _bind_methods();

	//void set_primitive_type(PrimType p_type) {
	//	prim_type = p_type;
	//	create_geo();
	//}
	//PrimType get_primitive_type() { return prim_type; }

	void set_primitive_connectivity(Connectivity p_connectivity) {
		connectivity = p_connectivity;
		create_geo();
	}
	Connectivity get_primitive_connectivity() { return connectivity; }

	void create_points();
	void create_prims_poly();
	//void create_prims_mesh();
	void create_prims_poly_rows();
	void create_prims_poly_columns();
	void create_prims_poly_rows_columns();
	void create_prims_poly_tris();
	void create_prims_poly_quads();
	//void create_prims_mesh_rows();
	//void create_prims_mesh_columns();
	//void create_prims_mesh_rows_columns();
	//void create_prims_mesh_tris();
	//void create_prims_mesh_quads();

public:
	HarryGrid() {
		node_category = "Primitive";
		node_name = "Grid";
		//create_geo();
	}

	Vector2 get_grid_size() const;
	void set_grid_size(const Vector2 &p_size);

	int get_num_column() const;
	void set_num_column(const int &p_num_column);

	int get_num_row() const;
	void set_num_row(const int &p_num_row);

	void create_geo();
};

#endif
