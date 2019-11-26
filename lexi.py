def binarysort(val,alist):
    end=len(alist)
    if end==0:
        alist.append(val)
    elif end==1:
        if val<alist[0]:
            alist.insert(0,val)
        else:
            alist.append(val)
    else:
        start=0
        while end!=start+1:
            mid=(end+start)//2
            if val==alist[mid]:
                break
            elif val<alist[mid]:
                end=mid
            else:
                start=mid
        alist.insert(end,val)

def mySort(arr):
    alist=[]
    while len(arr)!=0:
        binarysort(arr.pop(),alist)
    return alist


def binary_search(arr, val, start, end): 
    # we need to distinugish whether we should insert 
    # before or after the left boundary. 
    # imagine [0] is the last step of the binary search 
    # and we need to decide where to insert -1 
    if start == end: 
        if arr[start] > val: 
            return start 
        else: 
            return start+1
  
    # this occurs if we are moving beyond left\'s boundary 
    # meaning the left boundary is the least position to 
    # find a number greater than val 
    if start > end: 
        return start 
  
    mid = (start+end)//2
    if arr[mid] < val: 
        return binary_search(arr, val, mid+1, end) 
    elif arr[mid] > val: 
        return binary_search(arr, val, start, mid-1) 
    else: 
        return mid 
  
def insertion_sort(arr): 
    for i in range(1, len(arr)): 
        val = arr[i] 
        j = binary_search(arr, val, 0, i-1) 
        arr = arr[:j] + [val] + arr[j:i] + arr[i+1:] 
    return arr 

def sep2digits(num):

    digitlist=[]
    length=len(str(num))+1
    for i in range(1,length):
        digitlist.insert(0,int((num%10**i)//10**(i-1)))

    return digitlist

def con2int(numlist):
    sum=0
    length=len(numlist)
    while length!=0:
        tmp=numlist.pop(0)
        length=len(numlist)
        sum+=tmp*10**(length)
    return sum


    digitlist=[]
    length=len(str(num))+1
    for i in range(1,length):
        digitlist.insert(0,int((num%10**i)//10**(i-1)))

    return digitlist

def lex(num):
    numlist=sep2digits(num)
    length_1=len(numlist)-1
    length=len(numlist)
    for i in reversed(range(length_1)):
        
        if numlist[i] < numlist[i+1]:
            for j in reversed(range(i+1,length)):
                if numlist[i] < numlist[j]:
                    numlist[i], numlist[j] = numlist[j], numlist[i]
                    break
            tmp=numlist[i+1:]
            tmp=mySort(tmp)
            numlist[i+1:]=tmp
            break

    return con2int(numlist)


if __name__ == "__main__":
    print(lex(362541))

            