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

#include "harry.h"

/**
  @Author iWhiteRabbiT
*/

void Harry::refresh_mesh() {
	materials
	set_mesh(harry_root->create_mesh());
}

void Harry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_harry_root", "root"), &Harry::set_harry_root);
	ClassDB::bind_method(D_METHOD("get_harry_root"), &Harry::get_harry_root);
	ClassDB::bind_method("refresh_mesh", &Harry::refresh_mesh);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "harry_root", PROPERTY_HINT_RESOURCE_TYPE, "HarryRoot"), "set_harry_root", "get_harry_root");
}

void Harry::set_harry_root(const Ref<HarryRoot> &p_root) {

	if (harry_root.is_valid()) {
		harry_root->disconnect("mesh_changed", this, "refresh_mesh");
	}

	harry_root = p_root;

	if (harry_root.is_valid()) {
		harry_root->connect("mesh_changed", this, "refresh_mesh");
	}

	//properties_dirty = true;

	update_configuration_warning();

	refresh_mesh();
}

Ref<HarryRoot> Harry::get_harry_root() const {
	return harry_root;
}
