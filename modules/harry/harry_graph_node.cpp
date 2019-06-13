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

#include "harry_graph_node.h"

/**
 * @Author iWhiteRabbiT
*/

void HarryGraphNode::Set(const StringName &p_name, const Ref<HarryNode> &p_node, const Vector2 &p_offset, const Ref<HarrySubnet> &p_subnet) {

	node = p_node;
	subnet = p_subnet;

	set_name(p_name);

	set_title(p_name);
	set_size(Size2(150, 85));
	set_offset(p_offset);

	GridContainer *gc = memnew(GridContainer);
	add_child(gc);
	gc->set_columns(3);
	gc->set_anchor(MARGIN_LEFT, 0);
	gc->set_anchor(MARGIN_RIGHT, 1);
	gc->set_anchor(MARGIN_TOP, 0);
	gc->set_anchor(MARGIN_BOTTOM, 0);
	gc->set_margin(MARGIN_LEFT, 0);
	gc->set_margin(MARGIN_RIGHT, 0);
	gc->set_margin(MARGIN_TOP, 0);
	gc->set_margin(MARGIN_BOTTOM, 0);

	Ref<StyleBoxFlat> sbi;
	sbi.instance();
	sbi->set_bg_color(Color(1, 1, 0));

	CheckButton *cb = memnew(CheckButton);
	gc->add_child(cb);
	cb->set_pressed(true);
	cb->add_style_override("normal", sbi);

	Panel *p = memnew(Panel);
	gc->add_child(p);
	p->set_h_size_flags(SIZE_FILL);
	p->set_v_size_flags(0);

	cb = memnew(CheckButton);
	gc->add_child(cb);
	cb->set_pressed(true);
	//cb->connect("toggled", this, "_")

	for (int i = 0; i < 1; i++) {
		Label *in_name = memnew(Label);
		add_child(in_name);
		in_name->set_text("");

		set_slot(i,
				true, 0, Color(1, 1, 1, 1),
				true, 0, Color(0.7f, 0.7f, 0.9f, 1));
	}
}
