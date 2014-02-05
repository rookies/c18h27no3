#!/usr/bin/python3
#  level.py
#  
#  Copyright 2014 Robert Knauer <robert@privatdemail.net>
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
import struct, hashlib, io, zipfile

class Level (object):
	LEVEL_VERSION = 3
	ITEMDEFS = [
		"coin",
		"bottle"
	]
	OPPONENTDEFS = []
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
	checksum = ""
	zipbuf = io.BytesIO()
	zipfile = None
	
	def __init__(self):
		self.openzip()
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
		self.extensions = {}
		self.checksum = ""
		self.zipbuf = io.BytesIO()
		self.openzip()
	def openzip(self):
		self.zipfile = zipfile.ZipFile(self.zipbuf, "a", zipfile.ZIP_STORED, False)
	def read(self, filepath):
		self.cleanup()
		# Open file:
		f = open(filepath, "rb")
		# Get filesize:
		f.seek(0,2)
		fsize = f.tell()
		f.seek(0,0)
		# Calculate checksum:
		buf = bytearray(f.read())
		buf[13:45] = b"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
		h = hashlib.sha256(buf)
		f.seek(0,0)
		# Read CAPSAICIN header:
		if f.read(9) != bytes("CAPSAICIN", "ascii"):
			raise Exception("Invalid file format! CAPSAICIN header not found!")
		# Read version:
		version = struct.unpack("<h", f.read(2))[0]
		if version != self.LEVEL_VERSION:
			raise Exception("Invalid file version! Only v%d is supported, not v%d!" % (self.LEVEL_VERSION, version))
		# Read level width:
		self.level_width = struct.unpack("<h", f.read(2))[0]
		# Read checksum:
		self.checksum = "".join("%0.2x" % c for c in struct.unpack("<32s", f.read(32))[0])
		if self.checksum != h.hexdigest():
			raise Exception("Invalid checksum! Should be %s, but is %s." % (self.checksum, h.hexdigest()))
		# Read metadata number:
		num = struct.unpack("<B", f.read(1))[0]
		# Read metadata:
		for i in range(num):
			key = f.read(struct.unpack("<h", f.read(2))[0]).decode("utf-8")
			value = f.read(struct.unpack("<h", f.read(2))[0]).decode("utf-32-le")
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
			pos, block_number, item_number, opp_number = struct.unpack("<hBBB", f.read(5))
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
			opponents = []
			for j in range(opp_number):
				y_pos, oid = struct.unpack("<BB", f.read(2))
				opponents.append({
					"position": y_pos,
					"id": oid
				})
			self.columns.append({
				"position": pos,
				"blocks": blocks,
				"items": items,
				"opponents": opponents
			})
		# Read extensions:
		ext_number = struct.unpack("<h", f.read(2))[0]
		for i in range(ext_number):
			name = f.read(struct.unpack("<B", f.read(1))[0]).decode("utf-8")
			data = f.read(struct.unpack("<h", f.read(2))[0])
			if name in self.extensions:
				raise Exception("Extension duplicate! There's already a %s extension." % name)
			else:
				self.extensions[name] = data
		# Read zip data:
		if f.tell() < fsize:
			self.zipbuf.write(f.read())
			self.openzip()
	def dump(self, verbose=False):
		print("=== LEVEL DUMP ===")
		print("Version: %d" % self.LEVEL_VERSION)
		print("Width: %d" % self.level_width)
		print("Checksum: %s" % self.checksum)
		print("= METADATA =")
		for key, value in self.metadata.items():
			print("'%s' = '%s'" % (key, value))
		print("= BLOCK DEFINITIONS =")
		for bdef in self.blockdefs:
			print("%d: type=%d; arg='%s'" % (bdef["id"], bdef["type"], bdef["arg"]))
		if verbose:
			print("= BLOCKS, ITEMS & OPPONENTS =")
			for col in self.columns:
				for blk in col["blocks"]:
					print("Block: x=%d; y=%d; blockdef_id=%d" % (col["position"], blk["position"], blk["blockdef"]))
				for itm in col["items"]:
					print("Item:  x=%d; y=%d; id=%d" % (col["position"], itm["position"], itm["id"]))
				for opp in col["opponents"]:
					print("Opponent:  x=%d; y=%d; id=%d" % (col["position"], opp["position"], opp["id"]))
		print("= EXTENSIONS =")
		for name, ext in self.extensions.items():
			print("'%s' => '%s'" % (name, ext))
		print("= ZIP FILE =")
		for f in self.zipfile.infolist():
			print("-> %s (%d Bytes)" % (f.filename, f.file_size))
	def write(self, filepath):
		# Open file:
		f = open(filepath, "wb")
		# Write header:
		f.write(b"CAPSAICIN")
		f.write(struct.pack("<hh", self.LEVEL_VERSION, self.level_width))
		# Write dummy checksum:
		f.write(b"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0")
		# Write metadata:
		f.write(struct.pack("<B", len(self.metadata)))
		for key, value in self.metadata.items():
			f.write(struct.pack("<h", len(key)))
			f.write(bytes(key, "ascii"))
			f.write(struct.pack("<h", len(value)*4))
			f.write(bytes(value, "utf-32-le"))
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
				f.write(struct.pack("<BBB", 0, 0, 0))
			else:
				f.write(struct.pack("<BBB", len(col["blocks"]), len(col["items"]), len(col["opponents"])))
				for blk in col["blocks"]:
					f.write(struct.pack("<Bh", blk["position"], blk["blockdef"]))
				for itm in col["items"]:
					f.write(struct.pack("<BB", itm["position"], itm["id"]))
				for opp in col["opponents"]:
					f.write(struct.pack("<BB", opp["position"], opp["id"]))
		# Write extensions:
		f.write(struct.pack("<h", len(self.extensions)))
		for name, ext in self.extensions.items():
			f.write(struct.pack("<B", len(name)))
			f.write(bytes(name, "ascii"))
			f.write(struct.pack("<h", len(ext)))
			f.write(ext)
		# Write zip file:
		self.zipfile.close()
		self.zipbuf.seek(0,0)
		f.write(self.zipbuf.read())
		self.zipbuf.seek(0,0)
		self.openzip()
		# Close file:
		f.close()
		# Calculate checksum:
		f = open(filepath, "r+b")
		h = hashlib.sha256(f.read())
		# Write it to the file:
		f.seek(13,0) # after file header
		f.write(h.digest())
		self.checksum = h.hexdigest()
		f.close()
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
	def append_col(self, pos):
		self.columns.append({
			"position": pos,
			"blocks": [],
			"items": [],
			"opponents": []
		})
	def delete_col_if_empty(self, pos):
		if len(self.columns[pos]["blocks"]) is 0 and len(self.columns[pos]["items"]) is 0 and len(self.columns[pos]["opponents"]) is 0:
			del self.columns[pos]
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
			self.append_col(x)
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
			self.delete_col_if_empty(pos)
			return True
	### ITEMS:
	def get_itemdefs(self):
		return self.ITEMDEFS
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
			self.append_col(x)
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
		# 2. check if the item exists:
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
			self.delete_col_if_empty(pos)
			return True
	### OPPONENTS:
	def get_opponentdefs(self):
		return self.OPPONENTDEFS
	def add_opponent(self, x, y, oid):
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
			self.append_col(x)
		# 3. check if the opponent exists:
		pos2 = None
		i = 0
		for opp in self.columns[pos]["opponents"]:
			if opp["position"] == y:
				pos2 = i
				break
			else:
				i += 1
		if pos2 is None:
			# 4a. if not, create a new opponent:
			self.columns[pos]["opponents"].append({
				"position": y,
				"id": oid
			})
		else:
			# 4b. if it exists, overwrite the old:
			self.columns[pos]["opponents"][pos2]["id"] = oid
	def remove_opponent(self, x, y):
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
		# 2. check if the opponent exists:
		pos2 = None
		i = 0
		for opp in self.columns[pos]["opponents"]:
			if opp["position"] == y:
				pos2 = i
				break
			else:
				i += 1
		if pos2 is None:
			return False
		else:
			del self.columns[pos]["opponents"][pos2]
			self.delete_col_if_empty(pos)
			return True
	### _bgimg EXTENSION:
	def set_bgimg(self, arg):
		self.extensions["_bgimg"] = bytes(arg, "ascii")
		return True
	def unset_bgimg(self):
		if "_bgimg" in self.extensions:
			del self.extensions["_bgimg"]
			return True
		else:
			return False
	def get_bgimg(self):
		if "_bgimg" in self.extensions:
			return (True, self.extensions["_bgimg"].decode("utf-8"))
		else:
			return (False, None)
	### _bgmusic EXTENSION:
	def set_bgmusic(self, arg):
		self.extensions["_bgmusic"] = bytes(arg, "ascii")
		return True
	def unset_bgmusic(self):
		if "_bgmusic" in self.extensions:
			del self.extensions["_bgmusic"]
			return True
		else:
			return False
	def get_bgmusic(self):
		if "_bgmusic" in self.extensions:
			return (True, self.extensions["_bgmusic"].decode("utf-8"))
		else:
			return (False, None)
	### ZIP FILE:
	def zip_list(self):
		return self.zipfile.namelist()
	def zip_info(self, member=None):
		if member is None:
			return self.zipfile.infolist()
		else:
			return self.zipfile.getinfo(member)
	def zip_extract(self, member, path):
		return self.zipfile.extract(member, path)
	def zip_add(self, path, zip_path):
		return self.zipfile.write(path, zip_path)
	def zip_remove(self, member):
		# Create new buffer & zip file:
		newbuf = io.BytesIO()
		newfile = zipfile.ZipFile(newbuf, "a", zipfile.ZIP_STORED, False)
		# Copy all files except of the one to delete:
		for item in self.zipfile.infolist():
			if item.filename != member:
				buf = self.zipfile.read(item.filename)
				newfile.writestr(item, buf)
		# Close the files:
		newfile.close()
		self.zipfile.close()
		# Copy the new buffer to the old buffer:
		self.zipbuf = newbuf
		# Reopen the zipfile:
		self.openzip()
