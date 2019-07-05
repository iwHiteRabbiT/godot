/*************************************************************************/
/*  harry_editor.cpp                                                     */
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

#include "harry_editor.h"

/**
  @Author iWhiteRabbiT
*/

HarryEditor::HarryEditor() {

	ScrollContainer *path_edit = memnew(ScrollContainer);
	add_child(path_edit);
	path_edit->set_enable_h_scroll(true);
	path_edit->set_enable_v_scroll(false);
	path_hb = memnew(HBoxContainer);
	path_edit->add_child(path_hb);
	path_hb->add_child(memnew(Label(TTR("Path:"))));

	add_child(memnew(HSeparator));

	PanelContainer *editor_base = memnew(PanelContainer);
	editor_base->set_v_size_flags(SIZE_EXPAND_FILL);
	add_child(editor_base);

	Ref<Theme> base_theme = Theme::get_default();
	//base_theme = EditorNode::get_singleton()->get_theme_base()->get_theme();

	graph = memnew(GraphEdit);
	//graph->set_theme(base_theme);
	editor_base->add_child(graph);
	graph->set_v_size_flags(SIZE_EXPAND_FILL);
	graph->add_valid_right_disconnect_type(0);
	graph->add_valid_left_disconnect_type(0);
	graph->connect("popup_request", this, "_popup_request");
	graph->connect("connection_request", this, "_connection_request", varray(), CONNECT_DEFERRED);
	graph->connect("disconnection_request", this, "_disconnection_request", varray(), CONNECT_DEFERRED);
	graph->connect("node_selected", this, "_node_selected");

	_add_popup();

	open_file = memnew(EditorFileDialog);
	add_child(open_file);
	open_file->set_title(TTR("Open Harry Node"));
	open_file->set_mode(EditorFileDialog::MODE_OPEN_FILE);
	open_file->connect("file_selected", this, "_file_opened");

	undo_redo = EditorNode::get_singleton()->get_undo_redo();
}

void HarryEditor::edit(Harry *p_harry, HarryGeoSheetEditor *p_harry_geo_editor) {

	harry_geo_editor = p_harry_geo_editor;

	if (harry == p_harry)
		return;

	harry = p_harry;

	button_path.clear();
	button_path.push_back(NameNode{ "Root", harry->get_harry_root() });

	edit(harry->get_harry_root());

	//_add_popup();
}

void HarryEditor::edit(Ref<HarrySubnet> p_subnet) {

	if (harry_subnet.is_valid()) {
		harry_subnet->disconnect("node_instance_name_changed", this, "_node_instance_name_changed");
		harry_subnet->disconnect("dirty", this, "_dirty_node");
	}

	harry_subnet = p_subnet;

	if (harry_subnet.is_valid()) {
		harry_subnet->connect("node_instance_name_changed", this, "_node_instance_name_changed");
		harry_subnet->connect("dirty", this, "_dirty_node");
	}

	_update_graph();
	update_path();
}

void HarryEditor::update_path() {
	while (path_hb->get_child_count() > 1) {
		memdelete(path_hb->get_child(1));
	}

	Ref<ButtonGroup> group;
	group.instance();

	for (int i = 0; i < button_path.size(); i++) {
		Button *b = memnew(Button);
		b->set_text(button_path[i].name);
		b->set_toggle_mode(true);
		b->set_button_group(group);
		path_hb->add_child(b);
		b->set_pressed(true);
		b->set_focus_mode(FOCUS_NONE);
		b->connect("pressed", this, "_path_button_pressed", varray(i));
	}
}

void HarryEditor::_path_button_pressed(int p_path) {

	Ref<HarryNode> hn = button_path[p_path].node;

	for (int i = button_path.size() - 1; i > p_path; i--)
		button_path.remove(i);

	edit(hn);
}

void HarryEditor::_popup_request(const Vector2 &p_position) {

	//_update_options_menu();
	//use_popup_menu_position = true;
	popup_menu_position = graph->get_local_mouse_position();
	popup_menu_position += graph->get_scroll_ofs();
	add_popup->set_position(p_position);
	add_popup->popup();
}

void HarryEditor::_connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	//AnimationNodeBlendTree::ConnectionError err = blend_tree->can_connect_node(p_to, p_to_index, p_from);

	//if (err != AnimationNodeBlendTree::CONNECTION_OK) {
	//	EditorNode::get_singleton()->show_warning(TTR("Unable to connect, port may be in use or connection may be invalid."));
	//	return;
	//}

	//updating = true;
	undo_redo->create_action(TTR("Nodes Connected"));
	undo_redo->add_do_method(harry_subnet.ptr(), "connect_node", p_from, p_from_index, p_to, p_to_index);
	undo_redo->add_undo_method(harry_subnet.ptr(), "disconnect_node", p_from, p_from_index, p_to, p_to_index);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	//updating = false;
}

