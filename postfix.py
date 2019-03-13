





#if precedence is less or equal,pop out the previous top
#else if precedence greater, stay together

def priority(op1,op2,precedence):
	
	indexop1=precedence.index(op1)
	indexop2=precedence.index(op2)
	
	if indexop1==indexop2 or (indexop1<4 and indexop1>0 and indexop2<4 and indexop2>0) or (indexop1>3 and indexop2>3): return 0
	if (indexop1==0 and indexop2!=0) or (indexop1<4 and indexop1>0 and indexop2>3): return 1
	if (indexop2==0 and indexop1!=0) or (indexop2<4 and indexop2>0 and indexop1>3): return -1
	
def convertpostfix(exp,precedence):
	stack=[]
	array=""
	
	
	for token in exp:
	
		if token not in precedence:
			if token=="(":
				stack.append(token)
			elif token==")":
				while True:
					stacklast=stack.pop()+" "
					if stacklast=="( ": break
					else: array+=stacklast
			else:
				token+=" "
				array+=token
			
			
		else:
			if stack==[] or stack[-1]=="(": stack.append(token)
			
			elif priority(token,stack[-1],precedence)==1:
				stack.append(token)
				
			else:
				stacklast=stack.pop()+" "
				array+=stacklast
				stack.append(token)
	
	length=len(stack)
	for i in range(length):
		stacklast=stack.pop()+" "
		array+=stacklast
		
	return array			

def solveexp(exp,precedence):
	
	nums=[]
	for char in exp:
		if char== " ": continue
		elif char not in precedence:
			nums.append(char)
		else:
			if char=="^": char="**"
			nums.append(str(eval(nums.pop()+char+nums.pop())))
			
	return nums.pop()

def substituter(exp):
	store=[]
	for char in exp:
		if char.isalpha() and char not in store:
			var=input(f"{char}: ")
			exp=exp.replace(char,var)
			store.append(char)
	return exp

def board():
	
	while True:
		type=str(input("convert postfix and solve?-solve infix?: "))
		type=type.lower()
		if type=="postfix" or type=="infix": break
	
	
	precedence=["^","*","/","%","+","-"]
	exp=str(input("Write an expression: "))
	
	if type=="postfix":
		exp=convertpostfix(exp,precedence)
	
	exp=substituter(exp)
	
	
	print("Expression: ",exp)
	
	print("Result: ",solveexp(exp,precedence))
		
board()			
