#!/usr/bin/python

import os, subprocess, shutil

ccmd = 'find -name "*.trk"'
pproc = subprocess.Popen(ccmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
results = pproc.communicate()

files = results[0].split('\n')[:-1]


ccmd = 'find -name "*.csv"'
pproc = subprocess.Popen(ccmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
results = pproc.communicate()

files.extend(results[0].split('\n')[:-1])

# Find non-val files
for f in files:
  if '_val/' in f:
    targetFile = f.replace('_val/', '/')
    if targetFile in files:
       shutil.copyfile(targetFile, f)
       print("Copied '%s' to '%s'" % (targetFile, f) )
    else: 
       print("Cannot find '%s' for file '%s'", % (targetFile,f) )
