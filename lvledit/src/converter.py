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
import level1, level2, level3

def Level1to2 (l1):
	l2 = level2.Level()
	l2.level_width = l1.level_width
	l2.metadata = l1.metadata
	l2.blockdefs = l1.blockdefs
	l2.columns = l1.columns
	for col in l2.columns:
		col["items"] = []
	return l2
	
def Level2to3 (l2):
	l3 = level3.Level()
	l3.level_width = l2.level_width
	l3.metadata = l2.metadata
	l3.blockdefs = l2.blockdefs
	l3.columns = l2.columns
	l3.extensions = l2.extensions
	for col in l3.columns:
		col["opponents"] = []
	return l3
