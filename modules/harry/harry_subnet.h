/*************************************************************************/
/*  harry.h                                                              */
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

#ifndef HARRY_SUBNET_H
#define HARRY_SUBNET_H

#include "harry_node.h"

/**
 * @Author iWhiteRabbiT
*/

class HarrySubnet : public HarryNode {
	GDCLASS(HarrySubnet, HarryNode);

public:
	struct Connection {
		int from_index;
		StringName to;
		int to_index;

		bool operator==(const Connection &c) {
			return from_index == c.from_index &&
				   to == c.to &&
				   to_index == c.to_index;
		}
	};

	struct Node {
		//StringName instance_name;
		Ref<HarryNode> node;
		Vector2 position;
		List<Connection> connections;
		bool bypass;
		bool output;

		bool operator==(const Node &n) {

			if (!(node.get_ref_ptr() == n.node.get_ref_ptr()))
				return false;

			if (position != n.position)
				return false;

			if (connections.size() != n.connections.size())
				return false;

			for (int i = 0; i < connections.size(); i++)
				if (!(connections[i] == n.connections[i]))
					return false;

			return true;
		}
	};

private:
	Map<StringName, Node> children;

protected:
	//static void _bind_methods();
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	static void _bind_methods();

public:
	HarrySubnet() { node_name = "Subnet"; }
	void AddNode(StringName instance_name, Ref<HarryNode> p_node);
	Node GetNode(const StringName &p_name) const;
	List<Node> GetNodes(const Ref<HarryNode> &p_node) const;
	StringName GetName(const Node &p_node) const;

	void set_unique_title(const Ref<HarryNode> &p_node);

	void set_node_position(const StringName &p_node, const Vector2 &p_position);
	Vector2 get_node_position(const StringName &p_node) const;

	void set_node_bypass(const StringName &p_node, const bool &enabled);
	bool get_node_bypass(const StringName &p_node) const;

	void set_node_output(const StringName &p_node, const bool &enabled);
	bool get_node_output(const StringName &p_node) const;

	void connect_node(const StringName &p_from_node, int p_from_index, const StringName &p_to_node, int p_to_index);
	bool connection_exists(const StringName &p_from_node, int p_from_index, const StringName &p_to_node, int p_to_index);
	void disconnect_node(const StringName &p_from_node, int p_from_index, const StringName &p_to_node, int p_to_index);

	StringName FindNewName(const StringName &p_name) const;
	void GetNodeList(List<StringName> *r_list);
};

#endif
