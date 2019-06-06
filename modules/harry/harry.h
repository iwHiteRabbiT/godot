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

#ifndef HARRY_H
#define HARRY_H

#include "scene/3d/spatial.h"

/**
 * @Author iWhiteRabbiT
*/

class HarrySubnet;

class HarryNode : public Resource {
	GDCLASS(HarryNode, Resource);

	HarrySubnet *parent;

public:
	StringName GetName() const;
};

class HarryWrangle : public HarryNode {
	GDCLASS(HarryWrangle, HarryNode);
};

class HarrySubnet : public HarryNode {
	GDCLASS(HarrySubnet, HarryNode);

	struct Node {
		Ref<HarryNode> node;
		Vector2 position;
		Vector<StringName> connections;
	};

	Map<StringName, Node> children;

public:
	StringName GetName(const Ref<HarryNode> &p_node) const;
	void AddNode(const StringName &p_name, Ref<HarryNode> p_node);
	Ref<HarryNode> GetNode(const StringName &p_name) const;
	StringName FindNewName(const StringName &p_name) const;
	void GetNodeList(List<StringName> *r_list);
};

class HarryRoot : public HarrySubnet {
	GDCLASS(HarryRoot, HarrySubnet);
};

class Harry : public Spatial {
	GDCLASS(Harry, Spatial);

	Ref<HarryRoot> harry_root;

protected:
	static void _bind_methods();

public:
	void set_harry_root(const Ref<HarryRoot> &p_root);
	Ref<HarryRoot> get_harry_root() const;
};

#endif
