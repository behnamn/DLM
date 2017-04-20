#!/usr/bin/env python

import os, subprocess
import shutil
import errno
import math, random
import numpy as np
 
dir_path = os.path.dirname(os.path.realpath(__file__))
#dir_pathos.path.dirname(os.path.abspath(__file__))

def copydir(src, dest):
    try:
        shutil.copytree(src, dest)
    except OSError as e:
        # If the error was caused because the source wasn't a directory
        if e.errno == errno.ENOTDIR:
            shutil.copy(src, dest)
        else:
            print('Directory not copied. Error: %s' % e)

class cd:
	def __init__(self, newPath):
    		self.newPath = os.path.expanduser(newPath)
	def __enter__(self):
        	self.savedPath = os.getcwd()
        	if not os.path.exists(self.newPath):
			os.mkdir(self.newPath)
		os.chdir(self.newPath)
   	def __exit__(self, etype, value, traceback):
        	os.chdir(self.savedPath)
def line_graph(loops=[[7,5],[6,5]],lengths=[18,19,20,21,22]):
	gnufile = open("All.gnu",'w')
	L = [3,4,5,6,7,8,9]
	gnufile.write("set terminal png truecolor\n",)
	gnufile.write("set output \"All.png\"\n",)
	gnufile.write("set style data lines\n",)
	gnufile.write("set grid\n",)
	gnufile.write("set ylabel \"Free Energy\"\n",)
	gnufile.write("set xlabel \"Number of Base-pairs\"\n",)
	gnufile.write("set title \"Free Energy "+end+"\"\n",)
	gnufile.write("plot",)
	for i in range(0,len(loops)):
		loop = loops[i]
		for k in range(0,len(lengths)):
			length = lengths[k]
			gnufile.write("\"LM_"+str(loop[0])+":"+str(loop[1])+"_"+str(length)+".txt\" using 1:2 title \""+str(loop[0])+":"+str(loop[1])+"_"+str(length)+"\"",)
			if (i != len(loops) - 1 or k != len(lengths)-1): gnufile.write(",",)
	gnufile.close()
	subprocess.call("gnuplot All.gnu", shell=True)
def print_array(Array):
	for i in range(0,len(Array)):
		for j in range(0,len(Array[0])):
			print(str(Array[i][j])+'\t'),
		print('\n'),
def write_array(Array,filename):
	with open(filename+".txt",'w') as myfile:
		for i in range(0,len(Array)):
			for j in range(0,len(Array[0])):
				myfile.write(str(Array[i][j])+'\t')
			myfile.write('\n')
def circmean(beta,axis=None):
	alpha = np.array(beta)
	mean_angle = np.arctan2(np.mean(np.sin(alpha),axis),np.mean(np.cos(alpha),axis))
	return (180./math.pi) * mean_angle    
def circvar(beta,axis=None):
	alpha = np.array(beta)
	if np.ma.isMaskedArray(alpha) and alpha.mask.shape!=():
		N = np.sum(~alpha.mask,axis)
	else:
		if axis is None:
			N = alpha.size
		else:
			N = alpha.shape[axis]
	R = np.sqrt(np.sum(np.sin(alpha),axis)**2 + np.sum(np.cos(alpha),axis)**2)/N
	V = 1-R
	return (180./math.pi) * V

def get_TvP_without_dP(Staple):
    n_nucs = 2646.
    if Staple == "S":
        n_domains = 236.
    if Staple == "U":
        n_domains = 166.
    Temp = []
    Num_H = []
    Num_U = []
    Num_S = []
    Prob_d = []
    Prob_n = []
    filename = "occupancy.dat"
    with open(filename,'r') as myfile:
        for line in myfile:
            Temp.append(float(line.split('\t')[1]))
            Num_H.append(float(line.split('\t')[5]))
            Num_U.append(float(line.split('\t')[6]))
            Num_S.append(float(line.split('\t')[7]))
            Prob_n.append(float(line.split('\t')[9])/n_nucs)
    T2 = list(set(Temp))
    T = sorted(T2, key=float)
    N_H = []
    N_U = []
    N_S = []
    P_n = []
    for temp in T:
        Ni_H = []
        Ni_U = []
        Ni_S = []
        Pi_n = []
        for k in range(0,len(Temp)): 
            if Temp[k] == temp:
                Ni_H.append(Num_H[k])
                Ni_U.append(Num_U[k])
                Ni_S.append(Num_S[k])
                Pi_n.append(Prob_n[k])
        N_H.append(np.mean(Ni_H))
        N_U.append(np.mean(Ni_U))
        N_S.append(np.mean(Ni_S))
        P_n.append(np.mean(Pi_n))
    return [T, N_H, N_U, N_S, P_n]
def write_TvP(Staple, TvP):
    filename = Staple+"_Total.txt"
    with open(filename,'w') as myfile:
        myfile.write("T" +"\t")
        myfile.write("N_H" +"\t")
        myfile.write("N_U" +"\t")
        myfile.write("N_S" +"\t")
        myfile.write("P_n" +"\t")
        myfile.write('\n')
        for i in range(0,len(TvP[0])):
            myfile.write( str(TvP[0][i]) +"\t"+ str(TvP[1][i]) +"\t"+ str(TvP[2][i]) +"\t"+ str(TvP[3][i]) +"\t"+ str(TvP[4][i]) +"\n" )

def read_input(Staples):
    filename = "input.txt"
    with open(filename,'r') as myfile:
        for line in myfile:
            if line.split(" ")[0] == "staple_file":
                Staples.append((line.split(" ")[2])[0])

Staples = []




read_input(Staples)
for Staple in Staples:
    write_TvP(Staple,get_TvP_without_dP(Staple))	




#Submit Jobs
'''
for Staple in Staples:
	for Ramp in Ramps:
		for SimType in SimTypes:
			for Temp in Temps:
				with cd(Staple):
					with cd(Ramp):
						with cd(SimType):
							with cd(Temp):
								for gamma in gammas:
									for n in n_pars:
										for seed in seeds:
											subprocess.call('cp ~/DLM/Test/ ./', shell=True)
											subprocess.call('cp ~/DLM/Test/ ./', shell=True)
											subprocess.call('cp ~/DLM/Test/ ./', shell=True)
											name = Staple +"_"+ Ramp[0] +"_"+ SimType[0] +"_"+ Temp[0] +"_"+ gamma +"_"+ n +"_"+ "20_1" +"_"+ seed
											lines = [] 
											lines.append("#!/bin/sh")
											lines.append("./DLM "+gamma+" "+n+" 20 1 "+seed)
											with open(name, 'w') as myfile:
												for line in lines:
													myfile.write(line + "\n")
											subprocess.call('chmod u+x '+name, shell=True)       
											subprocess.call('addqueue -c "1 week" -m 1.0 '+name, shell=True)
'''
