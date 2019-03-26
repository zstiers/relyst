import os
import subprocess
import sys

def main(argv):
	outDir = '../code/script/src/generated'
	args   = ['-Dlanguage=Cpp', '-no-listener', '-visitor', '-o', outDir, '../relyst.g4']
	subprocess.call(['antlr4.bat'] + args)

	# Clean up the generated files. Remove needless and reformat includes
	os.chdir(outDir)
	filesToRemove = ['relystListener.cpp', 'relystBaseListener.cpp', 'relystVisitor.cpp', 'relystBaseVisitor.cpp']
	for filename in filesToRemove:
		try:
			os.remove(filename)
		except:
			pass
	for filename in os.listdir("."):
		if filename.endswith(".h"):
			with open(filename, 'r') as f:
				s = f.read()
			with open(filename, 'w') as f:
				f.write(s.replace('#include "antlr4-runtime.h"', '#include <antlr4/antlr4-runtime.h>', 1))
  
if __name__== "__main__":
	main(sys.argv)