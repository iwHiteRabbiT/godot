/*************************************************************************/
/*  harry_graph_node.cpp                                                 */
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
//#include "scene/resources/default_theme/default_theme.h"

/**
  @Author iWhiteRabbiT
*/

void HarryGraphNode::_toggle_bypass(bool enabled) {

	set_bypass(enabled);
	emit_signal("toggle_bypass", get_title(), enabled);
}

//bool HarryGraphNode::get_output() {
//	return btn_output->is_pressed();
//}

void HarryGraphNode::_toggle_output(bool enabled) {

	set_output(enabled);
	emit_signal("toggle_output", get_title(), enabled);
}

void HarryGraphNode::_bind_methods() {
	ClassDB::bind_method("_toggle_bypass", &HarryGraphNode::_toggle_bypass);
	ClassDB::bind_method("_toggle_output", &HarryGraphNode::_toggle_output);

	ADD_SIGNAL(MethodInfo("toggle_bypass", PropertyInfo(Variant::STRING, "node_name"), PropertyInfo(Variant::BOOL, "pressed")));
	ADD_SIGNAL(MethodInfo("toggle_output", PropertyInfo(Variant::STRING, "node_name"), PropertyInfo(Variant::BOOL, "pressed")));
}

void HarryGraphNode::Set(Ref<HarrySubnet> &p_subnet, const StringName &p_name, const int &input_connections, const Vector2 &p_offset, bool bypass, bool output, Ref<ButtonGroup> &output_btn_grp) {

	//node = p_node;
	subnet = p_subnet;

	set_name(p_name);

	set_title(p_name);
	//set_size(Size2(150, 85));
	set_size(Size2(100, 55));
	set_offset(p_offset);

	GridContainer *gc = memnew(GridContainer);
	add_child(gc);
	gc->set_columns(3);

	Control *p = memnew(Control);
	gc->add_child(p);
	p->set_h_size_flags(SIZE_EXPAND);
	p->set_v_size_flags(0);

	btn_output = memnew(TextureButton);
	gc->add_child(btn_output);
	btn_output->set_toggle_mode(true);
	btn_output->set_normal_texture(get_icon("GuiVisibilityHidden", "EditorIcons"));
	btn_output->set_pressed_texture(get_icon("GuiVisibilityVisible", "EditorIcons"));
	btn_output->set_v_size_flags(SIZE_SHRINK_CENTER);
	btn_output->set_modulate(Color(0, 173 / 255.0f, 240 / 255.0f, 1));

	btn_bypass = memnew(TextureButton);
	gc->add_child(btn_bypass);
	btn_bypass->set_toggle_mode(true);
	btn_bypass->set_normal_texture(get_icon("ArrowRight", "EditorIcons"));
	btn_bypass->set_pressed_texture(get_icon("ArrowUp", "EditorIcons"));
	btn_bypass->set_v_size_flags(SIZE_SHRINK_CENTER);
	btn_bypass->set_modulate(Color(213 / 255.0f, 205 / 255.0f, 47 / 255.0f, 1));

	btn_output->set_button_group(output_btn_grp);

	btn_output->connect("toggled", this, "_toggle_output");	
	btn_bypass->connect("toggled", this, "_toggle_bypass");

	set_output(output);
	set_bypass(bypass);

	int inputs = input_connections > 0 ? input_connections : 0;
	int outputs = 1;
	int slots = inputs < outputs ? outputs : inputs;

	for (int i = 0; i < slots; i++) {
		Label *in_name = memnew(Label);
		add_child(in_name);
		in_name->set_text("");

		set_slot(i,
				i<inputs, 0, Color(1, 1, 1, 1),
				i<outputs, 0, Color(0.7f, 0.7f, 0.9f, 1));
	}
}

//bool HarryGraphNode::get_bypass() {
//	return btn_bypass->is_pressed();
//}

void HarryGraphNode::set_bypass(bool enabled) {

	subnet->set_node_bypass(get_title(), enabled);

	//if (enabled == old_bypass)
	//	return false;

	//old_bypass = enabled;


	btn_bypass->set_pressed(enabled);
	set_comment(enabled);

	//if (enabled)
		//set_output(false);

	//return true;
}

//bool HarryGraphNode::get_output() {
//	return btn_output->is_pressed();
//}

void HarryGraphNode::set_output(bool enabled) {

	subnet->set_node_output(get_title(), enabled);
	//if (enabled == old_output)
	//	return false;

	//old_output = enabled;
	btn_output->set_pressed(enabled);

	//if (enabled)
		//set_bypass(false);

	//return true;
}
