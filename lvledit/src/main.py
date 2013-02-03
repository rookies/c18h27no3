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
from gi.repository import Gtk # python-gobject
from gi.repository.Gtk import Builder

class LevelEditor (object):
	def __init__(self):
		self.builder = Builder()
		self.builder.add_from_file("gui.glade")
		self.builder.connect_signals(self)
		#self.builder.get_object("window1")
	def run(self):
		try:
			Gtk.main()
		except KeyboardInterrupt:
			self.quit()
	def quit(self):
		Gtk.main_quit()
	def on_window1_delete_event(self, *args):
		self.quit()
	def on_imagemenuitem10_activate(self, *args):
		self.builder.get_object("aboutdialog1").set_visible(True)
	def on_aboutdialog_action_area1_button_press_event(self, *args):
		self.builder.get_object("aboutdialog1").set_visible(False)

if __name__ == "__main__":
	app = LevelEditor()
	app.run()
