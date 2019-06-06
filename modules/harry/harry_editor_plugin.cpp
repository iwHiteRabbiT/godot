/*************************************************************************/
/*  harry_editor_plugin.cpp                                              */
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

//#include "core/os/input.h"
//#include "editor/editor_scale.h"
//#include "editor/editor_settings.h"
//#include "editor/plugins/spatial_editor_plugin.h"
//#include "scene/3d/camera.h"

//#include "core/math/geometry.h"
//#include "core/os/keyboard.h"

#include "harry_editor_plugin.h"
//#include "tools/editor/plugins/canvas_item_editor_plugin.h"
//#include "tools/editor/editor_settings.h"

//#include "scene/main/viewport.h"

#include <iostream>

/**
 * @Author iWhiteRabbiT
*/

//HarryEditor::HarryEditor(EditorNode *p_editor) {
HarryEditor::HarryEditor() {

	std::cout << "New Harry Editor" << std::endl;

	//path_edit = memnew(ScrollContainer);
	//add_child(path_edit);
	//path_edit->set_enable_h_scroll(true);
	//path_edit->set_enable_v_scroll(false);
	//path_hb = memnew(HBoxContainer);
	//path_edit->add_child(path_hb);
	//path_hb->add_child(memnew(Label(TTR("Path:"))));

	//add_child(memnew(HSeparator));

	//editor_base = memnew(PanelContainer);
	//editor_base->set_v_size_flags(SIZE_EXPAND_FILL);
	//add_child(editor_base);

	graph = memnew(GraphEdit);
	add_child(graph);
	graph->set_v_size_flags(SIZE_EXPAND_FILL);
	graph->add_valid_right_disconnect_type(0);
	graph->add_valid_left_disconnect_type(0);
	graph->connect("popup_request", this, "_popup_request");
	graph->connect("connection_request", this, "_connection_request", varray(), CONNECT_DEFERRED);
	graph->connect("disconnection_request", this, "_disconnection_request", varray(), CONNECT_DEFERRED);

	add_popup = memnew(PopupMenu);
	graph->add_child(add_popup);
	add_popup->connect("id_pressed", this, "_add_node");
	add_popup->add_item("Wrangle", 0);
	add_popup->add_item("Subnet", 1);

	//HarryNode *hn = memnew(HarryNode);
	//graph->add_child(hn);

	//hn = memnew(HarryNode);
	//graph->add_child(hn);

	//hn = memnew(HarryNode);
	//graph->add_child(hn);
}

void HarryEditor::edit(Harry *p_harry) {
	if (harry == p_harry)
		return;

	harry = p_harry;
	harry_subnet = harry->get_harry_root();

	_update_graph();
}

void HarryEditor::_popup_request(const Vector2 &p_position) {

	//_update_options_menu();
	//use_popup_menu_position = true;
	//popup_menu_position = graph->get_local_mouse_position();
	add_popup->set_position(p_position);
	add_popup->popup();
}

void HarryEditor::_connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	graph->connect_node(p_from, p_from_index, p_to, p_to_index);
}

void HarryEditor::_disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	graph->disconnect_node(p_from, p_from_index, p_to, p_to_index);
}

void HarryEditor::_add_node(int p_idx) {

	std::cout << "_add_node" + p_idx << std::endl;

	HarryNode *hn;
	StringName name;

	switch (p_idx) {
		case 0:
			hn = memnew(HarryWrangle);
			name = "Wrangle";
			break;

		case 1:
			hn = memnew(HarrySubnet);
			name = "Subnet";
			break;
	}

	name = harry_subnet->FindNewName(name);
	harry_subnet->AddNode(name, hn);

	_update_graph();
}

void HarryEditor::_update_graph() {

	//if (updating)
	//	return;

	graph->clear_connections();
	//erase all nodes
	for (int i = 0; i < graph->get_child_count(); i++) {

		if (Object::cast_to<GraphNode>(graph->get_child(i))) {
			memdelete(graph->get_child(i));
			i--;
		}
	}

	if (harry_subnet == NULL)
		return;

	List<StringName> nodes;
	harry_subnet->GetNodeList(&nodes);

	for (List<StringName>::Element *E = nodes.front(); E; E = E->next()) {

		HarryGraphNode *node = memnew(HarryGraphNode);
		graph->add_child(node);

		Ref<HarryNode> hnode = harry_subnet->GetNode(E->get());
		node->Set(hnode);
	}
}

void HarryEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_ENTER_TREE || p_what == NOTIFICATION_THEME_CHANGED) {

		//error_panel->add_style_override("panel", get_stylebox("bg", "Tree"));
		//error_label->add_color_override("font_color", get_color("error_color", "Editor"));

		if (p_what == NOTIFICATION_THEME_CHANGED && is_visible_in_tree())
			_update_graph();
	}

	if (p_what == NOTIFICATION_PROCESS) {
		if (harry && harry->get_harry_root().is_valid()) {

			ObjectID root = 0;
			if (harry_subnet != NULL)
				root = harry_subnet->get_instance_id();

			ObjectID root1 = 0;
			if (harry->get_harry_root() != NULL)
				root1 = harry->get_harry_root()->get_instance_id();

			if (root != root1) {
				harry_subnet = harry->get_harry_root();
				_update_graph();
			}
		}
	}
}

void HarryEditor::_bind_methods() {

	ClassDB::bind_method("_add_node", &HarryEditor::_add_node);
	ClassDB::bind_method("_connection_request", &HarryEditor::_connection_request);
	ClassDB::bind_method("_disconnection_request", &HarryEditor::_disconnection_request);
	ClassDB::bind_method("_popup_request", &HarryEditor::_popup_request);
}

// **************************** PLUGIN BEGIN ********************************************

HarryEditorPlugin::HarryEditorPlugin(EditorNode *p_editor) {

	std::cout << "Editor" << std::endl;

	editor = p_editor;
	harry_editor = memnew(HarryEditor);
	harry_editor->set_custom_minimum_size(Size2(0, 300));

	button = editor->add_bottom_panel_item(TTR("Harry"), harry_editor);
	button->hide();
}

HarryEditorPlugin::~HarryEditorPlugin() {
}

void HarryEditorPlugin::make_visible(bool isVisible) {

	std::cout << "Make visible" << std::endl;

	if (isVisible) {
		std::cout << "Showing" << std::endl;
		button->show();
		editor->make_bottom_panel_item_visible(harry_editor);
		harry_editor->set_process(true);
		//harry_editor->show();
	} else {
		std::cout << "Hiding" << std::endl;
		if (harry_editor->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();
		harry_editor->set_process(false);
		//harry_editor->hide();
	}
}

void HarryEditorPlugin::edit(Object *p_object) {

	std::cout << "Edit" << std::endl;
	harry_editor->edit(Object::cast_to<Harry>(p_object));
}

bool HarryEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("Harry");
}
