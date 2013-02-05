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
from gi.repository import Gtk, Gdk, GdkPixbuf, GObject, cairo # python-gobject
from gi.repository.Gtk import Builder
import os.path

class LevelEditor (object):
	IMGPATH = "../data/img/"
	builder = None
	metadata_store = None
	blockdefs_store = None
	blockdefs_store2 = None
	level = level.Level()
	changed = False
	opened_file = None
	opened_filepath = ""
	level_pixmap = None
	block_images = []
	
	def __init__(self):
		### READ FROM GUI FILE ###
		self.builder = Builder()
		self.builder.add_from_file("gui.glade")
		self.builder.connect_signals(self)
		### CREATE STUFF FOR THE METADATA TREEVIEW ###
		key = Gtk.TreeViewColumn("Schlüssel", Gtk.CellRendererText(), text=0)
		value = Gtk.TreeViewColumn("Wert", Gtk.CellRendererText(), text=1)
		## Add the columns to the TreeView:
		self.builder.get_object("treeview1").append_column(key)
		self.builder.get_object("treeview1").append_column(value)
		## Create the model:
		self.metadata_store = Gtk.ListStore(GObject.TYPE_STRING, GObject.TYPE_STRING)
		## Assign the model to the TreeView:
		self.builder.get_object("treeview1").set_model(self.metadata_store)
		## Fill the model:
		self.update_metadata_store()
		### CREATE STUFF FOR THE BLOCKDEFS TREEVIEW #1 ###
		ident = Gtk.TreeViewColumn("ID", Gtk.CellRendererText(), text=0)
		deftype = Gtk.TreeViewColumn("Typ", Gtk.CellRendererText(), text=1)
		arg = Gtk.TreeViewColumn("Argument", Gtk.CellRendererText(), text=2)
		img = Gtk.TreeViewColumn("Vorschau", Gtk.CellRendererPixbuf(), pixbuf=3)
		## Add the columns to the TreeView:
		self.builder.get_object("treeview2").append_column(ident)
		self.builder.get_object("treeview2").append_column(deftype)
		self.builder.get_object("treeview2").append_column(arg)
		self.builder.get_object("treeview2").append_column(img)
		## Create the model:
		self.blockdefs_store = Gtk.ListStore(GObject.TYPE_UINT, GObject.TYPE_STRING, GObject.TYPE_STRING, GdkPixbuf.Pixbuf)
		## Assign the model to the TreeView:
		self.builder.get_object("treeview2").set_model(self.blockdefs_store)
		## Fill the model:
		self.update_blockdefs_store()
		### CREATE STUFF FOR THE BLOCKDEFS TREEVIEW #2 ###
		## Create the ident column:
		ident = Gtk.TreeViewColumn("ID", Gtk.CellRendererText(), text=0)
		img = Gtk.TreeViewColumn("Vorschau", Gtk.CellRendererPixbuf(), pixbuf=1)
		## Add the columns to the TreeView:
		self.builder.get_object("treeview3").append_column(ident)
		self.builder.get_object("treeview3").append_column(img)
		## Create the model:
		self.blockdefs_store2 = Gtk.ListStore(GObject.TYPE_UINT, GdkPixbuf.Pixbuf)
		## Assign the model to the TreeView:
		self.builder.get_object("treeview3").set_model(self.blockdefs_store2)
		## Fill the model:
		self.update_blockdefs_store2()
		### RESIZE LEVEL LAYOUT ###
		self.resize_level_layout()
		### SET THE WINDOW TITLE ###
		self.update_window_title()
	def run(self):
		try:
			Gtk.main()
		except KeyboardInterrupt:
			self.quit()
	def quit(self):
		Gtk.main_quit()
	def update_everything(self):
		## Metadata Store:
		self.update_metadata_store()
		## Blockdefs Stores:
		self.update_blockdefs_store()
		self.update_blockdefs_store2()
		## Level layout:
		self.fill_block_images()
		## Window Title:
		self.update_window_title()
		## Level Width Scale:
		self.builder.get_object("adjustment1").set_value(self.level.get_level_width())
	def update_metadata_store(self):
		self.metadata_store.clear()
		for key, value in self.level.get_all_metadata().items():
			self.metadata_store.append([key, value])
	def update_blockdefs_store(self):
		self.blockdefs_store.clear()
		for bdef in self.level.get_blockdefs():
			img = Gtk.Image()
			fname = self.IMGPATH + "blocks/" + bdef["arg"] + ".png"
			fname_alt = self.IMGPATH + "block_not_found.png"
			if bdef["type"] == 1:
				t = "Standard"
				if not os.path.exists(fname):
					fname = fname_alt
			elif bdef["type"] == 2:
				t = "Spezial"
				fname = fname_alt
			elif bdef["type"] == 3:
				t = "level-spezifisch"
				fname = fname_alt
			else:
				t = "unbekannt"
				fname = fname_alt
			img.set_from_file(fname)
			self.blockdefs_store.append([
				bdef["id"],
				t,
				str(bdef["arg"]),
				img.get_pixbuf().scale_simple(128, 64, GdkPixbuf.InterpType.NEAREST)
			])
			img.clear()
	def update_blockdefs_store2(self):
		self.blockdefs_store2.clear()
		for bdef in self.level.get_blockdefs():
			img = Gtk.Image()
			fname = self.IMGPATH + "blocks/" + bdef["arg"] + ".png"
			if bdef["type"] == 1 and os.path.exists(fname):
				img.set_from_file(fname)
			else:
				img.set_from_file(self.IMGPATH + "block_not_found.png")
			self.blockdefs_store2.append([
				bdef["id"],
				img.get_pixbuf().scale_simple(128, 64, GdkPixbuf.InterpType.NEAREST)
			])
			img.clear()
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
	def ask_for_discarding_changes(self):
		dlg = Gtk.MessageDialog(parent=self.builder.get_object("window1"))
		dlg.add_buttons(Gtk.STOCK_CANCEL, 1, Gtk.STOCK_OK, 2)
		dlg.set_markup("Ungespeicherte Änderungen")
		dlg.format_secondary_text("Die aktuelle Datei wurde seit der letzten Änderung nicht gespeichert. Änderungen verwerfen?")
		res = dlg.run()
		dlg.destroy()
		if res == 1:
			return False
		else:
			return True
	def get_block_height(self):
		return (self.builder.get_object("layout1").get_allocation().height)/20.
	def resize_level_layout(self):
		layout = self.builder.get_object("layout1")
		layout.set_size((self.level.get_level_width()+1)*self.get_block_height(), layout.get_size()[1])
	def fill_block_images(self):
		layout = self.builder.get_object("layout1")
		height = layout.get_allocation().height
		block_height = height/20.
		self.resize_level_layout()
		del self.block_images[:]
		i = 0
		for col in self.level.get_columns():
			for blk in col["blocks"]:
				self.block_images.append(Gtk.Image())
				bdef = self.level.get_blockdef_by_id(blk["blockdef"])
				if bdef is None or bdef[0] != 1:
					fname = self.IMGPATH + "block_not_found.png"
				else:
					if os.path.exists(self.IMGPATH + "blocks/" + bdef[1] + ".png"):
						fname = self.IMGPATH + "blocks/" + bdef[1] + ".png"
					else:
						fname = self.IMGPATH + "block_not_found.png"
				self.block_images[i].set_from_file(fname)
				self.block_images[i].set_from_pixbuf(self.block_images[i].get_pixbuf().scale_simple(block_height*2, block_height, GdkPixbuf.InterpType.NEAREST))
				layout.put(self.block_images[i], col["position"]*block_height, height-(((blk["position"]/2.)+0.5)*block_height))
				i += 1
		self.builder.get_object("layout1").show_all()
	### window1 EVENTS ###
	def on_window1_delete_event(self, *args):
		# closed
		if not self.changed or self.ask_for_discarding_changes():
			self.quit()
			return False
		return True
	def on_imagemenuitem1_activate(self, *args):
		# file -> new
		if not self.changed or self.ask_for_discarding_changes():
			self.level.cleanup()
			self.changed = False
			self.opened_file = None
			self.opened_filepath = ""
			self.update_everything()
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
		if not self.changed or self.ask_for_discarding_changes():
			self.quit()
	def on_imagemenuitem10_activate(self, *args):
		# help -> about
		self.builder.get_object("aboutdialog1").set_visible(True)
	def on_window1_size_allocate(self, *args):
		# size changed
		self.builder.get_object("scrolledwindow1").set_size_request(args[1].width*0.75, -1)
		self.resize_level_layout()
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
	### window1/tab3 EVENTS ###
	def on_scale1_format_value(self, widget, value):
		return "%d" % value
	def on_scale1_change_value(self, widget, scroll, value):
		self.level.set_level_width(value)
		if not self.changed:
			self.changed = True
			self.update_window_title()
		self.resize_level_layout()
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
		self.changed = True
		self.update_everything()
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
	def on_button9_clicked(self, *args):
		# open pressed
		if self.changed:
			if not self.ask_for_discarding_changes():
				self.builder.get_object("filechooserdialog2").set_visible(False)
				return
		fname = self.builder.get_object("filechooserdialog2").get_filename()
		try:
			self.level.read(fname)
		except Exception:
			self.builder.get_object("messagedialog1").set_markup("Ungültige Datei!")
			self.builder.get_object("messagedialog1").format_secondary_text("Die ausgewählte Datei ist in einem nicht-unterstützten Format!")
			self.builder.get_object("messagedialog1").set_visible(True)
		else:
			### IMPORTANT: update all stuff ###
			self.changed = False
			self.opened_file = os.path.basename(fname)
			self.opened_filepath = fname
			self.update_everything()
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
		elif len(key) > 65535 or len(key) == 0:
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Schlüssel!")
			self.builder.get_object("messagedialog1").format_secondary_text("Der Schlüssel entspricht nicht der zulässigen Zeichen-Anzahl! (1 bis 65535 Zeichen)")
			self.builder.get_object("messagedialog1").set_visible(True)
		elif len(value) > 65535 or len(value) == 0:
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Wert!")
			self.builder.get_object("messagedialog1").format_secondary_text("Der Wert entspricht nicht der zulässigen Zeichen-Anzahl! (1 bis 65535 Zeichen)")
			self.builder.get_object("messagedialog1").set_visible(True)
		else:
			self.level.set_metadata(key, value)
			self.changed = True
			self.update_everything()
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
		if len(value) > 65535 or len(value) == 0:
			self.builder.get_object("messagedialog1").set_markup("Ungültiger Wert!")
			self.builder.get_object("messagedialog1").format_secondary_text("Der Wert entspricht nicht der zulässigen Zeichen-Anzahl! (1 bis 65535 Zeichen)")
			self.builder.get_object("messagedialog1").set_visible(True)
		else:
			self.level.set_metadata(key, value)
			self.changed = True
			self.update_everything()
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
