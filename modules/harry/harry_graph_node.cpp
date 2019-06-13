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
#include "scene/resources/default_theme/default_theme.h"

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
	//gc->set_anchor(MARGIN_LEFT, 0);
	//gc->set_anchor(MARGIN_RIGHT, 1);
	//gc->set_anchor(MARGIN_TOP, 0);
	//gc->set_anchor(MARGIN_BOTTOM, 0);
	//gc->set_margin(MARGIN_LEFT, 0);
	//gc->set_margin(MARGIN_RIGHT, 0);
	//gc->set_margin(MARGIN_TOP, 0);
	//gc->set_margin(MARGIN_BOTTOM, 0);

	Ref<StyleBoxFlat> sbi_white;
	sbi_white.instance();
	sbi_white->set_bg_color(Color(1, 1, 1));

	Ref<StyleBoxFlat> sbi_blue;
	sbi_blue.instance();
	sbi_blue->set_bg_color(Color(14 / 255.0f, 77 / 255.0f, 146 / 255.0f));

	Ref<StyleBoxFlat> sbi_blueless;
	sbi_blueless.instance();
	sbi_blueless->set_bg_color(Color(14 / 255.0f, 77 / 255.0f, 146 / 255.0f, 40/255.0f));

	Ref<StyleBoxFlat> sbi_yellow;
	sbi_yellow.instance();
	sbi_yellow->set_bg_color(Color(91 / 255.0f, 77 / 255.0f, 14 / 255.0f));

	Ref<StyleBoxFlat> sbi_yellowless;
	sbi_yellowless.instance();
	sbi_yellowless->set_bg_color(Color(91 / 255.0f, 77 / 255.0f, 14 / 255.0f, 40/255.0f));

	Ref<Texture> tex_bypass = get_icon("bypass", "Harry");
	Ref<Texture> tex_output = get_icon("output", "Harry");

	CheckBox *cb = memnew(CheckBox);
	gc->add_child(cb);
	cb->set_pressed(true);
	cb->add_style_override("hover", sbi_white);
	cb->add_style_override("hover_pressed", sbi_white);
	cb->add_style_override("pressed", sbi_yellow);
	cb->add_style_override("normal", sbi_yellowless);
	cb->add_icon_override("checked", tex_bypass);
	cb->add_icon_override("unchecked", tex_bypass);

	Control *p = memnew(Control);
	gc->add_child(p);
	p->set_h_size_flags(SIZE_EXPAND);
	p->set_v_size_flags(0);

	cb = memnew(CheckBox);
	gc->add_child(cb);
	cb->set_pressed(true);
	cb->add_style_override("hover", sbi_white);
	cb->add_style_override("hover_pressed", sbi_white);
	cb->add_style_override("pressed", sbi_blue);
	cb->add_style_override("normal", sbi_blueless);
	cb->add_icon_override("checked", tex_output);
	cb->add_icon_override("unchecked", tex_output);
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
