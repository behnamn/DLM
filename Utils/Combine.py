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

def get_TvP_without_dP(Ramp,Staple,gamma,n,seeds):
	Anneal_Melt = Ramp[0]
	HUS = Staple
	if HUS == "S":
		n_domains = 236.
	if HUS == "U":
		n_domains = 166.
	Temp = []
	Prob = []
	for seed in seeds:
		filename = Ramp +"_"+ Staple +"_"+ gamma +"_"+ n +"_"+ "20_1" +"_"+ seed + ".txt"
		i=0
		with open(filename,'r') as myfile:
			for line in myfile:
				if i>7:
					Temp.append(float(line.split()[1]))
					Prob.append(float(line.split()[3])/n_domains)
				i+=1
	if Anneal_Melt == "A":
		T2 = list(set(Temp))
		#T = sorted(T2, key=float, reverse=True)
		T = sorted(T2, key=float)
	if Anneal_Melt == "M":
		T2 = list(set(Temp))
		T = sorted(T2, key=float)
	P = []
	for temp in T:
		Pi = []
		for k in range(0,len(Temp)): 
			if Temp[k] == temp:
				Pi.append(Prob[k])
		P.append(np.mean(Pi))
	T80=0
	T50=0
	T20=0
	if Anneal_Melt == "M":
		T.append(100.)
		P.append(0.)
		for i in range(0,len(T)):
			if P[i] < 0.2:
				T20 = T[i]
				break
		for i in range(0,len(T)):
			if P[i] < 0.5:
				T50 = T[i]
				break
		for i in range(0,len(T)):
			if P[i] < 0.8:
				T80 = T[i]
				break
	if Anneal_Melt == "A":
		T.insert(0, 40.)
		P.insert(0, 1)
		for i in range(0,len(T)):
			if P[i] < 0.2:
				T20 = T[i]
				break
		for i in range(0,len(T)):
			if P[i] < 0.5:
				T50 = T[i]
				break
		for i in range(0,len(T)):
			if P[i] < 0.8:
				T80 = T[i]
				break
	Tm = T50
	Trange = abs(T80-T20)
	return [T,P,Tm,Trange]
def get_TvP(Ramp,Staple,Temp,gamma,n,seeds):
	TvP = get_TvP_without_dP(Ramp,Staple,gamma,n,seeds)
	T_old = TvP[0]
	P_old = TvP[1]
	dT = 0.5
	T = []
	P = []
	if Ramp == "Melt":
		T_low = T_old[0]
		T_high = T_old[len(T_old)-1] 	
	if Ramp == "Anneal":
		T_low = T_old[0]
		T_high = T_old[len(T_old)-1] 	
	if Temp == "Small":
		Tn = T_low
		while (Tn < T_high):
			T.append(Tn)
			Pn = []
			for i in range(0,len(T_old)):
				if (T_old[i] >= Tn and T_old[i] < Tn + dT):
					Pn.append(P_old[i])
			P.append(np.mean(Pn))
			Tn += dT
	else:
		T = T_old
		P = P_old
	dP = []
	for i in range(0,len(T)):
		if (i == 0):
			dP.append(abs(P[0]-P[1])/abs(T[0]-T[1]))
		else:
			dP.append(abs(P[i]-P[i-1])/abs(T[i]-T[i-1]))
	return[T,P,dP,TvP[2],TvP[3]]
def write_TvP(Ramp,Staple,Sim_Type,Temp,gamma,n,seeds):
	TvP = get_TvP(Ramp,Staple,Temp,gamma,n,seeds)
	filename = Staple +"_"+ Ramp +"_"+ Sim_Type +"_"+ Temp +"_"+ gamma +"_"+ n
	with open(dir_path+"/"+filename+".txt",'w') as myfile:
		myfile.write("T" +"\t")
		myfile.write("P(" + Staple +","+ Ramp[0] +","+ Sim_Type[0] +","+ Temp[0] +","+ gamma +","+ n +")\t")
		myfile.write("dP(" + Staple +","+ Ramp[0] +","+ Sim_Type[0] +","+ Temp[0] +","+ gamma +","+ n +")\t")
		myfile.write("Tm = " + str(TvP[3]) + "\tdT = " + str(TvP[4]))
		myfile.write('\n')
		for i in range(0,len(TvP[0])):
			myfile.write( str(TvP[0][i]) +"\t"+ str(TvP[1][i]) +"\t"+ str(TvP[2][i]) +"\n" )
	
	
		

#Staples = ['S','U']
Staples = ['U']
Ramps = ['Anneal','Melt']
#Ramps = ['Melt']
SimTypes = ['Average','Seq']
#SimTypes = ['Average']
#Temps = ['Large','Small']
Temps = ['Large']

gammas = ['2.5','1.5']
#gammas = ['2.5']
n_pars = ['0','2']
#n_pars = ['2']
#seeds = ['10','20','30','40','50','60']
#seeds = ['10','20']
#seeds = ['10']
#seeds = ['30','40','50','60']

P_tot = []
dP_tot = []

for Staple in Staples:
    for Ramp in Ramps:
        for SimType in SimTypes:
            for Temp in Temps:
                for gamma in gammas:
                    for n in n_pars:
                        filename = Staple +"_"+ Ramp +"_"+ SimType +"_"+ Temp +"_"+ gamma +"_"+ n
                        P = []
                        dP = []
                        with open(filename+".txt",'r') as myfile:
                            for line in myfile:
                                P.append(line.split()[1])
                                dP.append(line.split()[2])
                        P_tot.append(P)
                        dP_tot.append(dP)

for i in range(0,len(dP_tot[0])):
    for j in range(0,len(dP_tot)):
        print(str(dP_tot[j][i])+'\t'),
    print('\n'),
'''
for i in range(0,len(P_tot[0])):
    for j in range(0,len(P_tot)):
        print(str(P_tot[j][i])+'\t'),
    print('\n'),
'''


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
