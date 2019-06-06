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
 * @Author iWhiteRabbiT
*/

StringName HarrySubnet::GetName(const Ref<HarryNode> &p_node) const {
	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		if (E->get().node == p_node) {
			return E->key();
		}
	}

	ERR_FAIL_V(StringName());
}

void HarrySubnet::AddNode(const StringName &p_name, Ref<HarryNode> p_node) {
	ERR_FAIL_COND(children.has(p_name));

	Node n;
	n.node = p_node;
	children[p_name] = n;

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

StringName HarryNode::GetName() const {
	return parent->GetName(Ref<HarryNode>(this));
}

void Harry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_harry_root", "root"), &Harry::set_harry_root);
	ClassDB::bind_method(D_METHOD("get_harry_root"), &Harry::get_harry_root);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "harry_root", PROPERTY_HINT_RESOURCE_TYPE, "HarryRoot"), "set_harry_root", "get_harry_root");
}

void Harry::set_harry_root(const Ref<HarryRoot> &p_root) {

	if (harry_root.is_valid()) {
		//harry_root->disconnect("tree_changed", this, "_tree_changed");
	}

	harry_root = p_root;

	if (harry_root.is_valid()) {
		//harry_root->connect("tree_changed", this, "_tree_changed");
	}

	//properties_dirty = true;

	update_configuration_warning();
}

Ref<HarryRoot> Harry::get_harry_root() const {
	return harry_root;
}
