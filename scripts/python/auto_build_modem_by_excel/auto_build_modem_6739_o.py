#!/usr/bin/python


import os, xlrd, shutil, tarfile
from xlrd.biffh import XLRDError

#*********************************************************
# data
makefile_array = ''
rename_array = ''

#**********************************************************
# string 
apps_dirname = "apps"
mcu_dirname = "mcu"
tools_dirname = "tools"
temp_dirname = 'temp_modem'
build_temp1 = 'build'
build_temp2 = 'build_internal'
apps_fname = 'GEN93_USER_rel.tar.bz2'
apps_cmd = "./build.sh clean,build,pack all GEN93_USER"
excel_fname = 'modem_makefile_list.xls'
modemRename = "modemRenameCopy.pl"

src_path = os.path.dirname(os.getcwd())
print(src_path)
apps_path = os.path.join(src_path, apps_dirname)
mcu_path = os.path.join(src_path, mcu_dirname)
tools_path = os.path.join(src_path, tools_dirname)
modemRename_path = os.path.join(tools_path, modemRename)

print(apps_path)
print(mcu_path)
print(tools_path)

#---------------------------------------------------------------------
# build apps 
#

os.chdir(apps_path)

if os.path.exists('rel') == True:
	shutil.rmtree('rel')

if os.path.exists('build') == True:
	shutil.rmtree('build')

if os.path.exists(apps_fname) == True:
	os.remove(apps_fname)

if os.system(apps_cmd) != 0:
	print("\033[1;34;43m\n\nAPPS build failed!!\033[0m\n\n")
	exit(0)

if os.path.exists(apps_fname) == False:
	print("\033[1;34;43m\n\nAPPS tar file not exist!!!\033[0m\n\n")
	exit(0)

print("\033[1;34;43m\n\n 1111111111111 !!!\033[0m\n\n")
tar = tarfile.open(apps_fname, 'r:bz2')
for tar_info in tar:
	tar.extract(tar_info, '.')
tar.close()
print("\033[1;34;43m\n\n 22222222222222 !!!\033[0m\n\n")
#
#--------------------------------------------------------------------


#---------------------------------------------------------------------
# load excle sheet
# data makefile_array rename_array

os.chdir(tools_path)

if os.path.exists(excel_fname) == False:
	print("\033[1;34;43m\n\n ./tools/*.xls not exists!!!\033[0m\n\n")
	exit(0)

try:
	print("\033[1;34;43m\n\n 33333333333333333 !!!\033[0m\n\n")
	book = xlrd.open_workbook(excel_fname)
	try:
		sheet = book.sheet_by_index(0)
	except XLRDError:
		print("\033[1;34;43m\n\n can not read xls sheet!!!\033[0m\n\n")
	makefile_array = sheet.col_values(0)
	rename_array = sheet.col_values(1)
except IOError:
	sys.stdout.flush()
	print("\033[1;34;43m\n\n xlrd module operator faild!!!\033[0m\n\n")

book.release_resources()
print("\033[1;34;43m\n\n 4444444444444444 !!!\033[0m\n\n")

for i in range(len(makefile_array)):
	print(str(i) + "\t\t" + makefile_array[i] + "\t\t" + rename_array[i])
	
#
#
#---------------------------------------------------------------------

#-----------------------------------------------------------------------------
# 1. build modem 
# 2. use modemRenameCopy.pl 
# 3. rename temp_modem/
#

os.chdir(mcu_path)

if os.path.exists(modemRename_path) == False:
	print("\033[1;34;43m\n\n %s is not exists!!!\033[0m\n\n" % modemRename_path)
	exit(0)

print("\033[1;34;43m\n\n 5555555555555555 !!!\033[0m\n\n")
for i in range(len(makefile_array)):
	if os.path.isdir(build_temp1) == True:
		shutil.rmtree(build_temp1)
	if os.path.isdir(build_temp2) == True:
		shutil.rmtree(build_temp2)
	
	build_modem_cmd = './m ' + '"' +  makefile_array[i] + '"' + ' new'
	print(build_modem_cmd)
	
	if os.system(build_modem_cmd) != 0:
		print("\033[1;34;43m\n\n build project %s faild!!!\033[0m\n\n" % (makefile_array[i]))
		exit(0)
	
	print(makefile_array[i].split('.')[0])
	
	modemRename_cmd = 'perl ' + modemRename_path + ' . ' + '"' + makefile_array[i].split('.')[0] + '"'
	print(modemRename_cmd)
	
	if os.system(modemRename_cmd) != 0:
		print("\033[1;34;43m\n\n %s failed!!!\033[0m\n\n" % modemRename_cmd)
		exit(0)
	if os.path.exists(temp_dirname) == False:
		print("\033[1;34;43m\n\n %s not exist!!!\033[0m\n\n" % temp_dirname)	
		exit(0)

	elf_map_sym_cp = "find build -name *PCB01*S00.??? | grep -v dummy | xargs -i cp {} temp_modem/"
	if os.system(elf_map_sym_cp) != 0:
		print("\033[1;34;43m\n\n %s failed!!!\033[0m\n\n" % elf_map_sym_cp)
		exit(0)

	
	copy_apps_cmd = "cp -rf " + apps_path + "/rel/* " + temp_dirname + "/"
	print(copy_apps_cmd)
	if os.system(copy_apps_cmd) != 0:
		print("\033[1;34;43m\n\n %s failed!!!\033[0m\n\n" % copy_apps_cmd)
		exit(0)

	os.rename(temp_dirname, rename_array[i])
#
#
#------------------------------------------------------------------------------

