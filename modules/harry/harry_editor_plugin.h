/*************************************************************************/
/*  grid_map_editor_plugin.h                                             */
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

#ifndef HARRY_EDITOR_PLUGIN_H
#define HARRY_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "editor/pane_drag.h"
#include "scene/gui/graph_edit.h"
#include "harry.h"

class HarryEditor : public VBoxContainer {
	GDCLASS(HarryEditor, VBoxContainer);

	EditorNode *editor;
	VBoxContainer *settings_vbc;
	Label *label;

	//ScrollContainer *path_edit;
	//HBoxContainer *path_hb;
	PanelContainer *editor_base;

	GraphEdit *graph;
	PopupMenu *add_popup;

	void _popup_request(const Vector2 &p_position);
	void _add_node(int p_idx);

public:
	HarryEditor();
	//HarryEditor(EditorNode *p_editor);
};

class HarryEditorPlugin : public EditorPlugin {
	GDCLASS(HarryEditorPlugin, EditorPlugin);

	EditorNode *editor;
	HarryEditor *harryEditor;
	Button *button;

public:
	HarryEditorPlugin(EditorNode *p_editor);
	~HarryEditorPlugin();

	virtual void make_visible(bool isVisible);
	virtual void edit(Object *p_node);
	virtual bool handles(Object *p_node) const;
};
#endif
