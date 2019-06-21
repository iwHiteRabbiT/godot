/*************************************************************************/
/*  harry_grid.cpp                                                       */
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

#include "harry_grid.h"

/**
  @Author iWhiteRabbiT
*/

void HarryGrid::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_grid_size", "grid_size"), &HarryGrid::set_grid_size);
	ClassDB::bind_method(D_METHOD("get_grid_size"), &HarryGrid::get_grid_size);
	ClassDB::bind_method(D_METHOD("set_num_column", "num_column"), &HarryGrid::set_num_column);
	ClassDB::bind_method(D_METHOD("get_num_column"), &HarryGrid::get_num_column);
	ClassDB::bind_method(D_METHOD("set_num_row", "num_row"), &HarryGrid::set_num_row);
	ClassDB::bind_method(D_METHOD("get_num_row"), &HarryGrid::get_num_row);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size"), "set_grid_size", "get_grid_size");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_column"), "set_num_column", "get_num_column");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_row"), "set_num_row", "get_num_row");
}

Vector2 HarryGrid::get_grid_size() const {

	return grid_size;
}

void HarryGrid::set_grid_size(const Vector2 &p_size) {

	grid_size = p_size;
	create_geo();
	dirty();
}

int HarryGrid::get_num_column() const {

	return num_column;
}

void HarryGrid::set_num_column(const int &p_num_column) {

	num_column = p_num_column;
	create_geo();
	dirty();
}

int HarryGrid::get_num_row() const {

	return num_row;
}

void HarryGrid::set_num_row(const int &p_num_row) {

	num_row = p_num_row;
	create_geo();
	dirty();
}

void HarryGrid::create_geo() {

	clear_all();

	start_batch();

	Vector3 g = Vector3(grid_size.x, 0, grid_size.y);
	Vector3 s = g / Vector3(num_column - 1, 1, num_row - 1);
	Vector3 o = -0.5f * g;

	for (int j = 0; j < num_row; j++) {
		for (int i = 0; i < num_column; i++) {

			add_point(o + s * Vector3(i, 0, j));
		}
	}

	PoolVector<int> tri;
	tri.resize(3);
	for (int j = 0; j < num_row - 1; j++) {
		for (int i = 0; i < num_column - 1; i++) {

			int p0 = i + j * num_column;
			int p1 = p0 + 1;
			int p2 = (i + 1) + (j + 1) * num_column;
			int p3 = p2 - 1;

			tri.set(0, p0);
			tri.set(1, p1);
			tri.set(2, p2);
			add_prim(tri);

			tri.set(0, p0);
			tri.set(1, p2);
			tri.set(2, p3);
			add_prim(tri);
		}
	}

	commit_batch();
}
