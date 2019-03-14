import random as rnd
from collections import defaultdict
import operator

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
	print()

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


def saveCoo(coolist,x,y,char):
	for player in coolist:
		if player[0]==char:
			player[1].append(x)
			player[2].append(y)
			return coolist
	
def findroundwinner(coolist,win_occ):
	for player in coolist:
		d=defaultdict(int)
		for i in player[1]:
			d[i] += 1
		result = max(list(d.items()), key=operator.itemgetter(1))
		
		if result[1]==win_occ: return player[0]
		d=defaultdict(int)
		for i in player[2]:
			d[i] += 1
		result = max(list(d.items()), key=operator.itemgetter(1))
		
		if result[1]==win_occ: return player[0]
	return 0
	
def xoxgame():

#game initials
	game=takeinput("How many rounds? (at least 1)",0)
	win_occ=takeinput("Win after how many occurences? (at least 3)",2)
	m=takeinput(f"Enter column (at least {win_occ})",win_occ-1)
	n=takeinput(f"Enter row (at least as {win_occ})",win_occ-1)
	playernum=takeinput("How many players? (at least 1)",0)
	
	coolist=[]
	scoreboard={}
#player names
	i=0
	while i < playernum:
		char=str(input(f"Alias of player (only one character) {i+1}: "))
		if len(char)!=1 or isinarray(coolist,char):
			print("Invalid alias with multiple characters or try different sequence!!! Do not oppose me!!!")
		else:
			 coolist.append([char,[],[]])
			 scoreboard[char]=0
			 i+=1
#######################	完成です!!!		 
	rnd.shuffle(coolist)
	print("\n################################################################################\n")
	print(f"{coolist[0][0]} starts!!!")
	
	lencoolist=len(coolist)
	 
	
	#number of rounds (<=game) and the only coefficient for scoring 
	countround=1
	
	#between rounds
	while countround<=game:
		playerturn=0
		#number of plays
		playcount=0
		table=createTable(m,n)
		#during a round
		while True:
			print(f"{countround}. round:\n")
			if playerturn==lencoolist: playerturn-=lencoolist
			char=coolist[playerturn][0]
		
			print(f"\n{char}'s turn")
			printTable(table,m,n)
#			print("ELEMENTS: ")
#			printElements(table,m,n)
			while True:
				y=int(input("Enter the x coordinate: "))
				x=int(input("Enter the y coordinate: "))
				
				if x<n and y<m:
					if table[x][y]==" ":
						table[x][y]=char
						break
					else: print("The square is not empty, is indeed occupied!!!")
						
				else: print("Invalid coordinates. Out of bounds!!!")
					
					
			coolist=saveCoo(coolist,x,y,char)
			scoreboard[char]+=countround
			playerturn+=1
			if playcount==playernum*(win_occ-1):
				roundwinner=findroundwinner(coolist,win_occ)
				if roundwinner!=0: 
					printTable(table,m,n)
	#				print("ELEMENTS: ")
	#				printElements(table,m,n)
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
	
	for player in scoreboard:
		print(player,": ",scoreboard[player])

if __name__ == "__main__":
	xoxgame()
	
