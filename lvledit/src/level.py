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
	LEVEL_VERSION = 1
	level_width = 0
	metadata = {}
	blockdefs = []
	columns = []
	
	def __init__(self):
		pass
	def read(self, filepath):
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
			pos, block_number = struct.unpack("<hB", f.read(3))
			blocks = []
			for j in range(block_number):
				y_pos, blockdef = struct.unpack("<Bh", f.read(3))
				blocks.append({
					"position": y_pos,
					"blockdef": blockdef
				})
			self.columns.append({
				"position": pos,
				"blocks": blocks
			})
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
			print("= BLOCKS =")
			for col in self.columns:
				for blk in col["blocks"]:
					print("x=%d; y=%d; blockdef_id=%d" % (col["position"], blk["position"], blk["blockdef"]))
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
		for col in self.columns:
			f.write(struct.pack("<hB", col["position"], len(col["blocks"])))
			for blk in col["blocks"]:
				f.write(struct.pack("<Bh", blk["position"], blk["blockdef"]))
	## VERSION:
	def get_version(self):
		return self.LEVEL_VERSION
	## LEVEL WIDTH:
	def set_level_width(self, width):
		self.level_width = width
	def get_level_width(self):
		return self.level_width
	## METADATA:
	def set_metadata(self, key, value):
		self.metadata[key] = value
	def get_metadata(self, key):
		return self.metadata[key]
	def get_all_metadata(self):
		return self.metadata
	## BLOCKDEFS:
	def get_blockdefs(self):
		return self.blockdefs
	## COLUMNS:
	def get_columns(self):
		return self.columns
