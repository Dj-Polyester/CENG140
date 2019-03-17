import random as rnd
from collections import defaultdict
import operator
import time

def takeinput(string,minvalue):
	while True:
		try:
			varname=int(input(f"{string}: "))
			if varname>minvalue and type(varname)==int:
				break
			print("What the f*** are you doing? Entry must exceed ",minvalue)
			if minvalue==0: print("Then why did you choose to play?")
		except Exception as e:
			print("Are you trolling? --> ",e)
		
	return varname

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
	print()
	j=0
	for i in range(n):
		print(f" {i}",end="",flush=True)
	print()
	while(j < 2*m+1):
		if j%2==0:
			for i in range(n):
				print(" -",end="",flush=True)
		else:
			for i in range(n):
				index=int((j-1)/2)
				print(f"|{table[index][i]}",end="",flush=True)
			print(f"| {index}",end="",flush=True)
		print("\n",end="",flush=True)
		j+=1
	print()

def printtoFile(table,m,n,filename):
	print(file=filename)
	j=0
	for i in range(n):
		print(f" {i}",end="",file=filename,flush=True)
	print(file=filename)
	while(j < 2*m+1):
		if j%2==0:
			for i in range(n):
				print(" -",end="",file=filename,flush=True)
		else:
			for i in range(n):
				index=int((j-1)/2)
				print(f"|{table[index][i]}",end="",file=filename,flush=True)
			print(f"| {index}",end="",file=filename,flush=True)
		print("\n",end="",file=filename,flush=True)
		j+=1
	print(file=filename)

def printElements(table,m,n):
	lentab=range(len(table))
	lenrow=range(len(table[0]))
	for row in table:
		if len(row)!=n: print()
	for j in lentab:
		length=len(table[j])
		if length!=n: print(f"{j}.row->{length} long")
		for i in lenrow:
			element=table[j][i]
			if element==" ": print(f"({i},{j})   space")
			else:print(f"({i},{j})   {element}")
	
def findroundwinner(table,m,n,win_occ,char):
	ranm=range(m)
	rann=range(n)
	ranm1=range(m-1)
	rann1=range(n-1)
	count=1
	
	#1)horizontal case
	for i in ranm:
		
		for j in rann1:
			
			if table[i][j]==char and table[i][j+1]==char: count+=1
			else: count=1
			if count==win_occ:return True
	count=1
	
	#2)vertical case
	for j in rann:
		
		for i in ranm1:
			
			if table[i][j]==char and table[i+1][j]==char: count+=1
			else: count=1
			if count==win_occ:return True
			
	#3)cross case (left-right)
	count=1
	i=n-win_occ
	j=0
	
	while True:
	
		if table[j][i]==char and table[j+1][i+1]==char:
			count+=1
		else: count=1
		
		if m<n:
			if i<=m-2 and j==m-2:
				j-=(i-1)
				i=0
			elif i==n-2 or j==m-2:
				i-=(j+1)
				j=0
			else:
				i+=1
				j+=1
		elif m>=n:
			if i==n-2 and j<n-2:
				i-=(j+1)
				j=0
			elif i==n-2 or j==m-2:
				j-=(i-1)
				i=0
			else:
				i+=1
				j+=1
		
		if count==win_occ:return True
		
		if i==win_occ-2 and j==m-2: break
	
	
	
	#3)cross case (right-left)
	count=1
	i=win_occ-1
	j=0
	while True:
	
		if table[j][i]==char and table[j+1][i-1]==char:
			count+=1
		else: count=1
		if m<n:
			if i>=n-m+1 and j==m-2:
				j-=(n-i-2)
				i=n-1
			elif i==1 or j==m-2:
				i+=(j+1)
				j=0
			else:
				i-=1
				j+=1
		elif m>=n:
			if i==1 and j<n-2:
				i+=(j+1)
				j=0
			elif i==1 or j==m-2:
				j-=(n-i-2)
				i=n-1
			else:
				i-=1
				j+=1
		if count==win_occ:return True
		if i==n-win_occ+1 and j==m-2: break	

	return False
	
