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

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String node_name = name.get_slicec('/', 1);
		String what = name.get_slicec('/', 2);

		if (what == "node") {
			Ref<HarryNode> anode = p_value;
			if (anode.is_valid()) {
				AddNode(node_name, p_value);
			}
			return true;
		}

		if (what == "position") {

			if (children.has(node_name)) {
				children[node_name].position = p_value;
			}
			return true;
		}
	}
	//else if (name == "node_connections") {

	//	Array conns = p_value;
	//	ERR_FAIL_COND_V(conns.size() % 3 != 0, false);

	//	for (int i = 0; i < conns.size(); i += 3) {
	//		connect_node(conns[i], conns[i + 1], conns[i + 2]);
	//	}
	//	return true;
	//}

	return false;
}

bool HarrySubnet::_get(const StringName &p_name, Variant &r_ret) const {

	String name = p_name;
	if (name.begins_with("nodes/")) {
		String node_name = name.get_slicec('/', 1);
		String what = name.get_slicec('/', 2);

		if (what == "node") {
			if (children.has(node_name)) {
				r_ret = children[node_name].node;
				return true;
			}
		}

		if (what == "position") {

			if (children.has(node_name)) {
				r_ret = children[node_name].position;
				return true;
			}
		}
	}
	//else if (name == "node_connections") {
	//	List<NodeConnection> nc;
	//	get_node_connections(&nc);
	//	Array conns;
	//	conns.resize(nc.size() * 3);

	//	int idx = 0;
	//	for (List<NodeConnection>::Element *E = nc.front(); E; E = E->next()) {
	//		conns[idx * 3 + 0] = E->get().input_node;
	//		conns[idx * 3 + 1] = E->get().input_index;
	//		conns[idx * 3 + 2] = E->get().output_node;
	//		idx++;
	//	}

	//	r_ret = conns;
	//	return true;
	//}

	return false;
}

void HarrySubnet::_get_property_list(List<PropertyInfo> *p_list) const {

	List<StringName> names;
	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		names.push_back(E->key());
	}
	names.sort_custom<StringName::AlphCompare>();

	for (List<StringName>::Element *E = names.front(); E; E = E->next()) {
		String name = E->get();
		//if (name != "output") {
		//p_list->push_back(PropertyInfo(Variant::STRING, "nodes/" + name + "/name", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
		p_list->push_back(PropertyInfo(Variant::OBJECT, "nodes/" + name + "/node", PROPERTY_HINT_RESOURCE_TYPE, "HarryNode", PROPERTY_USAGE_NOEDITOR));
		//}
		p_list->push_back(PropertyInfo(Variant::VECTOR2, "nodes/" + name + "/position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
		//p_list->push_back(PropertyInfo(Variant::ARRAY, "node_connections", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
	}

}

StringName HarrySubnet::GetName(const Ref<HarryNode> &p_node) const {
	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		if (E->get().node == p_node) {
			return E->key();
		}
	}

	ERR_FAIL_V(StringName());
}

void HarrySubnet::AddNode(StringName instance_name, Ref<HarryNode> p_node) {

	ERR_FAIL_COND(children.has(instance_name));

	Node n;
	//n.instance_name = instance_name;
	n.node = p_node;
	children[instance_name] = n;

	emit_changed();
	//emit_signal("tree_changed");

	//p_node->connect("tree_changed", this, "_tree_changed", varray(), CONNECT_REFERENCE_COUNTED);
	//p_node->connect("changed", this, "_node_changed", varray(p_name), CONNECT_REFERENCE_COUNTED);
}

HarrySubnet::Node HarrySubnet::GetNode(const StringName &p_name) const {
	//ERR_FAIL_COND_V(!children.has(p_name), Node());

	if (!children.has(p_name))
		return Node();

	return children[p_name];
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
