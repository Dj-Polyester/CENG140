import random as rnd
from collections import defaultdict

def xoxgame():
	while True:
		m=int(input("Enter column: "))
		n=int(input("Enter row: "))
		playernum=int(input("How many players?: "))
		if m<=1 or n<=1 or playernum<=1 or type(m)!=int or type(n)!=int or type(playernum)!=int:
			print("What the f**k are you doing?")
		else: break
	
	table=createTable(m,n)
	coolist=[]
######################
	i=0
	while i < playernum:
		char=input(f"Alias of player {i+1}: ")
		if len(char)!=1 or isinarray(coolist,char):
			print("invalid alias!!!")
		else:
			 coolist.append([char,[],[]])
			 i+=1
#######################			 
	while True:
		win_occ=int(input("Win after how many occurences? : "))	
		if win_occ > min(m,n) or type(win_occ)!=int: print("What the f**k are you doing?")
		else: break
	rnd.shuffle(coolist)
	
	print(f"{coolist[0][0]} starts!!!")
	
	lencoolist=len(coolist)
	playerturn=0
	count=0
	while True:
		if playerturn==lencoolist: playerturn-=lencoolist
		char=coolist[playerturn][0]
		
		print(f"{coolist[playerturn][0]}'s turn")
		printTable(table,m,n)
		while True:
			y=int(input("Enter the x coordinate: "))
			x=int(input("Enter the y coordinate: "))
			if x<n and y<m and table[x][y]==" ": break
			else: print("Invalid coordinates!!!")
		coolist=saveCoo(coolist,x,y,char) 
		table[x][y]=char 
		playerturn+=1
		if count==playernum*(win_occ-1):
			winner=findwinner(coolist,win_occ)
			if winner!=0: break
		count+=1
	print(f"{winner} wins!!!")

def isinarray(array,char):
	for player in array:
		if player[0]==char: return 1
		return 0
def createTable(m,n):
	mlist=[]
	for i in range(m):
		nlist=[]
		for j in range(n):
			nlist.append(" ")
		mlist.append(nlist)
	return mlist

def printTable(table,m,n):
	j=0
	while(j < 2*m+1):
		if j%2==0:
			for i in range(n):
				print(" -",end="",flush=True)
		else:
			for i in range(n):
				index=int((j-1)/2)
				print(f"|{table[index][i]}",end="",flush=True)
			print("|",end="",flush=True)
		print("\n",end="",flush=True)
		j+=1

def saveCoo(coolist,x,y,char):
	for player in coolist:
		if player[0]==char:
			player[1].append(x)
			player[2].append(y)
			return coolist
	
def findwinner(coolist,win_occ):
	for player in coolist:
		d=defaultdict(int)
		for i in player[1]:
			d[i] += 1
		result = max(list(d.items()), key=lambda x: x[1])
		
		if result[1]==win_occ: return player[0]
		d=defaultdict(int)
		for i in player[2]:
			d[i] += 1
		result = max(list(d.items()), key=lambda x: x[1])
		
		if result[1]==win_occ: return player[0]
	return 0

xoxgame()
