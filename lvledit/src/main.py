#!/usr/bin/python3
#  main.py
#  
#  Copyright 2013 Robert Knauer <robert@privatdemail.net>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  
import level
from gi.repository import Gtk, GObject # python-gobject
from gi.repository.Gtk import Builder

class LevelEditor (object):
	builder = None
	metadata_store = None
	level = level.Level()
	changed = False
	opened_file = None
	
	def __init__(self):
		### READ FROM GUI FILE ###
		self.builder = Builder()
		self.builder.add_from_file("gui.glade")
		self.builder.connect_signals(self)
		### CREATE STUFF FOR THE METADATA TREEVIEW ###
		## Create the key column:
		key = Gtk.TreeViewColumn()
		key.set_title("Schlüssel")
		key_cell = Gtk.CellRendererText()
		key.pack_start(key_cell, True)
		## Create the value column:
		value = Gtk.TreeViewColumn()
		value.set_title("Wert")
		value_cell = Gtk.CellRendererText()
		value.pack_start(value_cell, True)
		## Add the columns to the TreeView:
		self.builder.get_object("treeview1").append_column(key)
		self.builder.get_object("treeview1").append_column(value)
		## Tell the renderers which items in the model they have to display:
		key.add_attribute(key_cell, "text", 0)
		value.add_attribute(value_cell, "text", 1)
		## Create the model:
		self.metadata_store = Gtk.ListStore(GObject.TYPE_STRING, GObject.TYPE_STRING)
		## Assign the model to the TreeView:
		self.builder.get_object("treeview1").set_model(self.metadata_store)
		### FILL THE METADATA TREEVIEW ###
		self.update_metadata_store()
		### SET THE WINDOW TITLE ###
		self.update_window_title()
	def run(self):
		try:
			Gtk.main()
		except KeyboardInterrupt:
			self.quit()
	def quit(self):
		Gtk.main_quit()
	def update_metadata_store(self):
		self.metadata_store.clear()
		for key, value in self.level.get_all_metadata().items():
			self.metadata_store.append([key, value])
	def update_window_title(self):
		## Check for unsaved file:
		if self.changed:
			t = "*"
		else:
			t = ""
		## Check for the filename:
		if self.opened_file is None:
			t += "unnamed"
		else:
			t += str(self.opened_file)
		## Append the program name & version:
		t += " - CAPSAICIN LevelEditor v0.1"
		## Set title:
		self.builder.get_object("window1").set_title(t)
	### window1 EVENTS ###
	def on_window1_delete_event(self, *args):
		# closed
		self.quit()
	def on_imagemenuitem2_activate(self, *args):
		# file -> open
		self.builder.get_object("filechooserdialog2").set_visible(True)
	def on_imagemenuitem3_activate(self, *args):
		# file -> save
		self.builder.get_object("filechooserdialog1").set_visible(True)
	def on_imagemenuitem4_activate(self, *args):
		# file -> save as
		self.builder.get_object("filechooserdialog1").set_visible(True)
	def on_imagemenuitem5_activate(self, *args):
		# file -> quit
		self.quit()
	def on_imagemenuitem10_activate(self, *args):
		# help -> about
		self.builder.get_object("aboutdialog1").set_visible(True)
	### aboutdialog1 EVENTS ###
	def on_aboutdialog1_delete_event(self, *args):
		# closed
		self.builder.get_object("aboutdialog1").set_visible(False)
		return True
	def on_aboutdialog_action_area1_button_press_event(self, *args):
		# close pressed
		self.builder.get_object("aboutdialog1").set_visible(False)
	### window1/tab1 EVENTS ###
	def on_button1_clicked(self, *args):
		# new pressed
		self.builder.get_object("dialog2").set_visible(True)
	def on_button2_clicked(self, *args):
		# edit pressed
		row = self.builder.get_object("treeview-selection1").get_selected_rows()
		self.builder.get_object("entry4").set_text(row[0].get_value(row[0].get_iter(row[1][0]), 0))
		self.builder.get_object("entry5").set_text(row[0].get_value(row[0].get_iter(row[1][0]), 1))
		self.builder.get_object("dialog3").set_visible(True)
	def on_button3_clicked(self, *args):
		# delete pressed
		self.builder.get_object("dialog1").set_visible(True)
	def on_treeview_selection1_changed(self, *args):
		# treeview selection changed
		selected = self.builder.get_object("treeview-selection1").count_selected_rows()
		if selected == 1:
			# Allow editing:
			self.builder.get_object("button2").set_sensitive(True)
			# Allow deleting:
			self.builder.get_object("button3").set_sensitive(True)
		elif selected > 1:
			# Disable editing:
			self.builder.get_object("button2").set_sensitive(False)
			# Allow deleting:
			self.builder.get_object("button3").set_sensitive(True)
		else:
			# Disable editing:
			self.builder.get_object("button2").set_sensitive(False)
			# Disable deleting:
			self.builder.get_object("button3").set_sensitive(False)
	### dialog1 (delete metadata) EVENTS ###
	def on_dialog1_delete_event(self, *args):
		# closed
		self.builder.get_object("dialog1").set_visible(False)
		return True
	def on_button4_clicked(self, *args):
		# no button pressed
		self.builder.get_object("dialog1").set_visible(False)
	def on_button5_clicked(self, *args):
		# yes button pressed
		rows = self.builder.get_object("treeview-selection1").get_selected_rows()
		for item in rows[1]:
			self.level.delete_metadata(rows[0].get_value(rows[0].get_iter(item), 0))
		self.update_metadata_store()
		self.builder.get_object("dialog1").set_visible(False)
	### filechooserdialog1 (save) EVENTS ###
	def on_filechooserdialog1_delete_event(self, *args):
		# closed
		self.builder.get_object("filechooserdialog1").set_visible(False)
		return True
	def on_button6_clicked(self, *args):
		# abort pressed
		self.builder.get_object("filechooserdialog1").set_visible(False)
	### filechooserdialog2 (open) EVENTS ###
	def on_filechooserdialog2_delete_event(self, *args):
		# closed
		self.builder.get_object("filechooserdialog2").set_visible(False)
		return True
	def on_button8_clicked(self, *args):
		# abort pressed
		self.builder.get_object("filechooserdialog2").set_visible(False)
	### dialog2 (add metadata) EVENTS ###
	def on_dialog2_delete_event(self, *args):
		# closed
		self.builder.get_object("dialog2").set_visible(False)
		return True
	def on_button10_clicked(self, *args):
		# abort button pressed
		self.builder.get_object("dialog2").set_visible(False)
		self.builder.get_object("entry2").set_text("")
		self.builder.get_object("entry3").set_text("")
	def on_button11_clicked(self, *args):
		# add button pressed
		key = self.builder.get_object("entry2").get_text().strip()
		value = self.builder.get_object("entry3").get_text().strip()
		if key in self.level.get_all_metadata():
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Schlüssel!")
			self.builder.get_object("messagedialog1").format_secondary_text("Dieser Schlüssel wird bereits verwendet!")
			self.builder.get_object("messagedialog1").set_visible(True)
		elif len(key) > 255 or len(key) == 0:
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Schlüssel!")
			self.builder.get_object("messagedialog1").format_secondary_text("Der Schlüssel entspricht nicht der zulässigen Zeichen-Anzahl! (1 bis 255 Zeichen)")
			self.builder.get_object("messagedialog1").set_visible(True)
		elif len(value) > 255 or len(value) == 0:
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Wert!")
			self.builder.get_object("messagedialog1").format_secondary_text("Der Wert entspricht nicht der zulässigen Zeichen-Anzahl! (1 bis 255 Zeichen)")
			self.builder.get_object("messagedialog1").set_visible(True)
		else:
			self.level.set_metadata(key, value)
			self.update_metadata_store()
			self.builder.get_object("dialog2").set_visible(False)
			self.builder.get_object("entry2").set_text("")
			self.builder.get_object("entry3").set_text("")
	### dialog3 (edit metadata) EVENTS ###
	def on_dialog3_delete_event(self, *args):
		# closed
		self.builder.get_object("dialog3").set_visible(False)
		return True
	def on_button12_clicked(self, *args):
		# abort button pressed
		self.builder.get_object("dialog3").set_visible(False)
	def on_button13_clicked(self, *args):
		# submit button pressed
		key = self.builder.get_object("entry4").get_text()
		value = self.builder.get_object("entry5").get_text().strip()
		if len(value) > 255 or len(value) == 0:
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Wert!")
			self.builder.get_object("messagedialog1").format_secondary_text("Der Wert entspricht nicht der zulässigen Zeichen-Anzahl! (1 bis 255 Zeichen)")
			self.builder.get_object("messagedialog1").set_visible(True)
		else:
			self.level.set_metadata(key, value)
			self.update_metadata_store()
			self.builder.get_object("dialog3").set_visible(False)
			self.builder.get_object("entry4").set_text("")
			self.builder.get_object("entry5").set_text("")
	### messagedialog1 EVENTS ###
	def on_messagedialog1_delete_event(self, *args):
		# closed
		self.builder.get_object("messagedialog1").set_visible(False)
		return True
	def on_button14_clicked(self, *args):
		# okay button pressed
		self.builder.get_object("messagedialog1").set_visible(False)

if __name__ == "__main__":
	app = LevelEditor()
	app.run()