void HarryEditor::_disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	if (harry_subnet->connection_exists(p_from, p_from_index, p_to, p_to_index)) {
		graph->disconnect_node(p_from, p_from_index, p_to, p_to_index);

		updating = true;
		undo_redo->create_action(TTR("Nodes Disconnected"));
		undo_redo->add_do_method(harry_subnet.ptr(), "disconnect_node", p_from, p_from_index, p_to, p_to_index);
		undo_redo->add_undo_method(harry_subnet.ptr(), "connect_node", p_from, p_from_index, p_to, p_to_index);
		undo_redo->add_do_method(this, "_update_graph");
		undo_redo->add_undo_method(this, "_update_graph");
		undo_redo->commit_action();
		updating = false;
	}
}

void HarryEditor::_file_opened(const String &p_file) {

	file_loaded = ResourceLoader::load(p_file);
	if (file_loaded.is_valid()) {
		_add_node(MENU_LOAD_FILE_CONFIRM);
	}
}

void HarryEditor::_add_node(int p_idx) {

	Ref<HarryNode> rhn;

	switch (p_idx) {
		case MENU_LOAD_FILE:
			open_file->clear_filters();
			{
				List<String> filters;
				ResourceLoader::get_recognized_extensions_for_type("HarryNode", &filters);
				for (List<String>::Element *E = filters.front(); E; E = E->next()) {
					open_file->add_filter("*." + E->get());
				}
			}
			open_file->popup_centered_ratio();
			return;

		case MENU_LOAD_FILE_CONFIRM:
			rhn = file_loaded;
			file_loaded.unref();
			break;

		default:
			StringName type = harry_class_names[p_idx].class_name;

			HarryNode *hn = Object::cast_to<HarryNode>(ClassDB::instance(type));
			ERR_FAIL_COND(!hn);
			rhn = Ref<HarryNode>(hn);
	}

	StringName instance_name = harry_subnet->FindNewName(rhn->get_node_name());
	harry_subnet->AddNode(instance_name, rhn);
	//graph->make_canvas_position_local(popup_menu_position);
	harry_subnet->set_node_position(instance_name, popup_menu_position);

	_update_graph();
}

void HarryEditor::_node_selected(Object *p_node) {

	GraphNode *gn = Object::cast_to<GraphNode>(p_node);
	ERR_FAIL_COND(!gn);

	String name = gn->get_title();

	Ref<HarryNode> hn = harry_subnet->GetNode(name).node;
	ERR_FAIL_COND(!hn.is_valid());

	EditorNode::get_singleton()->push_item(hn.ptr(), "", true);

	harry_geo_editor->refresh(hn);
}

void HarryEditor::_node_dragged(const Vector2 &p_from, const Vector2 &p_to, const StringName &p_which) {

	updating = true;
	undo_redo->create_action(TTR("Node Moved"));
	undo_redo->add_do_method(harry_subnet.ptr(), "set_node_position", p_which, p_to / EDSCALE);
	undo_redo->add_undo_method(harry_subnet.ptr(), "set_node_position", p_which, p_from / EDSCALE);
	//undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	updating = false;
}

void HarryEditor::_dive_in(const String &p_which) {

	Ref<HarryNode> hn = harry_subnet->GetNode(p_which).node;

	NameNode nn;
	nn.name = p_which;
	nn.node = hn;

	button_path.push_back(nn);
	edit(nn.node);
}

void HarryEditor::_toggle_bypass(const String &p_which, bool pressed) {

	//harry_subnet->set_node_bypass(p_which, pressed);
	//harry->set_edited(true);
	//_change_notify();
}

void HarryEditor::_toggle_output(const String &p_which, bool pressed) {

	//harry_subnet->set_node_output(p_which, pressed);
	//harry->_change_notify();

	return;
	if (toggling)
		return;

	toggling = true;
	bool enable_next = !pressed;

	for (int i = 0; i < graph->get_child_count(); i++) {

		HarryGraphNode *gn = Object::cast_to<HarryGraphNode>(graph->get_child(i));

		if (!gn)
			continue;

		if (gn->get_title() != p_which) {
			gn->set_output(enable_next);
			harry_subnet->set_node_output(p_which, enable_next);
			enable_next = false;
		}
	}
	toggling = false;
}

void HarryEditor::_node_instance_name_changed(const StringName &p_old_name, const StringName &p_new_name) {

	for (int i = 0; i < graph->get_child_count(); i++) {

		GraphNode *gn = Object::cast_to<GraphNode>(graph->get_child(i));

		if (!gn)
			continue;

		if (gn->get_title() == p_old_name) {
			//gn->set_name(p_new_name);
			gn->set_title(p_new_name);
		}
	}
}

