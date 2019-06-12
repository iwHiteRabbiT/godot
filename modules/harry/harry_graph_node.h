/*************************************************************************/
/*  harry_node.h                                                         */
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

#ifndef HARRY_GRAPHNODE_H
#define HARRY_GRAPHNODE_H

#include "harry_node.h"
#include "harry_subnet.h"
#include "scene/gui/graph_node.h"
#include "scene/gui/label.h"


/**
 * @Author iWhiteRabbiT
*/

class HarryGraphNode : public GraphNode {
	GDCLASS(HarryGraphNode, GraphNode);

	Ref<HarryNode> node;
	Ref<HarrySubnet> subnet;

//protected:
	//static void _bind_methods();

public:
	HarryGraphNode() {};
	virtual void Set(const StringName &p_name, const Ref<HarryNode> &p_node, const Vector2 &p_offset, const Ref<HarrySubnet> &p_subnet);
	//void set_unique_title(const StringName &p_name);
};

#endif
