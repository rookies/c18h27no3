#!/usr/bin/python3
#  level.py
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
import struct

class Level (object):
	LEVEL_VERSION = 2
	level_width = 50
	metadata = {
		"name": "",
		"creator": "",
		"creator_mail": "",
		"creator_www": ""
	}
	blockdefs = []
	columns = []
	extensions = {}
	
	def __init__(self):
		pass
	def cleanup(self):
		self.level_width = 50
		self.metadata = {
			"name": "",
			"creator": "",
			"creator_mail": "",
			"creator_www": ""
		}
		self.blockdefs = []
		self.columns = []
	def read(self, filepath):
		self.cleanup()
		# Open file:
		f = open(filepath, "rb")
		# Read CAPSAICIN header:
		if f.read(9) != bytes("CAPSAICIN", "ascii"):
			raise Exception("Invalid file format! CAPSAICIN header not found!")
		# Read version:
		version = struct.unpack("<h", f.read(2))[0]
		if version != self.LEVEL_VERSION:
			raise Exception("Invalid file version! Only v%d is supported, not v%d!" % (self.LEVEL_VERSION, version))
		# Read level width:
		self.level_width = struct.unpack("<h", f.read(2))[0]
		# Read metadata number:
		num = struct.unpack("<B", f.read(1))[0]
		# Read metadata:
		for i in range(num):
			key = f.read(struct.unpack("<h", f.read(2))[0]).decode("utf-8")
			value = f.read(struct.unpack("<h", f.read(2))[0]).decode("utf-8")
			self.metadata[key] = value
		# Read blockdef number:
		num = struct.unpack("<h", f.read(2))[0]
		# Read blockdefs:
		for i in range(num):
			bd_id, bd_type = struct.unpack("<hB", f.read(3))
			bd_arg = f.read(struct.unpack("<B", f.read(1))[0]).decode("utf-8")
			self.blockdefs.append({
				"id": bd_id,
				"type": bd_type,
				"arg": bd_arg
			})
		# Read data:
		for i in range(self.level_width):
			pos, block_number, item_number = struct.unpack("<hBB", f.read(4))
			blocks = []
			for j in range(block_number):
				y_pos, blockdef = struct.unpack("<Bh", f.read(3))
				blocks.append({
					"position": y_pos,
					"blockdef": blockdef
				})
			items = []
			for j in range(item_number):
				y_pos, iid = struct.unpack("<BB", f.read(2))
				items.append({
					"position": y_pos,
					"id": iid
				})
			self.columns.append({
				"position": pos,
				"blocks": blocks,
				"items": items
			})
		# Read extensions:
		ext_number = struct.unpack("<h", f.read(2))[0]
		for i in range(ext_number):
			name = f.read(struct.unpack("<B", f.read(1))[0]).decode("utf-8")
			data = f.read(struct.unpack("<h", f.read(2))[0])
			if name in self.extensions:
				raise Exception("Extension duplicate! There's already a %s extension." % name)
			else:
				self.extensions[name] = {
					"raw": data
				}
			
	def dump(self, verbose=False):
		print("=== LEVEL DUMP ===")
		print("Version: %d" % self.LEVEL_VERSION)
		print("Width: %d" % self.level_width)
		print("= METADATA =")
		for key, value in self.metadata.items():
			print("'%s' = '%s'" % (key, value))
		print("= BLOCK DEFINITIONS =")
		for bdef in self.blockdefs:
			print("%d: type=%d; arg='%s'" % (bdef["id"], bdef["type"], bdef["arg"]))
		if verbose:
			print("= BLOCKS & ITEMS =")
			for col in self.columns:
				for blk in col["blocks"]:
					print("x=%d; y=%d; blockdef_id=%d" % (col["position"], blk["position"], blk["blockdef"]))
				for itm in col["items"]:
					print("x=%d; y=%d; id=%d" % (col["position"], itm["position"], itm["id"]))
		print("= EXTENSIONS =")
		for name, ext in self.extensions.items():
			print("'%s' => '%s'" % (name, ext["raw"]))
	def write(self, filepath):
		# Open file:
		f = open(filepath, "wb")
		# Write header:
		f.write(b"CAPSAICIN")
		f.write(struct.pack("<hh", self.LEVEL_VERSION, self.level_width))
		# Write metadata:
		f.write(struct.pack("<B", len(self.metadata)))
		for key, value in self.metadata.items():
			f.write(struct.pack("<h", len(key)))
			f.write(bytes(key, "ascii"))
			f.write(struct.pack("<h", len(value)))
			f.write(bytes(value, "ascii"))
		# Write block definitions:
		f.write(struct.pack("<h", len(self.blockdefs)))
		for block in self.blockdefs:
			f.write(struct.pack("<hBB", block["id"], block["type"], len(block["arg"])))
			f.write(bytes(block["arg"], "ascii"))
		# Write data:
		for i in range(self.level_width):
			f.write(struct.pack("<h", i))
			col = self.get_column_by_pos(i)
			if col is None:
				f.write(struct.pack("<BB", 0, 0))
			else:
				f.write(struct.pack("<BB", len(col["blocks"], len(col["items"]))))
				for blk in col["blocks"]:
					f.write(struct.pack("<Bh", blk["position"], blk["blockdef"]))
				for itm in col["items"]:
					f.write(struct.pack("<BB", itm["position"], itm["id"]))
		# Write extensions:
		f.write(struct.pack("<h", len(self.extensions)))
		for name, ext in self.extensions:
			f.write(struct.pack("<B", len(name)))
			f.write(bytes(name, "ascii"))
			f.write(struct.pack("<h", len(ext["raw"])))
			f.write(ext["raw"])
	## VERSION:
	def get_version(self):
		return self.LEVEL_VERSION
	## LEVEL WIDTH:
	def set_level_width(self, width):
		self.level_width = int(width)
	def get_level_width(self):
		return self.level_width
	## METADATA:
	def set_metadata(self, key, value):
		self.metadata[key] = value
	def get_metadata(self, key):
		if key in self.metadata:
			return self.metadata[key]
		else:
			return None
	def get_all_metadata(self):
		return self.metadata
	def delete_metadata(self, key):
		if key in self.metadata:
			del self.metadata[key]
	## BLOCKDEFS:
	def get_blockdefs(self):
		return self.blockdefs
	def get_blockdef_by_id(self, ident):
		for bdef in self.blockdefs:
			if bdef["id"] == ident:
				return (bdef["type"], bdef["arg"])
		return None
	def add_blockdef(self, t, arg):
		# get lowest unused ID:
		for i in range(65536):
			used = False
			for bdef in self.blockdefs:
				if bdef["id"] == i:
					used = True
					break
			if not used:
				break
		# add the blockdef:
		self.blockdefs.append({
			"id": i,
			"type": int(t),
			"arg": arg
		})
	def del_blockdef(self, ident):
		i = 0
		for bdef in self.blockdefs:
			if bdef["id"] == ident:
				del self.blockdefs[i]
				break
			i += 1
	def update_blockdef(self, ident, t, arg):
		## get the list key:
		i = 0
		for bdef in self.blockdefs:
			if bdef["id"] == ident:
				break
			else:
				i += 1
		## update:
		self.blockdefs[i]["type"] = int(t)
		self.blockdefs[i]["arg"] = arg
	## COLUMNS:
	def get_columns(self):
		return self.columns
	def get_column_by_pos(self, pos):
		for col in self.columns:
			if col["position"] == pos:
				return col
		return None
	## BLOCKS:
	def add_block(self, x, y, bdef):
		# 1. check if the column exists:
		pos = None
		i = 0
		for col in self.columns:
			if col["position"] == x:
				pos = i
				break
			else:
				i += 1
		# 2. if not, create it:
		if pos is None:
			pos = len(self.columns)
			self.columns.append({
				"position": x,
				"blocks": [],
				"items": []
			})
		# 3. check if the block exists:
		pos2 = None
		i = 0
		for blk in self.columns[pos]["blocks"]:
			if blk["position"] == y:
				pos2 = i
				break
			else:
				i += 1
		if pos2 is None:
			# 4a. if not, create a new block:
			self.columns[pos]["blocks"].append({
				"position": y,
				"blockdef": bdef
			})
		else:
			# 4b. if it exists, overwrite the old:
			self.columns[pos]["blocks"][pos2]["blockdef"] = bdef
	def remove_block(self, x, y):
		# 1. check if the column exists:
		pos = None
		i = 0
		for col in self.columns:
			if col["position"] == x:
				pos = i
				break
			else:
				i += 1
		if pos is None:
			return False
		# 2. check if the block exists:
		pos2 = None
		i = 0
		for blk in self.columns[pos]["blocks"]:
			if blk["position"] == y:
				pos2 = i
				break
			else:
				i += 1
		if pos2 is None:
			return False
		else:
			del self.columns[pos]["blocks"][pos2]
			if len(self.columns[pos]["blocks"]) is 0:
				del self.columns[pos]
			return True
	### ITEMS:
	def add_item(self, x, y, iid):
		# 1. check if the column exists:
		pos = None
		i = 0
		for col in self.columns:
			if col["position"] == x:
				pos = i
				break
			else:
				i += 1
		# 2. if not, create it:
		if pos is None:
			pos = len(self.columns)
			self.columns.append({
				"position": x,
				"blocks": [],
				"items": []
			})
		# 3. check if the item exists:
		pos2 = None
		i = 0
		for itm in self.columns[pos]["items"]:
			if itm["position"] == y:
				pos2 = i
				break
			else:
				i += 1
		if pos2 is None:
			# 4a. if not, create a new item:
			self.columns[pos]["items"].append({
				"position": y,
				"id": iid
			})
		else:
			# 4b. if it exists, overwrite the old:
			self.columns[pos]["items"][pos2]["id"] = iid
	def remove_item(self, x, y):
		# 1. check if the column exists:
		pos = None
		i = 0
		for col in self.columns:
			if col["position"] == x:
				pos = i
				break
			else:
				i += 1
		if pos is None:
			return False
		# 2. check if the block exists:
		pos2 = None
		i = 0
		for itm in self.columns[pos]["items"]:
			if itm["position"] == y:
				pos2 = i
				break
			else:
				i += 1
		if pos2 is None:
			return False
		else:
			del self.columns[pos]["items"][pos2]
			if len(self.columns[pos]["items"]) is 0:
				del self.columns[pos]
			return True
