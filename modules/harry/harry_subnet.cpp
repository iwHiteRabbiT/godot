/*************************************************************************/
/*  harry_subnet.cpp                                                     */
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
  @Author iWhiteRabbiT
*/

void HarrySubnet::refresh_mesh() {
	emit_signal("mesh_changed");
}

bool HarrySubnet::_set(const StringName &p_name, const Variant &p_value) {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String node_name = name.get_slicec('/', 1);
		String what = name.get_slicec('/', 2);

		if (what == "node") {
			Ref<HarryNode> anode = p_value;
			if (anode.is_valid()) {
				AddNode(node_name, anode);
			}
			return true;
		}

		if (what == "position") {

			if (children.has(node_name)) {
				children[node_name].position = p_value;
			}
			return true;
		}

		if (what == "bypass") {

			if (children.has(node_name)) {
				children[node_name].bypass = p_value;
			}
			return true;
		}

		if (what == "output") {

			if (children.has(node_name)) {
				children[node_name].output = p_value;
			}
			return true;
		}

		if (what == "connections") {

			if (children.has(node_name)) {
				Array conns = p_value;
				ERR_FAIL_COND_V(conns.size() % 3 != 0, false);

				for (int i = 0; i < conns.size(); i += 3) {
					connect_node(conns[i + 1], conns[i + 2], node_name, conns[i]);
				}
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

		if (what == "bypass") {

			if (children.has(node_name)) {
				r_ret = children[node_name].bypass;
				return true;
			}
		}

		if (what == "output") {

			if (children.has(node_name)) {
				r_ret = children[node_name].output;
				return true;
			}
		}

		if (what == "connections") {

			if (children.has(node_name)) {

				List<Connection> cs = children[node_name].connections;

				Array conns;
				conns.resize(cs.size() * 3);

				int idx = 0;
				for (List<Connection>::Element *E = cs.front(); E; E = E->next()) {
					Connection c = E->get();
					conns[idx * 3 + 0] = c.input_index;
					conns[idx * 3 + 1] = c.output;
					conns[idx * 3 + 2] = c.output_index;
					idx++;
				}

				r_ret = conns;
				return true;
			}
		}
	}

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
		p_list->push_back(PropertyInfo(Variant::OBJECT, "nodes/" + name + "/node", PROPERTY_HINT_RESOURCE_TYPE, "HarryNode", PROPERTY_USAGE_NOEDITOR));
		p_list->push_back(PropertyInfo(Variant::VECTOR2, "nodes/" + name + "/position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
		//p_list->push_back(PropertyInfo(Variant::ARRAY, "nodes/" + name + "/connections", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
		p_list->push_back(PropertyInfo(Variant::BOOL, "nodes/" + name + "/bypass", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
		p_list->push_back(PropertyInfo(Variant::BOOL, "nodes/" + name + "/output", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
	}

	for (List<StringName>::Element *E = names.front(); E; E = E->next()) {
		String name = E->get();
		//p_list->push_back(PropertyInfo(Variant::OBJECT, "nodes/" + name + "/node", PROPERTY_HINT_RESOURCE_TYPE, "HarryNode", PROPERTY_USAGE_NOEDITOR));
		//p_list->push_back(PropertyInfo(Variant::VECTOR2, "nodes/" + name + "/position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
		p_list->push_back(PropertyInfo(Variant::ARRAY, "nodes/" + name + "/connections", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
	}
}

void HarrySubnet::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_node_position", "name", "position"), &HarrySubnet::set_node_position);
	ClassDB::bind_method(D_METHOD("get_node_position", "name"), &HarrySubnet::get_node_position);
	ClassDB::bind_method(D_METHOD("connect_node", "from", "from_i", "to", "to_i"), &HarrySubnet::connect_node);
	ClassDB::bind_method(D_METHOD("disconnect_node", "from", "from_i", "to", "to_i"), &HarrySubnet::disconnect_node);
	ClassDB::bind_method(D_METHOD("set_unique_title", "node"), &HarrySubnet::set_unique_title);
	ClassDB::bind_method("refresh_mesh", &HarrySubnet::refresh_mesh);

	ADD_SIGNAL(MethodInfo("node_instance_name_changed", PropertyInfo(Variant::STRING, "old_name"), PropertyInfo(Variant::STRING, "new_name")));
}

void HarrySubnet::AddNode(StringName instance_name, Ref<HarryNode> p_node) {

	ERR_FAIL_COND(children.has(instance_name));

	Node n;
	//n.instance_name = instance_name;
	n.node = p_node;
	if (!n.node->is_connected("name_changed", this, "set_unique_title"))
		n.node->connect("name_changed", this, "set_unique_title");

	if (!n.node->is_connected("mesh_changed", this, "refresh_mesh"))
		n.node->connect("mesh_changed", this, "refresh_mesh");

	if (children[instance_name] == n)
		return;

	children[instance_name] = n;

	dirty();
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

List<HarrySubnet::Node> HarrySubnet::GetNodes(const Ref<HarryNode> &p_node) const {

	List<Node> nodes;

	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		if (E->get().node == p_node) {
			nodes.push_back(E->get());
		}
	}

	return nodes;
}

StringName HarrySubnet::GetName(const Node &p_node) const {
	for (Map<StringName, Node>::Element *E = children.front(); E; E = E->next()) {
		if (E->get() == p_node) {
			return E->key();
		}
	}

	ERR_FAIL_V(StringName());
}

void HarrySubnet::set_unique_title(const Ref<HarryNode> &p_node) {

	List<Node> ns = GetNodes(p_node);

	bool anychange = false;

	for (List<Node>::Element *E = ns.front(); E; E = E->next()) {
		Node n = E->get();
		String old_instance_name = GetName(n);
		String new_instance_name = FindNewName(p_node->get_node_name());

		children.erase(old_instance_name);
		//Node n = children[old_instance_name];

		if (children[new_instance_name] == n)
			continue;

		children[new_instance_name] = n;
		anychange = true;

		for (Map<StringName, Node>::Element *E1 = children.front(); E1; E1 = E1->next()) {

			Node n1 = E1->get();

			for (int i = 0; i < n1.connections.size(); i++) {
				if (n1.connections[i].output == old_instance_name)
					n1.connections[i].output = new_instance_name;
			}

			children[E1->key()] = n1;
		}

		emit_signal("node_instance_name_changed", old_instance_name, new_instance_name);
	}

	if (anychange)
		dirty();
}

void HarrySubnet::set_node_position(const StringName &p_node, const Vector2 &p_position) {
	ERR_FAIL_COND(!children.has(p_node));

	if (children[p_node].position == p_position)
		return;

	if (children[p_node].position == p_position)
		return;

	children[p_node].position = p_position;
	dirty();
}

Vector2 HarrySubnet::get_node_position(const StringName &p_node) const {
	ERR_FAIL_COND_V(!children.has(p_node), Vector2());
	return children[p_node].position;
}

void HarrySubnet::set_node_bypass(const StringName &p_node, const bool &enabled) {
	ERR_FAIL_COND(!children.has(p_node));

	if (children[p_node].bypass == enabled)
		return;

	children[p_node].bypass = enabled;
	dirty();
}

bool HarrySubnet::get_node_bypass(const StringName &p_node) const {
	ERR_FAIL_COND_V(!children.has(p_node), false);
	return children[p_node].bypass;
}

void HarrySubnet::set_node_output(const StringName &p_node, const bool &enabled) {
	ERR_FAIL_COND(!children.has(p_node));

	if (children[p_node].output == enabled)
		return;

	children[p_node].output = enabled;
	dirty();
}

bool HarrySubnet::get_node_output(const StringName &p_node) const {
	ERR_FAIL_COND_V(!children.has(p_node), false);
	return children[p_node].output;
}

void HarrySubnet::connect_node(const StringName &p_output_node, int p_output_index, const StringName &p_input_node, int p_input_index) {

	ERR_FAIL_COND(!children.has(p_output_node));
	ERR_FAIL_COND(!children.has(p_input_node));
	//ERR_FAIL_COND(p_output_node == SceneStringNames::get_singleton()->output);
	ERR_FAIL_COND(p_output_node == p_input_node);

	Connection connection;
	connection.input_index = p_input_index;
	connection.output = p_output_node;
	connection.output_index = p_output_index;

	children[p_input_node].connections.push_back(connection);

	dirty();
}

bool HarrySubnet::connection_exists(const StringName &p_output_node, int p_output_index, const StringName &p_input_node, int p_input_index) {
	ERR_FAIL_COND_V(!children.has(p_input_node), false);

	Node n = children[p_input_node];

	for (int i = 0; i < n.connections.size(); i++) {
		Connection c = n.connections[i];
		if (c.input_index == p_input_index &&
				c.output == p_output_node &&
				c.output_index == p_output_index) {
			return true;
		}
	}

	return false;
}

void HarrySubnet::disconnect_node(const StringName &p_output_node, int p_output_index, const StringName &p_input_node, int p_input_index) {

	ERR_FAIL_COND(!children.has(p_input_node));

	Node &n = children[p_input_node];

	for (int i = 0; i < n.connections.size(); i++) {
		Connection c = n.connections[i];
		if (c.input_index == p_input_index &&
				c.output == p_output_node &&
				c.output_index == p_output_index) {
			n.connections.erase(c);
		}
	}

	dirty();
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

Ref<ArrayMesh> HarrySubnet::create_mesh(Vector<CacheCount> &p_input_caches) {

	for (Map<StringName, Node>::Element *e = children.front(); e; e = e->next()) {
		Node n = e->get();

		if (n.output && !n.bypass) {
			Vector<CacheCount> &caches = get_caches(n);
			return n.node->create_mesh(caches);
		}
	}

	return Ref<ArrayMesh>();
}

Vector<HarryNode::CacheCount> HarrySubnet::get_caches(Node &p_node) {

	Vector<CacheCount> caches;
	caches.resize(p_node.connections.size());
	// VectorWriteProxy<CacheCount> cw = caches.write;

	for (List<Connection>::Element *c = p_node.connections.front(); c; c = c->next()) {
		Connection co = c->get();

		Node &no = GetNode(co.output);

		Vector<CacheCount> &subcaches = get_caches(no);
		CacheCount cc = no.node->get_cache(subcaches);
		caches.set(co.input_index, cc);
		// cw[co.input_index] = cc;
	}

	return caches;
}

Vector<Ref<Material> > HarrySubnet::get_materials() {

	for (Map<StringName, Node>::Element *e = children.front(); e; e = e->next()) {
		Node n = e->get();

		if (n.output && !n.bypass)
			return n.node->get_materials();
	}

	return Vector<Ref<Material> >();
}