void HarryEditor::_dirty_node(const Ref<HarryNode> &p_node) {
	undo_redo->create_action(TTR("Dirty Node"));
	undo_redo->commit_action();

	//EditorData &editor_data = EditorNode::get_editor_data();
	//editor_data.get_edited_scene_root()->_change_notify();
}

void HarryEditor::_update_graph() {

	if (updating)
		return;

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

	if (!output_btn_grp.is_valid())
		output_btn_grp.instance();

	for (List<StringName>::Element *E = nodes.front(); E; E = E->next()) {

		StringName name = E->get();
		HarrySubnet::Node hn = harry_subnet->GetNode(name);

		//if (!hn.node->is_connected("dirty", this, "_dirty_node"))
		//	hn.node->connect("dirty", this, "_dirty_node");

		//HarryNode *p_hn = hn.node.ptr();

		HarryGraphNode *node;
		if (dynamic_cast<HarrySubnet *>(hn.node.ptr())) {
			node = memnew(HarrySubnetGraphNode);
			node->connect("dive_in", this, "_dive_in");
		} else
			node = memnew(HarryGraphNode);

		graph->add_child(node);

		node->connect("dragged", this, "_node_dragged", varray(name));
		node->connect("toggle_bypass", this, "_toggle_bypass");
		node->connect("toggle_output", this, "_toggle_output");
		node->Set(harry_subnet, name, hn.position, hn.bypass, hn.output, output_btn_grp);
	}

	for (List<StringName>::Element *E = nodes.front(); E; E = E->next()) {

		StringName name = E->get();
		HarrySubnet::Node hn = harry_subnet->GetNode(name);

		for (List<HarrySubnet::Connection>::Element *E = hn.connections.front(); E; E = E->next()) {

			HarrySubnet::Connection c = E->get();

			//graph->connect_node(name, c.from_index, c.to, c.to_index);
			graph->connect_node(c.output, c.output_index, name, c.input_index);
		}
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
		if (harry && !harry_subnet.is_valid() && harry->get_harry_root().is_valid()) {
			edit(harry->get_harry_root());
		}
	}
}

void HarryEditor::_bind_methods() {

	ClassDB::bind_method("_add_node", &HarryEditor::_add_node);
	ClassDB::bind_method("_connection_request", &HarryEditor::_connection_request);
	ClassDB::bind_method("_disconnection_request", &HarryEditor::_disconnection_request);
	ClassDB::bind_method("_popup_request", &HarryEditor::_popup_request);
	ClassDB::bind_method("_node_dragged", &HarryEditor::_node_dragged);
	ClassDB::bind_method("_update_graph", &HarryEditor::_update_graph);
	ClassDB::bind_method("_node_selected", &HarryEditor::_node_selected);
	ClassDB::bind_method("_file_opened", &HarryEditor::_file_opened);
	ClassDB::bind_method("_node_instance_name_changed", &HarryEditor::_node_instance_name_changed);
	ClassDB::bind_method("_dive_in", &HarryEditor::_dive_in);
	ClassDB::bind_method("_path_button_pressed", &HarryEditor::_path_button_pressed);
	ClassDB::bind_method("_toggle_bypass", &HarryEditor::_toggle_bypass);
	ClassDB::bind_method("_toggle_output", &HarryEditor::_toggle_output);
	ClassDB::bind_method("_dirty_node", &HarryEditor::_dirty_node);
}

void HarryEditor::_add_popup() {
	add_popup = memnew(PopupMenu);
	graph->add_child(add_popup);
	add_popup->connect("id_pressed", this, "_add_node");

	List<StringName> harry_node_classes;
	ClassDB::get_inheriters_from_class("HarryNode", &harry_node_classes);

	Map<StringName, PopupMenu *> submenus;
	for (int i = 0; i < harry_node_classes.size(); i++) {
		ClassName cn;
		cn.class_name = harry_node_classes[i];

		HarryNode *hn = Object::cast_to<HarryNode>(ClassDB::instance(cn.class_name));

		StringName cat = hn->get_node_category();
		if (!cat)
			continue;

		if (!submenus.has(cat)) {
			submenus[cat] = memnew(PopupMenu);
			submenus[cat]->set_name(cat);
			submenus[cat]->connect("id_pressed", this, "_add_node");
		}

		cn.node_name = hn->get_node_name();
		harry_class_names.push_back(cn);

		submenus[cat]->add_item(cn.node_name, i);
	}

	for (Map<StringName, PopupMenu *>::Element *e = submenus.front(); e; e = e->next()) {
		PopupMenu *sub = e->get();

		add_popup->add_child(sub);
		add_popup->add_submenu_item(sub->get_name(), sub->get_name());
	}

	add_popup->add_separator();
	add_popup->add_item(TTR("Load..."), MENU_LOAD_FILE);
}
