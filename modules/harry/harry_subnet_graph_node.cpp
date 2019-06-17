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

#include "harry_subnet_graph_node.h"

/**
 * @Author iWhiteRabbiT
*/

void HarrySubnetGraphNode::_dive_in() {

	emit_signal("dive_in", get_title());
}

void HarrySubnetGraphNode::_bind_methods() {

	ClassDB::bind_method("_dive_in", &HarrySubnetGraphNode::_dive_in);

	ADD_SIGNAL(MethodInfo("dive_in", PropertyInfo(Variant::STRING, "node_name")));
}

void HarrySubnetGraphNode::Set(Ref<HarrySubnet> &p_subnet, const StringName &p_name, const Vector2 &p_offset, bool bypass, bool output, Ref<ButtonGroup> &output_btn_grp) {

	HarryGraphNode::Set(p_subnet, p_name, p_offset, bypass, output, output_btn_grp);

	Button *btn_dive_in = memnew(Button);
	add_child(btn_dive_in);
	btn_dive_in->set_text(TTR("Dive In"));
	btn_dive_in->connect("pressed", this, "_dive_in", varray(), CONNECT_DEFERRED);
}