def xoxgame():
	fhistory=open("history.txt","a")
	fscoreboard=open("scoreboard.txt","a")
	print(time.ctime(),file=fhistory)
	print(time.ctime(),file=fscoreboard)
#game initials
	game=takeinput("How many rounds? (at least 1)",0)
	win_occ=takeinput("Win after how many occurences? (at least 3)",2)
	m=takeinput(f"Enter column (at least {win_occ})",win_occ-1)
	n=takeinput(f"Enter row (at least as {win_occ})",win_occ-1)
	playernum=takeinput("How many players? (at least 1)",0)
	
	playerlist=[]
	scoreboard={}
#player names
	i=0
	while i < playernum:
		char=str(input(f"Alias of player (only one character) {i+1}: "))
		if len(char)!=1 or char in playerlist:
			print("Invalid alias with multiple characters or try different sequence!!! Do not oppose me!!!")
		else:
			 playerlist.append(char)
			 scoreboard[char]=0
			 i+=1
#######################	完成です!!!		 
	rnd.shuffle(playerlist)
	
	print("\n################################################################################\n")
	print(f"{playerlist[0]} starts!!!\n")
	
	lenplayerlist=len(playerlist)
	 
	
	#number of rounds (<=game) and the only coefficient for scoring 
	countround=1
	
	#between rounds
	while countround<=game:
		roundwinner=0
		playerturn=0
		
		#number of plays
		playcount=0
		
		table=createTable(m,n)
		print(f"{countround}. round:\n",file=fhistory)
		#during a round
		while True:
			print(f"{countround}. round:\n")
			if playerturn==lenplayerlist: playerturn-=lenplayerlist
			char=playerlist[playerturn]
		
			print(f"\n{char}'s turn")
			
			printTable(table,m,n)
			
			while True:
				try:
					y=int(input("Enter the x coordinate: "))
					x=int(input("Enter the y coordinate: "))
				
					if x<m and y<n:
						if table[x][y]==" ":
							table[x][y]=char
							break
						else: print("The square is not empty, is indeed occupied!!!")
						
					else: print("Invalid coordinates. Out of bounds!!!")
				except ValueError: print("Invalid value!!!")
			
			print(f"{playcount+1}.play:\n{char}:({y},{x})",file=fhistory)
			printtoFile(table,m,n,fhistory)
			
			scoreboard[char]+=countround
			playerturn+=1
			if playcount>=playernum*(win_occ-1):
				for char in playerlist:
					if findroundwinner(table,m,n,win_occ,char):
						roundwinner=char
						printTable(table,m,n)
						break
				if roundwinner!=0:	
					break

			playcount+=1
		#############################################################################################
		print("\n=================================================================================\n")
		
		print(f"{roundwinner} wins the round!!!\n")
		
		#SCOREBOARD AT THE END OF THE ROUND
		print("SCOREBOARD:")
		
		for player in scoreboard:
			print(player,": ",scoreboard[player])
		countround+=1
			 
	#find the winner of the game
	gamewinner=max(scoreboard.items(), key=operator.itemgetter(1))[0]
	print("\n################################################################################\n")
	print(f"{gamewinner} wins the game with a score of {scoreboard[gamewinner]}!!!\n")
	#SCOREBOARD AT THE END OF THE GAME
	print("SCOREBOARD:")
	print("Result of the game:\n",file=fscoreboard)
	print("Game is over.\n",file=fhistory)
	for player in scoreboard:
		print(player,": ",scoreboard[player])
		print(player,": ",scoreboard[player],file=fscoreboard)
	
	print(time.ctime(),file=fhistory)
	fhistory.close()
	fscoreboard.close()

if __name__ == "__main__":
	xoxgame()
	

	
