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

#include "harry_subnet.h"

/**
 * @Author iWhiteRabbiT
*/

bool HarrySubnet::_set(const StringName &p_name, const Variant &p_value) {
	return false;
}

bool HarrySubnet::_get(const StringName &p_name, Variant &r_ret) const {
	return false;
}

void HarrySubnet::_get_property_list(List<PropertyInfo> *p_list) const {
}

StringName HarrySubnet::GetName(const Ref<HarryNode> &p_node) const {
	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		if (E->get().node == p_node) {
			return E->key();
		}
	}

	ERR_FAIL_V(StringName());
}

void HarrySubnet::AddNode(Ref<HarryNode> p_node) {

	StringName name = p_node->GetName();

	ERR_FAIL_COND(children.has(name));

	Node n;
	n.node = p_node;
	children[name] = n;

	emit_changed();
	//emit_signal("tree_changed");

	//p_node->connect("tree_changed", this, "_tree_changed", varray(), CONNECT_REFERENCE_COUNTED);
	//p_node->connect("changed", this, "_node_changed", varray(p_name), CONNECT_REFERENCE_COUNTED);
}

Ref<HarryNode> HarrySubnet::GetNode(const StringName &p_name) const {
	ERR_FAIL_COND_V(!children.has(p_name), Ref<HarryNode>());

	return children[p_name].node;
}

StringName HarrySubnet::FindNewName(const StringName &p_name) const {

	StringName name = p_name;

	int i = 0;
	while (children.has(name)) {
		i++;

		Array vals;
		vals.push_back(p_name);
		vals.push_back(i);

		bool e;
		name = String("%s %d").sprintf(vals, &e);
	}

	return StringName(name);
}

void HarrySubnet::GetNodeList(List<StringName> *r_list) {
	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		r_list->push_back(E->key());
	}
}
