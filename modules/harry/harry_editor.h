/*************************************************************************/
/*  harry_editor_plugin.h                                                */
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

#ifndef HARRY_EDITOR_H
#define HARRY_EDITOR_H

#include "harry.h"
#include "harry_wrangle.h"
#include "harry_graph_node.h"
#include "editor/editor_node.h"
#include "scene/gui/graph_edit.h"
//#include "editor/editor_plugin.h"
//#include "editor/pane_drag.h"

/**
 * @Author iWhiteRabbiT
*/

class HarryEditor : public VBoxContainer {
	GDCLASS(HarryEditor, VBoxContainer);

	Harry *harry;
	Ref<HarrySubnet> harry_subnet;

	EditorNode *editor;
	VBoxContainer *settings_vbc;
	Label *label;

	PanelContainer *editor_base;

	GraphEdit *graph;
	PopupMenu *add_popup;

	UndoRedo *undo_redo;
	bool updating = false;

	void _popup_request(const Vector2 &p_position);
	void _connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index);
	void _disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index);

	void _add_node(int p_idx);
	void _node_selected(Object *p_node);

	void _update_graph();

	void _node_dragged(const Vector2 &p_from, const Vector2 &p_to, const StringName &p_which);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	HarryEditor();
	void edit(Harry *p_harry);
};

#endif
