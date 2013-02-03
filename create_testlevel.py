#!/usr/bin/python
##################################
### CAPSAICIN v1 Level Creator ###
##################################
### LEVEL FORMAT ###
# Header:						CAPSAICIN[version,16b][level_width,16b]
# Metadata Start:				[metadata_number,8b]
# Loop through Metadata:		[len_key,16b][key][len_value,16b][value]
# Blockdefs Start:				[len_blockdefs,16b]
# Loop through Blockdefs:		[id,16b][type,8b][arg_len,8b][arg]
# Loop through colums (x):		[x_coord,16b][y_number,8b]
#	Loop through blocks (y):	[y_coord,8b][blockdef_id,16b]
### ADDITIONAL DEFINITIONS ###
## Metadata keys ##
# name: Name of the level
# creator: Name of the level creator
# creator_mail: E-mail address of the level creator
# creator_www: Website of the level creator
## Blockdef types & arguments ##
# type=1 (builtin sprite, no special effect) -> argument=sprite_name
# type=2 (builtin sprite, with special effect) -> argument=sprite_name
# type=3 (level-specific sprite) -> argument=sprite_name
import struct, sys, random

### SETTINGS (Important: no utf-8 support!) ###
output = open("/dev/stdout", "wb")
version = 1
levelwidth = 100
metadata = {
	"name": "Testlevel",
	"creator": "Robert Knauer",
	"creator_mail": "robert@privatdemail.net",
	"creator_www": "https://github.com/rookies"
}
blockdefs = [
	{
		"type": 1,
		"argument": "grass"
	},
	{
		"type": 1,
		"argument": "dirt"
	}
]
blocks_per_col = 2
### HEADER ###
output.write(b"CAPSAICIN")
output.write(struct.pack("<hh", version, levelwidth))
### METADATA ###
output.write(struct.pack("<B", len(metadata)))
for key, value in metadata.items():
	output.write(struct.pack("<h", len(key)))
	output.write(bytes(key, "ascii"))
	output.write(struct.pack("<h", len(value)))
	output.write(bytes(value, "ascii"))
### BLOCK DEFINITIONS ###
output.write(struct.pack("<h", len(blockdefs)))
i = 0
for block in blockdefs:
	output.write(struct.pack("<hBB", i, block["type"], len(block["argument"])))
	output.write(bytes(block["argument"], "ascii"))
	i += 1
### DATA ###
for i in range(levelwidth):
	output.write(struct.pack("<hB", i, blocks_per_col))
	for j in range(blocks_per_col):
		y_coord = random.randrange(0, 30)
		output.write(struct.pack("<Bh", y_coord, random.randint(0, len(blockdefs)-1)))
